from flask import render_template, session, request, flash, redirect
from helpers import apology, login_required, lookup

# shared instances
from app import app, db


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
            return render_template('quoted-block.html', quote=quote)
        else:
            print('>> quote error: ', quote)
            return '<div class="mt-5">Stock quote not found</div>'
    else:
        return apology('Invalid symbol')
