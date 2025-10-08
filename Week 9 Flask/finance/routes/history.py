from flask import render_template, session, request, Blueprint, current_app
from helpers import login_required

bp = Blueprint("history", __name__)

@bp.route("/history")
@login_required
def history():
    """Show history of transactions"""
    db = current_app.config['db']

    page = request.args.get('page', 1, type=int)
    limits = 10
    offset = (page - 1) * limits
    
    query = '''
        SELECT * FROM transactions 
        WHERE users_id = ? 
        ORDER BY created_at DESC
        LIMIT ? OFFSET ?
    '''
    
    transactions = db.execute(query, session['user_id'], limits, offset)

    print('>> transactions: ', transactions)
    
    return render_template('history.html', transactions=transactions, page=page)