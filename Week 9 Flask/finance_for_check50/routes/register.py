from flask import render_template, request, flash, redirect, Blueprint, current_app
from helpers import apology
from werkzeug.security import generate_password_hash

bp = Blueprint("register", __name__)

@bp.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    db = current_app.config['db']

    # print('> print ehe:', generate_password_hash('ehe'))
    # app.logger.info('> log ehe:' + generate_password_hash('ehe'))

    if request.method == 'GET':
        return render_template('register.html')
    
    elif request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        confirmation = request.form.get('confirmation')
        
        # missing username
        if not username:
            return apology("Username not found")
        
        # username exists
        users = db.execute("SELECT username FROM users WHERE username = ?", username)
        # print('\n>> user:\n', user)
        
        if len(users) > 0 and users[0].get('username') == username:
            return apology("Username exists")
            
        # either password is blank or the passwords do not match
        if not password or not confirmation or password != confirmation:
            return apology("Password error")
            
        insert_res = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        
        if insert_res is None:
            return apology("Insert user error", 500)
        
        # print('>> ', username, password, confirmation)
        flash('Registered successfully!')
        return redirect('/login')