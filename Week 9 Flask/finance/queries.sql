CREATE TABLE transactions (
    id            INTEGER    PRIMARY KEY,
    users_id      INTEGER    REFERENCES users(id),
    symbol        TEXT       REFERENCES ticker_symbols(symbol),
    [action]      TEXT       CHECK ([action] IN ('BUY', 'SELL')),
    price         REAL       CHECK (price > 0) NOT NULL,
    shares        INTEGER    CHECK (shares > 0) NOT NULL,  
    total         REAL       CHECK (total >= 0) NOT NULL,     -- GENERATED ALWAYS AS (price * shares) STORED,    -- computed column: automatically updated => --total needs to be calculated in app first before inserting -> no need computed
    created_at    TEXT       DEFAULT (datetime('now'))       -- e.g. "2025-10-03 17:35:00"
);


DROP TABLE IF EXISTS transactions;

INSERT INTO transactions (users_id, symbol, [action], price, shares, total)
VALUES (3, 'AAL', 'BUY', 12.3, 45, 553.5);


INSERT INTO transactions (users_id, symbol, [action], price, shares)
VALUES (2, 'AAPL', 'BUY', 28.1, 10);


INSERT INTO transactions (users_id, symbol, [action], price, shares)
VALUES (2, 'TSLA', 'BUY', 42.0, 20);


INSERT INTO transactions (users_id, symbol, [action], price, shares)
VALUES (3, 'AAL', 'BUY', 12.3, 45);


SELECT * FROM transactions
WHERE users_id = 5
ORDER BY created_at DESC;


INSERT INTO transactions (users_id, symbol, [action], price, shares)
VALUES (3, 'AAL', 'SELL', 12.3, 45);


UPDATE users
SET cash = 1234
WHERE id = 2;


SELECT * FROM transactions
WHERE users_id = 5;

SELECT SUM(total) FROM transactions
WHERE users_id = 5;


-- Group by symbols
SELECT symbol, SUM(shares), price, SUM(total)
FROM transactions
WHERE users_id = 5
GROUP BY symbol;


SELECT symbol, SUM(shares) AS total_shares, price, SUM(total) AS total_price
FROM transactions
WHERE users_id = 5
GROUP BY symbol;


-- Using Window Function: grand_total is included as a COLUMN -> repeated data
SELECT
    symbol,
    SUM(shares) AS total_shares,
    price,
    SUM(total) AS total_price,
    SUM(SUM(total)) OVER () AS grand_total
FROM transactions
WHERE users_id = 5
GROUP BY symbol;



-- Add a separate UNION row for the grand total
SELECT symbol, SUM(shares) AS total_shares, SUM(total) AS total_price
FROM transactions
WHERE users_id = 5
GROUP BY symbol

UNION ALL

SELECT 'TOTAL' AS symbol, NULL AS total_shares, SUM(total) AS total_price
FROM transactions
WHERE users_id = 5;


SELECT SUM(total) AS grand_total
FROM transactions
WHERE users_id = 5;



SELECT SUM(shares) AS total_shares, SUM(total) AS grand_total
FROM transactions
WHERE users_id = 8;



DELETE FROM transactions
WHERE users_id = 5;
