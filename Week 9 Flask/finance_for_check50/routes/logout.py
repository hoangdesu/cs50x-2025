from flask import flash, redirect, session, Blueprint

bp = Blueprint("logout", __name__)

@bp.route("/logout")
def logout():
    """Log user out"""
    flash(f'Goodbye {session["user_name"]}!')

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/login")