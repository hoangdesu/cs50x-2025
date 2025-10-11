from flask import render_template, session, request, flash, redirect, Blueprint, current_app
from helpers import apology, login_required, lookup, get_owned_shares, usd

bp = Blueprint("buy", __name__)

@bp.route("/buy", methods=["GET"])
@login_required
def buy_get():
    """Buy shares of stock"""
    return render_template('buy.html')


@bp.route("/buy", methods=["POST"])
@login_required
def buy_post():
    db = current_app.config['db']

    form_symbol = request.form.get('symbol').upper()
    shares = request.form.get('shares')
    
    symbol = lookup(form_symbol)

    if symbol is None:
        return apology('Invalid symbol')
    
    try:
        shares = int(shares)
    except ValueError:
        return apology('Invalid shares')
    
    buy_total = int(shares) * float(symbol.get('price'))
    print('>> buy_total:', buy_total)
    
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
            symbol=symbol.get('symbol'),
            price=symbol.get('price'), 
            shares=shares,
            total=buy_total
        )
        
        # update user's available cash
        new_balance = user_cash - buy_total
        db.execute('UPDATE users SET cash = ? WHERE id = ?', new_balance, session['user_id'])
        
        db.execute("COMMIT")  # commit all
        print("Inserted Buy transaction successfully")
        
    except Exception as e:
        db.execute("ROLLBACK")
        print("Transaction failed. Rolled back", e)
        return apology('Transaction failed')
    
    flash(f'Successfully bought {shares} shares of {symbol.get('symbol')} for {usd(buy_total)}!')
    return redirect('/')