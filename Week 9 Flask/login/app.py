# use `python3 -m flask run --debug` to run this file

from flask import Flask, redirect, render_template, request, session
from flask_session import Session

# Configure app
app = Flask(__name__)

# Configure session

# configures Flask sessions to be non-permanent,
# meaning they will expire when the user closes their browser
# If it were True, sessions would persist across browser sessions until they reach their configured lifetime limit
app.config["SESSION_PERMANENT"] = True


# store session data on the server's filesystem rather than in browser cookies
#   - Session data is saved as files on the server's disk
#   - Only a session ID is stored in the user's browser cookie
app.config["SESSION_TYPE"] = "filesystem"

# add Server-side Session to Flask application
Session(app)


@app.route("/")
def index():
    return render_template("index.html", name=session.get("name"))


@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        # always create a new session in the filesystem (folder flask_session)
        session["name"] = request.form.get("name")
        print('> session:', session)
        
        return redirect("/")
    
    # GET
    return render_template("login.html")


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")