from flask import render_template, session
from helpers import login_required, lookup

# shared instances
from app import app, db

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    
    symbols = db.execute('''
        SELECT t.symbol,
            SUM(
                CASE
                    WHEN t.action = 'BUY' THEN t.shares
                    WHEN t.action = 'SELL' THEN - t.shares
                END
            ) AS total_shares,
            SUM(
                CASE
                    WHEN t.action = 'BUY' THEN t.total
                    WHEN t.action = 'SELL' THEN - t.total
                END
            ) AS total_invested,
            (
                SUM(
                    CASE
                        WHEN t.action = 'BUY' THEN t.total
                        WHEN t.action = 'SELL' THEN - t.total
                    END
                ) * 1.0 / SUM(
                    CASE
                        WHEN t.action = 'BUY' THEN t.shares
                        WHEN t.action = 'SELL' THEN - t.shares
                    END
                )
            ) AS cost_basis
        FROM transactions AS t
        WHERE t.users_id = ?
        GROUP BY t.symbol
        HAVING total_shares > 0;
    ''', session['user_id'])
    
    for symbol in symbols:
        
        lookedup_symbol = lookup(symbol.get('symbol'))
        print('>> lookedup_symbol:', lookedup_symbol)

        symbol['price'] = lookedup_symbol.get('price')
        symbol['name'] = lookedup_symbol.get('name')
        symbol['total_market'] = lookedup_symbol.get('price') * symbol.get('total_shares')

        # Profit/loss percentage
        # profit_percent = ((current_price - avg_price) / avg_price) * 100
        symbol['profit_percent'] = round(((lookedup_symbol.get('price') - symbol.get('cost_basis')) / symbol.get('cost_basis')) * 100, 2)

        # Absolute profit/loss (in money)
        # profit = (current_price - avg_price) * total_shares
        symbol['profit_absolute'] = round((lookedup_symbol.get('price') - symbol.get('cost_basis')) * symbol.get('total_shares'), 2)

    
    print('>> symbols:', symbols)

    # get cash user currently has
    cash = db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])[0].get('cash')
    print('>> cash:', cash)
    
    # get number of shares and grand total for price user owns
    summaries = db.execute('''
        SELECT
            SUM(
                CASE
                    WHEN action = 'BUY' THEN shares
                    WHEN action = 'SELL' THEN -shares
                END
            ) AS total_shares,
            SUM(
                CASE
                    WHEN action = 'BUY' THEN total
                    WHEN action = 'SELL' THEN -total
                END
            ) AS grand_total_invested
        FROM transactions
        WHERE users_id = ?
    ''', session['user_id'])[0]

    print('>> summaries:', summaries)
    
    grand_total_market_value = 0

    for s in symbols:
        grand_total_market_value += s.get('total_market')

    summaries['grand_total_market_value'] = round(grand_total_market_value, 2)

    # Calculate overall percentage change and profit/loss
    total_invested = summaries['grand_total_invested']
    if total_invested and total_invested != 0:
        summaries['overall_pct_change'] = round(((grand_total_market_value - total_invested) / total_invested) * 100, 2)
        summaries['overall_profit_loss'] = round(grand_total_market_value - total_invested, 2)
    else:
        summaries['overall_pct_change'] = 0
        summaries['overall_profit_loss'] = 0
        
    
    return render_template(
        'index.html', 
        symbols=symbols, 
        user_name=session['user_name'], 
        cash=cash,
        summaries=summaries
    )