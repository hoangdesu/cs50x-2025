from flask import render_template, session
from helpers import login_required

# shared instances
from app import app, db

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    
    symbols = db.execute('''
        SELECT symbol, SUM(shares) AS total_shares, price, SUM(total) AS total_price
        FROM transactions
        WHERE users_id = ?
        GROUP BY symbol;
    ''', session['user_id'])
    
    print('>> symbols:', symbols)

    # get cash user currently has
    cash = db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])[0].get('cash')
    print('>> cash:', cash)
    
    # get number of shares and grand total for price user owns
    summaries = db.execute('''
        SELECT SUM(shares) AS total_shares, SUM(total) AS grand_total
        FROM transactions
        WHERE users_id = ?
    ''', session['user_id'])[0]

    print('>> summaries:', summaries)
    
    return render_template(
        'index.html', 
        symbols=symbols, 
        user_name=session['user_name'], 
        cash=cash,
        summaries=summaries
    )