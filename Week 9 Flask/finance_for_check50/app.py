import os

# https://cs50.readthedocs.io/libraries/cs50/python/
from cs50 import SQL

from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import logging

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")
app.config['db'] = db

# - registers a function to run after each HTTP request is processed
@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Executes the controller for index / and registers all the routes 

# import routes.index

# /register
# import routes.register

# # /login
# import routes.login

# # /logout
# import routes.logout

# # /search
# import routes.search

# # /quote
# import routes.quote

# # /buy
# import routes.buy

# # /sell
# import routes.sell

# # /history
# import routes.history

# /index
from routes.index import bp as index_bp

# /register
from routes.register import bp as register_bp

# /login
from routes.login import bp as login_bp

# /logout
from routes.logout import bp as logout_bp

# /search
from routes.search import bp as search_bp

# /quote
from routes.quote import bp as quote_bp

# /buy
from routes.buy import bp as buy_bp

# /sell
from routes.sell import bp as sell_bp

# /history
from routes.history import bp as history_bp


# Register routes with Blueprint -> better approach and make it work on CS50
app.register_blueprint(index_bp)
app.register_blueprint(register_bp)
app.register_blueprint(login_bp)
app.register_blueprint(logout_bp)
app.register_blueprint(search_bp)
app.register_blueprint(quote_bp)
app.register_blueprint(buy_bp)
app.register_blueprint(sell_bp)
app.register_blueprint(history_bp)
