from flask import request, jsonify
from helpers import apology, login_required
from werkzeug.security import generate_password_hash

# shared instances
from app import app, db

@app.route("/search")
@login_required
def search():
    # Search for symbol autocomplete
    symbol = request.args.get('symbol')
    if symbol:
        print('>> GET /search symbol:', symbol)
        query = '''
            SELECT * FROM ticker_symbols 
            WHERE name LIKE ? OR symbol LIKE ? LIMIT 20
        '''
        suggested_ticker_symbols = db.execute(query, symbol + "%", symbol + "%")
        return jsonify(suggested_ticker_symbols)