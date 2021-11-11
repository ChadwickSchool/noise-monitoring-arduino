from flask import Flask, request
from sheetEditor import SheetEditor

obj = SheetEditor()

app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"

@app.route("/update-sheet")
def update_sheet():
    requestArgs = request.args
    obj.send(requestArgs["avg"],requestArgs["max"])
    return f"Done: {requestArgs}\n"