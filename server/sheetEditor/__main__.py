from sheetEditor import SheetEditor
#from sheetEditor import readRange

def main():
    obj = SheetEditor()
    obj.send(10, 9001)
    #obj.getNumRows()
    #obj.getSheets()
    #obj.autoSheetName()

if __name__ == "__main__":
    main()
    