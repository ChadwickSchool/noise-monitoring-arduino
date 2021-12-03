from __future__ import print_function
import os.path
import os
from re import X
from typing import List
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google.oauth2 import service_account
import datetime
import json

from pyasn1.type.univ import Null

class SheetEditor(object):
    """
    A class used to edit a google spreadsheet

    Attributes
    ----------
    SPREADSHEET_ID : str
        the id of the google spreadsheet
    sheet : googleapiclient.discovery.Resource
        interact with google spreadsheets API

    Methods
    -------
    getNumRows(sheetName)
        Gets the number of rows in a sheet
    autoSheetName()
        Finds or creates a sheet with its name being the current date(mm/dd/yy)
    newSheet(name)
        Creates a new sheet with parameter name
    getSheets(self)
        Gets a list of sheet names from a spreadsheet
    send(self,avgVal,maxVal)
        Writes to a google sheet with name date on the next undedited row
    """

    def __init__(self):
        """

        """

        SCOPES = ['https://www.googleapis.com/auth/spreadsheets']
        SERVICE_ACCOUNT_FILE = os.getenv("SERVICE_ACCOUNT_FILE")
        creds = service_account.Credentials.from_service_account_file(SERVICE_ACCOUNT_FILE, scopes=SCOPES)
        self.SPREADSHEET_ID = '1Gt-uwLcnEuY6wUygzd6ovZx7KOEWHXH22nz9kZkGUV0'
        service = build('sheets', 'v4', credentials=creds)
        self.sheet = service.spreadsheets()

    def getNumRows(self,sheetName):
        """ Gets the number of rows in a sheet

        Gets the number of rows in a sheet by getting a list of all the edited rows and checking the length of the list.

        Parameters
        ----------
        sheetName : str
            the name of the sheet
        """

        result = self.sheet.values().get(
            spreadsheetId=self.SPREADSHEET_ID, range=sheetName).execute()
        rows = result.get('values', [])
        return len(rows)

    def autoSheetName(self):
        """ Finds or creates a sheet with its name being the current date(mm/dd/yy)

        Loops through a list of sheet names and checks if they are the current date. If one is the current date then return.
        Else Create a new sheet with name date and return the date as the name.

        Returns
        -------
        date : str
            the name of the sheet with the current date

        sheetName : str
            the name of the sheet with the current date
        """

        dateNow = datetime.datetime.now()
        date = dateNow.strftime("%x")
        sheetsNames = self.getSheets()
        for sheetName in sheetsNames:
            if sheetName == date:
                return sheetName
        self.newSheet(date)
        return date

    def newSheet(self, name):
        """ Creates a new sheet with parameter name

        Parameters
        ----------
        name : str
            the name of the new sheet
        """

        batch_update_spreadsheet_request_body = {
            'requests': [
                {
                    'addSheet': {
                        'properties': {
                            'title': name,
                            'index': 1
                        }
                    }
                }
            ]
        }
        updateRequest = self.sheet.batchUpdate(spreadsheetId=self.SPREADSHEET_ID, body=batch_update_spreadsheet_request_body)
        updateRequest.execute()

    def indexSheetId(self,sheetIndex):
        """ Gets the sheet id of the sheet at an index
        
        Parameters
        ----------
        sheetIndex: int
            the sheetIndex that you want to find the sheet id of

        Returns
        -------
        sheetId
            the sheetId of the sheet at the input index
        """
        spreadsheet_metadata = self.sheet.get(spreadsheetId=self.SPREADSHEET_ID).execute()
        sheets = spreadsheet_metadata.get('sheets', '')
        sheetId = ""

        for sheet in sheets:
            index = sheet.get("properties", {}).get("index", "Sheet1")
            if(sheetIndex == index):
                sheetId = sheet.get("properties", {}).get("sheetId", "Sheet1")
        return sheetId
        


    def getSheets(self):
        """ Gets a list of sheet names from a spreadsheet

        Returns
        -------
        sheetNames
            a list of strings that are the names of the sheets in a spreadsheet
        """

        spreadsheet_metadata = self.sheet.get(spreadsheetId=self.SPREADSHEET_ID).execute()
        sheets = spreadsheet_metadata.get('sheets', '')
        sheetNames = []
        for x in sheets:
            name = x.get("properties", {}).get("title", "Sheet1")
            sheetNames.append(name)
        return sheetNames

    def addNewChart(self,sheetId, title):
        """ Create an empty chart in a sheet if it does not have a chart 

        Parameters
        ----------
        sheetId
            the sheetId of the sheet to add a chart 
        title
            title of the chart
        """

        batch_update_spreadsheet_request_body = {
            "requests": [
                {
                "addChart": {
                    "chart": {
                    "spec": {
                        "title": title,
                        "basicChart": {
                        "chartType": "LINE",
                        "legendPosition": "BOTTOM_LEGEND",
                        #"axis": [
                         #   {
                          #  "position": "BOTTOM_AXIS",
                           # "title": "Model Numbers"
                            #},
                            #{
                            #"position": "LEFT_AXIS",
                            #"title": "Sales"
                            #}
                        #],
                        "domains": [
                            {
                                "domain": {
                                    "sourceRange": {
                                        "sources": [
                                            {
                                                "sheetId": sheetId,
                                                "startRowIndex": 0,
                                                "endRowIndex": 1000,
                                                "startColumnIndex": 1,
                                                "endColumnIndex": 2
                                            }
                                        ]
                                    }
                                }
                            }
                        ],
                        "series": [
                            {
                                "series": {
                                    "sourceRange": {
                                        "sources": [
                                            {
                                                "sheetId": sheetId,
                                                "startRowIndex": 0,
                                                "endRowIndex": 1000,
                                                "startColumnIndex": 3,
                                                "endColumnIndex": 4
                                            }
                                        ]
                                    }
                                },
                                "targetAxis": "LEFT_AXIS",
                                "dataLabel": {
                                    "type": "NONE",
                                    "textFormat": {
                                        "fontFamily": "Roboto"
                                    }
                                }
                            },
                            {
                                "series": {
                                    "sourceRange": {
                                        "sources": [
                                            {
                                                "sheetId": sheetId,
                                                "startRowIndex": 0,
                                                "endRowIndex": 1000,
                                                "startColumnIndex": 5,
                                                "endColumnIndex": 6
                                            }
                                        ]
                                    }
                                },
                                "targetAxis": "LEFT_AXIS"
                            }
                        ],
                        "headerCount": 0
                        }
                    },
                    "position": {
                        "overlayPosition": {
                           "anchorCell": {
                                "sheetId": sheetId,
                                "rowIndex": 5,
                                "columnIndex": 7
                            },
                            "offsetXPixels": 0,
                            "offsetYPixels": 0,
                            "widthPixels": 0,
                            "heightPixels": 0 
                        }
                    }
                    }
                }
                }
            ]
            }    

        spreadsheet_metadata = self.sheet.get(spreadsheetId=self.SPREADSHEET_ID).execute()
        sheets = spreadsheet_metadata.get('sheets', '')
        for sheet in sheets:
            if(sheet.get("properties", {}).get("sheetId", "Sheet1") == sheetId):
                currentSheet = sheet    

        if currentSheet.get("charts", {}) == {}: # if the sheet does not have a chart then make a chart
            updateRequest = self.sheet.batchUpdate(spreadsheetId=self.SPREADSHEET_ID, body=batch_update_spreadsheet_request_body)
            updateRequest.execute()
            print("no chart creating one")

    def getJsonStuff(self):
        """get json stuff
        
        """
        spreadsheet_metadata = self.sheet.get(spreadsheetId=self.SPREADSHEET_ID).execute()
        sheets = spreadsheet_metadata.get('sheets', '')
        charts = []
        for x in sheets:
            name = x.get("charts", {})
            print(json.dumps(name, indent=4))
            print("")
        


    def send(self,avgVal,maxVal):
        """ Writes to a google sheet with name date on the next undedited row

        Writes to a google spreadsheet and willl check if it has a sheet with a name of the current date(mm/dd/yy)
        and then writes the peramaters in a the next unedited row.

        Parameters
        ----------
        avgVal : str
            the input for writing to the avg col
        maxVal : str
            the input for writing to the max col
        """

        d = datetime.datetime
        val = [["Time", d.now().strftime("%X"), "avg",avgVal, "max",maxVal]]
        currentSheetName = self.autoSheetName()
        numRows = self.getNumRows(currentSheetName)
        self.addNewChart(self.indexSheetId(1),currentSheetName)
        rowToWrite = numRows + 1
        rangeToWrite = currentSheetName + "!A" + str(rowToWrite)
        self.sheet.values().update(
            spreadsheetId=self.SPREADSHEET_ID, range=rangeToWrite,
            valueInputOption="USER_ENTERED", body={"values":val}).execute()
        print("end")
