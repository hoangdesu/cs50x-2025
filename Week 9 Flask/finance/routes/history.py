from flask import render_template, session
from helpers import apology, login_required

# shared instances
from app import app, db


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