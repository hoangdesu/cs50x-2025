Creating a SQLite3 database file

Use csv mode

Import csv into a table name 'favorites'

```
sqlite3 favorites.db

sqlite> .mode csv
sqlite> .import favorites.csv favorites
sqlite> .schema
sqlite> .quit
```

- To run a single SQL command in VSCode: highlighted command, ⌘E + ⌘E 

- `.table` to show all tables in a db

