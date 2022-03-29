import os
import sys
sys.path.append(os.getcwd() + "\\")
from ui.console.menuMode.functionalities import *

submenu_adauga = {
    "1": (ui_adauga_la_final, "1. Adaugă număr complex la sfârșitul listei."),  
    "2": (ui_adauga_in_pozitie, "2. Inserare număr complex pe o poziție anume."),
    "back": ("-", "back. Revino la meniul principal."),
    "end": ("-", "end. Inchide aplicatia."),
}
submenu_tip = {
    "1": (ui_parte_imaginara_subsecventa, "1. Tipărește partea imaginara pentru numerele din listă. Se dă intervalul de poziții (sub secvența)."),
    "2": (ui_module_less_than_10, "2. Tipărește toate numerele complexe care au modulul mai mic decât 10."),
    "3": (ui_get_module_equal_10, "3. Tipărește toate numerele complexe care au modulul egal cu 10."),
    "back": ("-", "back. Revino la meniul principal."),
    "end": ("-", "end. Inchide aplicatia."),
}
submenu_filtrare = {
    "1": (ui_filter_prime_numbers, "1. Filtrarea numerelor complexe cu partea reala numar prim."),
    "2": (ui_filter_module_sign, "2. Filtrare modul – elimina din lista numerele complexe la care modulul este <, = sau > decât un număr dat."),
    "back": ("-", "back. Revino la meniul principal."),
    "end": ("-", "end. Inchide aplicatia."),
}
submenu_delete = {
    "1": (ui_delete_in_pos, "1. Șterge element de pe o poziție dată."),
    "2": (ui_delete_interval, "2. Șterge elementele de pe un interval de poziții."),
    "3": (ui_replace_all_appearances, "3. Înlocuiește toate aparițiile unui număr complex cu un alt număr complex."),
    "back": ("-", "back. Revino la meniul principal."),
    "end": ("-", "end. Inchide aplicatia."),
}
submenu_operatie = {
    "1": (ui_get_sum_over_subsequence, "1. Suma numerelor dintr-o subsecventă dată (se da poziția de început și sfârșit)."),
    "2": (ui_get_product_over_subsequence , "2. Produsul numerelor dintr-o subsecventă dată (se da poziția de început și sfârșit)."),
    "3": (ui_sorted_list, "3. Tipărește lista sortată descrescător după partea imaginara."),
    "back": ("-", "back. Revino la meniul principal."),
    "end": ("-", "end. Inchide aplicatia."),
}


menu_submenus = {
    "1": (submenu_adauga, "1. Adauga un numar complex in lista."),
    "2": (submenu_delete, "2. Modifică elemente din listă."),
    "3": (submenu_tip, "3. Cautare numere in lista."),
    "4": (submenu_operatie, "4. Operații cu numerele din listă."),
    "5": (submenu_filtrare, "5. Filtrare."),
    "undo": ("-", "undo. Reseteaza ultima operatie."),
    "redo": ("-", "redo. Anuleaza ultima operatie undo."),
    "end": ("-", "end. Inchide aplicatia."),
}

def print_menu():
    """afiseaza meniul principal (care continue submeniuri)
    """
    for val in menu_submenus.values():
        print(val[1])
def print_sub_menu(f):
    """printeaza submeniul de pe pozitia f

    Parameters
    ----------
    f : int
        pozitia submeniului ales
    """
    print(menu_submenus[f][1][3:])
    for val in menu_submenus[f][0].values():
        print("    ", end="")
        print(val[1])