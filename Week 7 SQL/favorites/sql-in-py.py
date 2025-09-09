from cs50 import SQL

# Open database
db = SQL('sqlite:///favorites.db')

fav = input('Favorite language: ')

query1 = '''
SELECT COUNT(*) AS counts 
FROM favorites 
WHERE language LIKE ?
'''

query2 = '''
SELECT *
FROM favorites
WHERE language LIKE ?
'''

# Search for language
rows = db.execute(query1, fav)

row = rows[0]
print(row['counts'])

# for row in rows:
#     print(row)