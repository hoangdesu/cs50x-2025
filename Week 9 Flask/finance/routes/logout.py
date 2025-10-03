from flask import flash, redirect, session

# shared instances
from app import app, db


@app.route("/logout")
def logout():
    """Log user out"""
    flash(f'Goodbye {session["user_name"]}!')

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/login")