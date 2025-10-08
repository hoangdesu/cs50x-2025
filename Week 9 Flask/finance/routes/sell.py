from flask import render_template, session, request, flash, redirect
from helpers import apology, login_required, lookup, get_owned_shares, usd

# shared instances
from app import app, db

@app.route("/sell", methods=["GET"])
@login_required
def sell_get():
    """Sell shares of stock"""
    
    args_symbol = request.args.get('symbol')
    if not args_symbol:
        flash('Please select a symbol first to sell')
        return redirect('/')

    symbol = lookup(args_symbol)
    
    print('>> session:', session)
    print('>> symbol:', symbol)
    
    owned_shares = get_owned_shares(symbol.get('symbol'))
    
    if owned_shares == 0:
        flash(f"Sorry you don't own any stock from {symbol.get('symbol')} to sell")
        return redirect('/')
    
    print('>> owned_shares:', owned_shares)
    
    available_cash = db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])[0].get('cash')
    print('>> available_cash:', available_cash)
    
    return render_template(
        'sell.html',
        symbol=symbol,
        owned_shares=owned_shares,
        available_cash=available_cash
    )

    
@app.route("/sell", methods=["POST"])
@login_required
def sell_post():
    """Sell shares of stock"""
    print('>> POST /sell: ', request.form)
    symbol = request.form.get('symbol')
    price = float(request.form.get('price'))
    shares = int(request.form.get('shares'))

    if not symbol:
        return apology('Invalid symbol')

    if shares < 0 or shares > get_owned_shares(symbol):
        print('>> shares:', shares, get_owned_shares(symbol))
        return apology('Invalid shares')

    # SQL transaction
    try:
        db.execute('BEGIN')

        query = """
            INSERT INTO transactions (users_id, symbol, [action], price, shares, total)
            VALUES (:user_id, :symbol, 'SELL', :price, :shares, :total);
        """
        
        sell_total = price * shares
        
        db.execute(
            query, 
            user_id=session['user_id'], 
            symbol=symbol,
            price=price,
            shares=shares,
            total=sell_total
        )
        
        user = db.execute('SELECT * FROM users WHERE id = ?', session["user_id"])[0]
    
        print('>> user:', user, user.get('cash'))
        
        user_cash = user.get('cash')
        new_balance = user_cash + sell_total
        db.execute('UPDATE users SET cash = ? WHERE id = ?', new_balance, session['user_id'])

        db.execute("COMMIT")
        print("Inserted Sell transaction successfully")
        
        
    except Exception as e:
        db.execute("ROLLBACK")
        print("Transaction failed. Rolled back", e)
        return apology('Transaction failed')
    

    flash(f'Successfully sold {shares} shares of {symbol} for {usd(sell_total)}!')
    return redirect('/')