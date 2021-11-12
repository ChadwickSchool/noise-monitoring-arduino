from sheetEditor import SheetEditor
#from sheetEditor import readRange

def main():
    obj = SheetEditor()
    obj.send(10, 9001)
    #obj.getNumRows("11/12/21")
    #obj.getSheets()
    #obj.autoSheetName()
    #obj.newSheet("lol")

if __name__ == "__main__":
    main()
    