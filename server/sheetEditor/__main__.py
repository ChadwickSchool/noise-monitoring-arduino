from os import wait
from re import S
from sheetEditor import SheetEditor
from sheetEditor.sound_Data import soundData
#from sheetEditor import readRange

def main():
    """A fucntions that is used to test methonds in an SheetEditor object 
    
    Write and comment in or out methonds that you are testing. 

    """
    obj = SheetEditor()
    sendData = soundData(12, 10, 11)
    testSendDataList = []

    i = 0
    while(i < 10):
        testSendDataList.append(sendData)
        i = i + 1
    #print(sendData.get_average())
    #obj.makeVal(testSendDataList)

    #print(sendData.get_time())
    #obj.send(testSendDataList)
    #obj.getNumRows("12/03/21")
    #obj.getSheets()
    #obj.autoSheetName()
    #obj.newSheet("lol")
    #obj.getSpreadSheetData()
    #obj.addNewChart(0 , "bleh")
    #obj.indexSheetId()
    obj.getJsonStuff()


if __name__ == "__main__":
    main()
    