import os
import sys
sys.path.append(os.getcwd() + "\\")
from ui.console.menuMode.RUN import runNormalMode
from ui.console.batchMode.RUN import runBatchMode

menuConsole = {
    "1": (runNormalMode, "1. Ruleaza in mod normal aplicatia."),
    "2": (runBatchMode,  "2. Ruleaza in batch mode aplicatia."),
}

def print_menu():
    for val in menuConsole.values():
        print(val[1])

def run():
    while True:
        print_menu()
        menu_choice = input("Alege un mod de rulare: ")
        if menu_choice in menuConsole:
            menuConsole[menu_choice][0]()
            break
        
