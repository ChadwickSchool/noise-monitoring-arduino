import re
from flask import Flask, request
from werkzeug.utils import send_file, send_from_directory
from sheetEditor import SheetEditor
from sheetEditor.sound_Data import soundData
from queue import Queue
import datetime
import time
import threading

class RequestProcessor(object):
    def process_requests():
        print("Request Process is Starting")
        listOfData = []
        while True: 
            if(requestQueue.empty() != True):
                listOfData.append(requestQueue.get())
                if(len(listOfData) > 100):
                    obj.send(listOfData)
                    listOfData.clear()
            else:
                time.sleep(10)

    # Else sleep for 0.5 seconds
    ## Takes one request off the queue and processes it

processThread = threading.Thread(target=RequestProcessor.process_requests)


    

obj = SheetEditor()
requestQueue = Queue()

app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"

@app.route("/update-sheet")
def update_sheet():
    if not processThread.is_alive():
        processThread.start()
    # TODO: Add request to a queue
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
    requestQueue.put(sentData)
    return f"Done: {requestArgs}\n"


