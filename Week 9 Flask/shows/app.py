# Searches for shows using Ajax with JSON

from cs50 import SQL
from flask import Flask, jsonify, render_template, request

app = Flask(__name__)

db = SQL("sqlite:///shows.db")


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/search")
def search():
    q = request.args.get("q")
    
    if q:
        if q == '*':
            shows = db.execute('SELECT * FROM shows LIMIT 1000')
        else:
            shows = db.execute("SELECT * FROM shows WHERE title LIKE ? LIMIT 50", "%" + q + "%")
    else:
        shows = []
        
    for show in shows:
        print('>>', show)
        
    # sending back as json (API like)
    # return jsonify(shows)
    
    # now this endpoint will return an HTML template
    # turn this from client-side rendering to server-side rendering
    return render_template("search.html", shows=shows)
