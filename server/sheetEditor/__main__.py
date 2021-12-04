from os import wait
from sheetEditor import SheetEditor
#from sheetEditor import readRange

def main():
    obj = SheetEditor()
    obj.send(10, 9001)
    obj.send(11, 9002)
    #obj.getNumRows("12/03/21")
    #obj.getSheets()
    #obj.autoSheetName()
    #obj.newSheet("lol")
    #obj.getSpreadSheetData()
    #obj.addNewChart(0 , "bleh")
    #obj.indexSheetId()
    #obj.getJsonStuff()


if __name__ == "__main__":
    main()
    