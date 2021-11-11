from __future__ import print_function
import os.path
import os
from re import X
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google.oauth2 import service_account
import datetime

class SheetEditor(object):
    def __init__(self):
        self.SCOPES = ['https://www.googleapis.com/auth/spreadsheets']
        self.SERVICE_ACCOUNT_FILE = os.getenv("SERVICE_ACCOUNT_FILE")
        self.creds = service_account.Credentials.from_service_account_file(
        self.SERVICE_ACCOUNT_FILE, scopes=self.SCOPES)
        self.SPREADSHEET_ID = '1Gt-uwLcnEuY6wUygzd6ovZx7KOEWHXH22nz9kZkGUV0'
        self.SAMPLE_RANGE_NAME = "10/27/2021!A3" #this needs to be dynamic not static # this needs to be gone 
        self.service = build('sheets', 'v4', credentials=self.creds)
        self.sheet = self.service.spreadsheets()
  
    def getNumRows(self,sheetName):
        result = self.sheet.values().get(
            spreadsheetId=self.SPREADSHEET_ID, range=sheetName).execute()
        rows = result.get('values', [])
        return len(rows)

    def autoSheetName(self):
        dateNow = datetime.datetime.now()
        date = dateNow.strftime("%x")
        sheetsNames = self.getSheets()
        for sheetName in sheetsNames:
            if sheetName == date:
                return sheetName

        #need to creat new sheet here with name date only here if a sheet doesn't exist 
        return date

    def getSheets(self):
        spreadsheet_metadata = self.sheet.get(spreadsheetId=self.SPREADSHEET_ID).execute()
        sheets = spreadsheet_metadata.get('sheets', '')
        sheetNames = []
        for x in sheets:
            name = x.get("properties", {}).get("title", "Sheet1")
            sheetNames.append(name)
        return sheetNames
            
    def send(self,avgVal,maxVal):
        val = [["avg",avgVal, "max",maxVal]]
        currentSheetName = self.autoSheetName()
        numRows = self.getNumRows(currentSheetName)
        rowToWrite = numRows + 1
        RANGE = currentSheetName + "!A" + str(rowToWrite)
        self.sheet.values().update(
            spreadsheetId=self.SPREADSHEET_ID, range=RANGE,
            valueInputOption="USER_ENTERED", body={"values":val}).execute()
        print("end") 

