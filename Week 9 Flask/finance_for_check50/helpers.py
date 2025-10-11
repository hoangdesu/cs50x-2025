import requests

from flask import redirect, render_template, session, current_app
from functools import wraps

def apology(message, code=400):
    """Render message as an apology to user."""

    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    # return a status code by returning a tuple where the second element is the HTTP status code
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/latest/patterns/viewdecorators/
    """

    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)

    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""
    url = f"https://finance.cs50.io/quote?symbol={symbol.upper()}"
    try:
        response = requests.get(url)
        response.raise_for_status()  # Raise an error for HTTP error responses
        quote_data = response.json()
        return {
            "name": quote_data["companyName"],
            "price": quote_data["latestPrice"],
            "symbol": symbol.upper()
        }
    except requests.RequestException as e:
        print(f"Request error: {e}")
    except (KeyError, ValueError) as e:
        print(f"Data parsing error: {e}")
    return None


def usd(value):
    """Format value as USD."""
    if value < 0:
        return f"-${abs(value):,.2f}"
    
    return f"${value:,.2f}"


def get_owned_shares(symbol: str) -> int:
    # avoid circular import
    db = current_app.config['db']
    
    owned_shares = db.execute("""
        SELECT 
            SUM(CASE WHEN t.action = 'BUY' THEN t.shares
                    WHEN t.action = 'SELL' THEN -t.shares END) AS owned_shares
        FROM transactions t
        WHERE users_id = ? AND symbol = ?
    """, session['user_id'], symbol)[0].get('owned_shares')
    
    if not owned_shares:
        owned_shares = 0
        
    return owned_shares
    