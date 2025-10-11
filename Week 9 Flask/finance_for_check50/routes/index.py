from flask import render_template, session, Blueprint, current_app
from helpers import login_required, lookup

# shared instances
# from app import app, db

bp = Blueprint("index", __name__)

@bp.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    db = current_app.config['db'] # can only access current_app inside a route function, not at the top of a module.
    
    symbols = db.execute('''
        SELECT symbol,
            SUM(
                CASE
                    WHEN action = 'BUY' THEN shares
                    WHEN action = 'SELL' THEN -shares
                END
            ) AS total_shares,
            SUM(
                CASE
                    WHEN action = 'BUY' THEN total
                END
            ) AS gross_invested,
            SUM(
                CASE
                    WHEN action = 'BUY' THEN total
                END
            ) * 1.0 / NULLIF(SUM(
                CASE
                    WHEN action = 'BUY' THEN shares
                END
            ), 0) AS cost_basis
        FROM transactions
        WHERE users_id = ?
        GROUP BY symbol
        HAVING total_shares > 0;
    ''', session['user_id'])
    
    for symbol in symbols:
        
        lookedup_symbol = lookup(symbol.get('symbol'))
        print('>> lookedup_symbol:', lookedup_symbol)

        symbol['price'] = lookedup_symbol.get('price')
        symbol['name'] = lookedup_symbol.get('name')
        symbol['total_market'] = round(lookedup_symbol.get('price') * symbol.get('total_shares'), 2)

        # Calculate total_invested from cost_basis * total_shares
        symbol['total_invested'] = round(symbol.get('cost_basis') * symbol.get('total_shares'), 2)

        # Profit/loss percentage based on total position
        # profit_percent = ((current_price / cost_basis) - 1) * 100
        cost_basis = symbol.get('cost_basis')
        symbol['profit_percent'] = round(((lookedup_symbol.get('price') / cost_basis) - 1) * 100, 2) if cost_basis else 0

        # Absolute profit/loss (in money)
        # profit = total_market_value - total_invested
        symbol['profit_absolute'] = round(symbol['total_market'] - symbol.get('total_invested'), 2)

    
    print('>> symbols:', symbols)

    # get cash user currently has
    cash = db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])[0].get('cash')
    print('>> cash:', cash)
    
    # Calculate summaries from symbols
    summaries = {
        'total_shares': sum(s['total_shares'] for s in symbols),
        'grand_total_market_value': round(sum(s['total_market'] for s in symbols), 2),
        'grand_total_invested': round(sum(s['total_invested'] for s in symbols), 2)
    }

    invested = summaries['grand_total_invested']
    market = summaries['grand_total_market_value']

    if invested > 0:
        summaries['overall_profit_loss'] = round(market - invested, 2)
        summaries['overall_pct_change'] = round(((market / invested) - 1) * 100, 2)
    else:
        summaries['overall_profit_loss'] = 0
        summaries['overall_pct_change'] = 0
        
    
    return render_template(
        'index.html', 
        symbols=symbols, 
        user_name=session['user_name'], 
        cash=cash,
        summaries=summaries
    )
