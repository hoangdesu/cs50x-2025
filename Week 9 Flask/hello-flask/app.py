# `flask run` will run this app.py by default
# `flask run --debug` for hot reload

from flask import Flask, render_template, request
from datetime import datetime

app = Flask(__name__)

# - Context processors are functions that run before every request and inject variables into the template context, making them available to all templates rendered in the application. 
# - This is useful for data that needs to be globally available, such as navigation menus, user information, or site-wide settings.
@app.context_processor
def inject_global_data():
    navs = [
        {
            'url': '/',
            'text': 'Home'
        },
        {
            'url': '/say-hi',
            'text': 'Say Hi'
        },
        {
            'url': '/wassup',
            'text': 'Wassup'
        },
        {
            'url': '/login',
            'text': 'Login'
        },
    ]
    
    current_time = datetime.now()
    print(current_time)
    return dict(navs=navs, current_time=current_time)


@app.route('/')
def index():
    return 'Hello Flask :D'


@app.route('/hi')
def hi():
    return '<h1>Hi!!</h1>'


# http://127.0.0.1:5000/wassup?name=hoang
@app.route('/wassup')
def wassup():
    # - By default, the request.args.get function will look for the name being provided by the user in request params. 
    # - If no name is provided, it will default to bro
    name = request.args.get('name', 'bro')
    name = 'bro' if name == '' else name
    
    # - template files are placed in /templates folder by default. no need to add it to path
    # - template expect a key "name" to be passed in
    return render_template('wassup.html', name=name)


@app.route('/say-hi')
def say_hi():
    return render_template('say-hi.html')
    

# Path param
@app.route('/user/<name>')
def get_user(name):
    if name == 'admin':
        return '<h1>Admin page</h1>'
    else: 
        return f'User page: {name}'
    
    
# Handle multiple methods on the same route
@app.route('/login', methods=['GET', 'POST'])
def login():
    # handle each method in an if block :s
    if request.method == 'GET':
        return render_template('login.html')
    
    elif request.method == 'POST':
        print('>> POST /login')
        # print(request.form)

        # - request.form is a dict used to store all fields sent from a form
        # - looks sth like this: ImmutableMultiDict([('username', 'a'), ('password', 'b')])
        username = request.form.get('username')
        password = request.form.get('password')
        if username == 'cun' and password == 'hehe':
            return 'Login success!'
        
        return 'Login failed :('