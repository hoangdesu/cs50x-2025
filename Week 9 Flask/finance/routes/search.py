from flask import request, jsonify, Blueprint, current_app
from helpers import login_required

bp = Blueprint("search", __name__)

@bp.route("/search")
@login_required
def search():
    """Search for symbol autocomplete"""
    db = current_app.config['db']

    symbol = request.args.get('symbol')
    if symbol:
        print('>> GET /search symbol:', symbol)
        query = '''
            SELECT * FROM ticker_symbols
            WHERE name LIKE ? OR symbol LIKE ? LIMIT 20
        '''
        suggested_ticker_symbols = db.execute(query, symbol + "%", symbol + "%")
        return jsonify(suggested_ticker_symbols)