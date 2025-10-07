from flask import render_template, session, request
from helpers import apology, login_required, lookup, get_owned_shares

# shared instances
from app import app


@app.route("/quote", methods=["GET"])
@login_required
def quote_get():
    """Get stock quote."""
    
    return render_template('quote.html');


@app.route("/quote", methods=["POST"])
@login_required
def quote_post():
    symbol = request.get_json()
    if symbol:
        print('>>POST /quote data: ', symbol)
    
        quote = lookup(symbol)
        print('>> lookup quote:', quote)
        
        if quote:
            # ultilize the session object to remember the quote user selected
            # to be used later in buy page
            session['quote'] = quote

            owned_shares = get_owned_shares(quote.get('symbol'))
            
            return render_template('quoted-block.html', quote=quote, owned_shares=owned_shares)
        else:
            print('>> quote error: ', quote)
            return '<div class="mt-5">Stock quote not found</div>'
    else:
        return apology('Invalid symbol')
