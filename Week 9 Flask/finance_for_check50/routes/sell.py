from flask import render_template, session, request, flash, redirect, Blueprint, current_app
from helpers import apology, login_required, lookup, get_owned_shares, usd

bp = Blueprint("sell", __name__)

@bp.route("/sell", methods=["GET"])
@login_required
def sell_get():
    """Sell shares of stock"""
    db = current_app.config['db']

    owned_symbols = db.execute("""
        SELECT symbol,
            SUM(
                CASE
                    WHEN action = 'BUY' THEN shares
                    WHEN action = 'SELL' THEN -shares
                END
            ) AS total_shares
        FROM transactions
        WHERE users_id = ?
        GROUP BY symbol
        HAVING total_shares > 0;
    """, session['user_id'])
    
    print('>> owned_symbols:', owned_symbols)
    
    return render_template('sell.html', symbols=owned_symbols)


@bp.route("/sell", methods=["POST"])
@login_required
def sell_post():
    """Sell shares of stock"""
    db = current_app.config['db']

    print('>> POST /sell: ', request.form)
    symbol = request.form.get('symbol')
    
    if symbol is None:
        return apology('Invalid symbol')
    
    try:
        shares = int(request.form.get('shares'))
    except Exception as e:
        return apology('Invalid shares')
    
    if shares is None:
        return apology('Invalid shares')
    
    owned_shares = get_owned_shares(symbol)
    
    print('>> owned_shares:', owned_shares)

    if shares < 0 or shares > owned_shares:
        return apology('Invalid shares')

    lookedup_symbol = lookup(symbol)
    if lookedup_symbol is None:
        return apology('Invalid symbol')
    
    price = lookedup_symbol.get('price')

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