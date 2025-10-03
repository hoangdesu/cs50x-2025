from flask import render_template, session, request, flash, redirect
from helpers import apology, login_required, lookup

# shared instances
from app import app, db

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell_get():
    """Sell shares of stock"""
    # return apology("TODO")
    
    return render_template('sell.html')

    
@app.route("/sell", methods=["POST"])
@login_required
def sell_post():
    """Sell shares of stock"""
    # return apology("TODO")
    
    return 