from flask import render_template, session
from helpers import login_required

# shared instances
from app import app, db

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