import os
import sys

sys.path.append(os.getcwd() + "\\")
from domain.complex_list_manager_class import ListManager, complex_list_to_text, generated_list
from ui.console.menuMode.menu import print_menu, print_sub_menu, menu_submenus
from ui.console.menuMode.functionalities import ui_redo, ui_undo

def runNormalMode():
    myListManager = ListManager()

    if __name__ == '__main__':
        myListManager = ListManager(generated_list)

    while True:
        os.system('cls')
        text = complex_list_to_text(myListManager.getList())
        print(text)
        print_menu()
        menu_choice = input("Alege o functionalitate: ")
        if menu_choice == "end":
            print("Bye!")
            return 0
        elif menu_choice == "undo":
            ui_undo(myListManager)
        elif menu_choice == "redo":
            ui_redo(myListManager)
        elif menu_choice in menu_submenus:
            while True:
                os.system('cls')
                text = complex_list_to_text(myListManager.getList())
                print(text)
                print_sub_menu(menu_choice)
                submenu_choice = input("Alege o optiune: ")
                if submenu_choice == "back":
                    break
                elif submenu_choice == "end":
                    print("Bye!")
                    return 0
                elif submenu_choice in menu_submenus[menu_choice][0]:
                    os.system('cls')
                    text = complex_list_to_text(myListManager.getList())
                    print(text)
                    print(menu_submenus[menu_choice][0][submenu_choice][1][3:])
                    menu_submenus[menu_choice][0][submenu_choice][0](myListManager)

if __name__ == '__main__':
    runNormalMode()

