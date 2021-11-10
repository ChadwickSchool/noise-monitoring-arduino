from __future__ import print_function
import os.path
import os
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google.oauth2 import service_account
import datetime

def send(average, maximum):
    SCOPES = ['https://www.googleapis.com/auth/spreadsheets']
    SERVICE_ACCOUNT_FILE = os.getenv("SERVICE_ACCOUNT_FILE") # 'creds/keys.json'
    creds = None 
    creds = service_account.Credentials.from_service_account_file(
        SERVICE_ACCOUNT_FILE, scopes=SCOPES)
    SAMPLE_SPREADSHEET_ID = '1Gt-uwLcnEuY6wUygzd6ovZx7KOEWHXH22nz9kZkGUV0'
    # need to change the sheet and the range here maybe?
    SAMPLE_RANGE_NAME = "10/27/2021!A3"
    service = build('sheets', 'v4', credentials=creds)
    sheet = service.spreadsheets()
    date = datetime.datetime.now()
    val = [["value",average, "value",maximum]]
    #val = [["value",average],["value",maximum]]
    request = sheet.values().update(
        spreadsheetId=SAMPLE_SPREADSHEET_ID, range=SAMPLE_RANGE_NAME,
        valueInputOption="USER_ENTERED", body={"values":val}).execute()
    print("end") 
