from flask import render_template, session, request, Blueprint
from helpers import apology, login_required, lookup, get_owned_shares

bp = Blueprint("quote", __name__)

@bp.route("/quote", methods=["GET"])
@login_required
def quote_get():
    """Get stock quote."""

    return render_template('quote.html')


@bp.route("/quote", methods=["POST"])
@login_required
def quote_post():
    symbol = request.form.get("symbol")
    if not symbol:
        return apology("Missing symbol")

    quote = lookup(symbol.upper())
    if not quote:
        return apology("invalid symbol")
    
    print('>> quote: ', quote)

    return render_template("quoted.html", quote=quote)

        

