from app import app, db
from helpers import lookup
from flask import session
from werkzeug.security import generate_password_hash

# Create test database
db.execute("DELETE FROM users WHERE username = '_cs50'")
db.execute("DELETE FROM transactions WHERE users_id IN (SELECT id FROM users WHERE username = '_cs50')")

# Register test user with initial cash of $10,000
db.execute(
    "INSERT INTO users (username, hash, cash) VALUES (?, ?, ?)",
    "_cs50", generate_password_hash("ohHai28!"), 10000.00
)

user = db.execute("SELECT * FROM users WHERE username = ?", "_cs50")[0]
print(f"Created user: {user}")

# Simulate buying stocks
# Buy 1 share of AAAA at $28
price1 = 28.00
shares1 = 1
total1 = price1 * shares1

db.execute(
    "INSERT INTO transactions (users_id, symbol, action, price, shares, total) VALUES (?, ?, ?, ?, ?, ?)",
    user['id'], "AAAA", "BUY", price1, shares1, total1
)

# Buy 3 shares of AAAA at $28
shares2 = 3
total2 = price1 * shares2

db.execute(
    "INSERT INTO transactions (users_id, symbol, action, price, shares, total) VALUES (?, ?, ?, ?, ?, ?)",
    user['id'], "AAAA", "BUY", price1, shares2, total2
)

# Update user cash
new_cash = 10000 - total1 - total2
db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user['id'])

print(f"\nTransactions created. User cash: ${new_cash}")
print(f"Expected to see: $112.00 (total market value) and ${new_cash:.2f} (remaining cash)")

# Check what the index query returns
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
''', user['id'])

print(f"\nQuery returned: {symbols}")

for symbol in symbols:
    print(f"\nSymbol: {symbol}")
    # Simulate lookup (check50 will mock this)
    price = 28.00  # AAAA price
    total_market = round(price * symbol['total_shares'], 2)
    print(f"Total market value: ${total_market}")

print("\nDone!")
