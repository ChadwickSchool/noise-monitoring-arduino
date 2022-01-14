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
    """
    A class used to proces requests in a thread safe enviroment. 

    Methods
    -------
    process_requests()
        process sent data from arduino
    """

    def process_requests():
        """ Checks if there are any requests to process then batches and sends them

        Checks a thread safe queue if it has requests to process then batches the requests into a list and
        after a set number of requetsts are in the list it will send. 

        
        """
        listOfData = []
        while True: 
            if(requestQueue.empty() != True):
                listOfData.append(requestQueue.get())
                if(len(listOfData) > 50):
                    obj.send(listOfData)
                    listOfData.clear()
            else:
                time.sleep(10)

processThread = threading.Thread(target=RequestProcessor.process_requests)


obj = SheetEditor()
requestQueue = Queue()

app = Flask(__name__)


@app.route("/")
def hello_world():
    """ 
    Returns "Hello, World!" when calling the sever with out any other route.
    """
    return "<p>Hello, World!</p>"

@app.route("/update-sheet")
def update_sheet():
    """ Location to send data useing get requests.

    When starting up for the first time checks if there is a thread for the queue and if there isn't creates one.
    Agruments are passed in throught the url and formated into a class that stores the arguments and the time.
    the data is then passed into a queue.
    
    # class with time, avg, and max
    # add class to a list 
    # after x many are in a list 
    # then send that list to google(kinda)
    # for each element in the list needs to be turned into an array of time, avg, max
    # then send 2D array as val to updatespreadhseet body 
    # send data

    """
    if not processThread.is_alive():
        processThread.start()
    # TODO: Add request to a queue
    requestArgs = request.args
    d = datetime.datetime
    sentData = soundData(d.now().strftime("%H:%M:%S.%f"), requestArgs["avg"], requestArgs["max"])
    requestQueue.put(sentData)
    return f"Done: {requestArgs}\n"


