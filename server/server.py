from flask import Flask, request
from werkzeug.utils import send_file, send_from_directory
from sheetEditor import SheetEditor
from sheetEditor.sound_Data import soundData
import datetime

 
obj = SheetEditor()
lotsOfData = []


app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"

@app.route("/update-sheet")
def update_sheet():
    requestArgs = request.args
    # class with time, avg, and max
    # add class to a list 
    # after x many are in a list 
    # then send that list to google(kinda)
    # for each element in the list needs to be turned into an array of time, avg, max
    # then send 2D array as val to updatespreadhseet body 
    # send data

    d = datetime.datetime
    sentData = soundData(d.now().strftime("%X"), requestArgs["avg"], requestArgs["max"])
    lotsOfData.append(sentData)
    if(len(lotsOfData) > 10):
        obj.send(lotsOfData)
        lotsOfData.clear()
    
    return f"Done: {requestArgs}\n"