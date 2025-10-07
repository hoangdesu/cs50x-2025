from flask import render_template, session, request, flash, redirect
from helpers import apology, login_required, lookup, get_owned_shares

# shared instances
from app import app, db

@app.route("/sell", methods=["GET", "POST"])
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
    # return apology("TODO")
    
    return 