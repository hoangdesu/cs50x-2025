Didnt pass test case:

:( buy handles valid purchase
Cause
expected to find "112.00" in page, but it wasn't found

Log
sending POST request to /login
sending POST request to /buy
sending POST request to /buy
checking that "112.00" is in page

Problem: Because the transactions.symbol is reference field to ticker_symbols.symbol. CS50's test case tries to insert a set of symbols that don't exist in the symbols table, making it fail the foreign key constraint. Not because of wrong formating, no HTML or wrong calculations

Solution: remove the foreign key constraint on transactions.symbol to pass the test case



How to run test locally, no need to login to cs50.dev to test:
Simply run `check50 cs50/problems/2025/x/finance` command in the current project folder
