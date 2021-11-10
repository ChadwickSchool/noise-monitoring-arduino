from __future__ import print_function
import os.path
import os
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google.oauth2 import service_account
import datetime

class SheetEditor(object):
    def __init__(self):
        self.SCOPES = ['https://www.googleapis.com/auth/spreadsheets']
        self.SERVICE_ACCOUNT_FILE = 'creds/keysNew.json'
        self.creds = service_account.Credentials.from_service_account_file(
        self.SERVICE_ACCOUNT_FILE, scopes=self.SCOPES)
        self.SAMPLE_SPREADSHEET_ID = '1Gt-uwLcnEuY6wUygzd6ovZx7KOEWHXH22nz9kZkGUV0'
        self.SAMPLE_RANGE_NAME = "10/27/2021!A3" 
        self.service = build('sheets', 'v4', credentials=self.creds)
        self.sheet = self.service.spreadsheets()
  
    def send(self,avgVal,maxVal):
        val = [["value",avgVal, "value",maxVal]]
        request = self.sheet.values().update(
            spreadsheetId=self.SAMPLE_SPREADSHEET_ID, range=self.SAMPLE_RANGE_NAME,
            valueInputOption="USER_ENTERED", body={"values":val}).execute()
        print("end") 
