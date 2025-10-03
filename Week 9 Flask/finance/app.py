import os

# https://cs50.readthedocs.io/libraries/cs50/python/
from cs50 import SQL

from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import logging

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")



# - registers a function to run after each HTTP request is processed
@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    query = '''
        SELECT symbol, SUM(shares) AS total_shares, price, SUM(total) AS total_price
        FROM transactions
        WHERE users_id = ?
        GROUP BY symbol;
    '''
    rows = db.execute(query, session['user_id'])
    
    print('>> rows:', rows)
    
    return render_template('index.html', transactions=rows)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    
    # GET
    if request.method == 'GET':
        symbol = request.args.get('symbol')

        # need to have a symbol chosen to access the buy page
        if not symbol:
            flash('Please select a symbol first to buy')
            return redirect('/quote')
        
        if 'quote' not in session:
            return apology("Sorry you haven't selected a quote")

        # if the quote on query string doesn't match the one stored in session
        # lookup again, update session to latest
        if symbol != session['quote']['symbol']:
            print(f'>> symbols mismatched. looking up again for {symbol}')
            new_symbol = lookup(symbol)
            if new_symbol is None:
                print('>> the new symbol user typed in address bar does not exist on CS50 finance API')
                return redirect('/quote')
            else:
                session['quote'] = new_symbol
            
        print(">> session['quote']:", session['quote'])
        
        return render_template('buy.html', quote=session['quote'])
    
    # POST
    elif request.method == 'POST':
        symbol = request.form.get('symbol')
        shares = request.form.get('shares')

        if symbol is None:
            return apology('Invalid symbol')
        
        if shares is None or int(shares) <= 0:
            return apology('Invalid shares')
        
        price = session['quote'].get('price')
        buy_total = int(shares) * float(price)
        
        # getting current user data for calculations
        
        # CS50's SELECT always returns a list, get the only result at index 0
        user = db.execute('SELECT * FROM users WHERE id = ?', session["user_id"])[0]
        
        print('>> user:', user, user.get('cash'))
        
        user_cash = user.get('cash')

        if buy_total > user_cash:
            return apology("You're too poor to buy")
        

        # using SQL transaction
        try:
            db.execute('BEGIN')  # start transaction
            
            # record new BUY transaction
            query = """
                INSERT INTO transactions (users_id, symbol, [action], price, shares, total)
                VALUES (:user_id, :symbol, 'BUY', :price, :shares, :total);
            """
            
            db.execute(
                query, 
                user_id=session['user_id'], 
                symbol=symbol, 
                price=price, 
                shares=shares,
                total=buy_total
            )
            
            # update user's available cash
            new_balance = user_cash - buy_total
            db.execute('UPDATE users SET cash = ? WHERE id = ?', new_balance, session['user_id'])
            
            db.execute("COMMIT")  # commit all
            print("Transaction inserted successfully")
            
        except Exception as e:
            db.execute("ROLLBACK")
            print("Transaction failed. Rolled back", e)
            return apology('Transaction failed')
        
        flash(f'Successfully bought {symbol}!')
        return redirect('/')


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    
    query = '''
        SELECT * FROM transactions 
        WHERE users_id = ? 
        ORDER BY created_at DESC
    '''
    
    transactions = db.execute(query, session['user_id'])

    print('>> transactions: ', transactions)
    
    return render_template('history.html', transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        print('\n>> session["user_id"]:', session["user_id"])

        # added feature: display username on navbar
        session['user_name'] = rows[0]['username']

        print('>> session:', session)

        # Redirect user to home page
        flash(f'Welcome back, {session["user_name"]}!')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    flash(f'Goodbye {session["user_name"]}!')

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/login")


@app.route("/search")
@login_required
def search():
    # Search for symbol autocomplete
    symbol = request.args.get('symbol')
    if symbol:
        print('>> GET /search symbol:', symbol)
        query = '''
            SELECT * FROM ticker_symbols 
            WHERE name LIKE ? OR symbol LIKE ? LIMIT 20
        '''
        suggested_ticker_symbols = db.execute(query, "%" + symbol + "%", "%" + symbol + "%")
        return jsonify(suggested_ticker_symbols)


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    if request.method == 'GET':
        return render_template('quote.html');
        
    elif request.method == 'POST':
        # symbol = request.form.get('symbol')
        # print('>> symbol:', symbol)
        
        symbol = request.get_json()
        if symbol:
            print('>>POST /quote data: ', symbol)
        
            quote = lookup(symbol)
            print('>> lookup quote:', quote)
            
            if quote:
                # ultilize the session object to remember the quote user selected
                # to be used later in buy page
                session['quote'] = quote
                return render_template('quoted-block.html', quote=quote)
            else:
                print('>> quote error: ', quote)
                return '<div class="mt-5">Stock quote not found</div>'
        else:
            return apology('Invalid symbol')


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    
    # print('> print ehe:', generate_password_hash('ehe'))
    # app.logger.info('> log ehe:' + generate_password_hash('ehe'))
    
    if request.method == 'GET':
        return render_template('register.html')
    
    elif request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        confirmation = request.form.get('confirmation')
        
        # missing username
        if not username:
            return apology("Username not found", 404)
        
        # username exists
        users = db.execute("SELECT username FROM users WHERE username = ?", username)
        # print('\n>> user:\n', user)
        
        if len(users) > 0 and users[0].get('username') == username:
            return apology("Username exists", 403)
            
        # either password is blank or the passwords do not match
        if not password or not confirmation or password != confirmation:
            return apology("Password error", 403)
            
        insert_res = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        
        if insert_res is None:
            return apology("Insert user error", 500)
        
        # print('>> ', username, password, confirmation)
        
        return redirect("/")
    
    


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
