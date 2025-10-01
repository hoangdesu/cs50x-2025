import json, sqlite3

def insert_ticker_symbols():
    conn = sqlite3.connect('./finance.db')
    
    # A cursor object is used to execute SQL commands and fetch results
    cursor = conn.cursor()
    
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS ticker_symbols (
            id INTEGER PRIMARY KEY,
            symbol TEXT UNIQUE NOT NULL,
            name TEXT NOT NULL
        )
    ''')
    
    # Commit changes to save the table
    conn.commit()
    
    # print(conn)
    
    with open('./ticker_symbols.json') as file:
        data = json.load(file)
        
    # print(data)
    
    for row in data:
        cursor.execute('''
            INSERT INTO ticker_symbols (symbol, name)
            VAlUES (?, ?)
        ''', (row.get('symbol'), row.get('name')))
        
    # Commit changes to save the table
    conn.commit()
    
    print('Done inserting!')
    conn.close()
    
    
insert_ticker_symbols()

