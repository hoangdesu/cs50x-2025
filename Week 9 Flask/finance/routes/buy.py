from flask import render_template, session, request, flash, redirect
from helpers import apology, login_required, lookup, get_owned_shares

# shared instances
from app import app, db


@app.route("/buy", methods=["GET"])
@login_required
def buy_get():
    """Buy shares of stock"""
    
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
    print('>> session:', session)
    
    owned_shares = get_owned_shares(symbol)
    print('>> owned_shares:', owned_shares)
    
    available_cash = db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])[0].get('cash')
    print('>> available_cash:', available_cash)
    
    max_shares_can_buy = int(available_cash / session['quote'].get('price'))
    print('>> max_shares_can_buy:', max_shares_can_buy)
        
    return render_template(
        'buy.html',
        quote = session ['quote'],
        owned_shares = owned_shares,
        max_shares_can_buy = max_shares_can_buy,
        available_cash = available_cash
    )


@app.route("/buy", methods=["POST"])
@login_required
def buy_post():
    symbol = request.form.get('symbol')
    shares = request.form.get('shares')

    if symbol is None:
        return apology('Invalid symbol')
    
    if shares is None or int(shares) <= 0:
        return apology('Invalid shares')
    
    price = request.form.get('price')
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