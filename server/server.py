from flask import Flask, request
from sheetEditor import send

app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"


# curl "http://127.0.0.1:5000/update-sheet?avg=7&max=2"

@app.route("/update-sheet")
def update_sheet():
    requestArgs = request.args
    print(requestArgs["avg"])
    print(requestArgs["max"])

    send(requestArgs["avg"],requestArgs["max"])

    return f"Done: {requestArgs}\n"