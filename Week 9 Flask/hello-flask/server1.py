# if running a different file name, use `flask --app server1 run`

from flask import Flask, render_template, request

app = Flask(__name__)


@app.route('/')
def index():
    return "Hello from server 1 file :D"
