from flask import Flask, request

app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"

@app.route("/update-sheet")
def update_sheet():
    requestArgs = request.args
    print(requestArgs['x'])
    return f"Done: {requestArgs}\n"