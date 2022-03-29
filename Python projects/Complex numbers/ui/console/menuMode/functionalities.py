import os
import sys
sys.path.append(os.getcwd() + "\\")
from domain.complex_list_manager_class import complex_list_to_imaginary_text, complex_list_to_text, delete_all_compared_to_number_and_sign, get_module_equal_10, get_module_less_than_10, get_product_over_subsequence, get_sum_over_subsequence, add_complex_number
from domain.complex_number_class import NrComplex, first_smaller_imaginary, real_part_prime
from utils.utils import get_all_without_property, get_subsequence, replace_all_appearances, sort


def read_index(limitdown, limitup, message):
    """citeste un index in intervalul [limitdown, limitup] afisand mesajul

    Parameters
    ----------
    limitdown : int
        [
    limitup : int
        ]
    message : str
        mesajul care sa fie afisat la citire

    Returns
    -------
    int
        indexul dorit

    Raises
    ------
    ValueError
        daca nu se introduce ce trebuie atunci repeta citirea
    """
    try:
        index = int(input(message))
        if index < limitdown or index > limitup:
            raise ValueError
        return index
    except ValueError:
        print("Respecta intervalul dat!!")
        return read_index(limitdown, limitup, message)
def read_interval(limitdown, limitup, message):
    """citeste 2 numere a<b cu propr a, b apartin [limitdown, limitup]

    Parameters
    ----------
    limitdown : int
        [
    limitup : int
        ]
    message : str
        mesajul care se va afisa

    Returns
    -------
    (int, int)
        cei 2 indexi

    Raises
    ------
    ValueError
        daca nu se introduc datele in mod corect, at se va repeta citirea
    """
    try:
        text = input(message)
        limits = text.split()

        start = int(limits[0])
        final = int(limits[1])
        if start < limitdown or start > final or final > limitup:
            raise ValueError
        return (start, final)
    except ValueError:
        print("Respecta intervalul dat si pune limitele in ordine crescatoare!!")
        return read_interval(limitdown, limitup, message)
    except IndexError:
        print("Pune 2 numere reprezentand limitele intervalului!!")
        return read_interval(limitdown, limitup, message)
def read_complex_number(message = "->Introduceti un numar complex sub forma a+bi: "):
    """afiseaza un mesaj utilizatorului si citeste un numar complex

    Parameters
    ----------
    message : str, optional
        mesajul pentru utilizator, by default "->Introduceti un numar complex sub forma a+bi: "

    Returns
    -------
    tuple
        un numar complex cu partea intreaga pe prima poz si partea imaginara pe a doua poz
    """
    try:
        text = input(message)
        if text == "":
            raise ValueError()
        return NrComplex(text = text)
    except ValueError:
        print("Adauga numarul complex sub forma ceruta!!")
        return read_complex_number(message)
    except IndexError:
        print("Adauga numarul complex sub forma ceruta!!")
        return read_complex_number(message)


def ui_adauga_la_final(myListManager):
    newel = read_complex_number()
    add_complex_number(myListManager, newel)
    print("Numarul a fost adaugat cu succes. Lista actuala este: ")
    text = complex_list_to_text(myListManager.getList())
    print(text)
    input("press enter to continue...")
def ui_adauga_in_pozitie(myListManager):
    newel = read_complex_number()
    message = "->Dati indexul (1->" + str(len(myListManager.getList())+1) + ") la care sa fie inserat numarul imaginar: "
    index = read_index(1, len(myListManager.getList())+1, message) - 1
    add_complex_number(myListManager, newel, index)
    print("Numarul a fost adaugat cu succes. Lista actuala este: ")
    text = complex_list_to_text(myListManager.getList())
    print(text)
    input("press enter to continue...")

def ui_parte_imaginara_subsecventa(myListManager):
    message = "->Dati limitele intervalului (1->"+str(len(myListManager.getList())) + ") pentru care sa se afiseze partea imaginara: "

    (start, final) = read_interval(1, len(myListManager.getList()), message)
    subsequnce = get_subsequence(myListManager.getList(), start-1, final-1)

    print("Partile imaginare ale numerelor din interiorul intervalul sunt: ")
    
    text = complex_list_to_imaginary_text(subsequnce)
    print(text)
    input("press enter to continue...")
def ui_module_less_than_10(myListManager):
    result = get_module_less_than_10(myListManager)
    print("Numerele complexe care au modulul mai mic decat 10 sunt: ")
    text = complex_list_to_text(result)
    print(text)
    input("press enter to continue...")
def ui_get_module_equal_10(myListManager):
    result = get_module_equal_10(myListManager)
    print("Numerele complexe care au modulul egal cu 10 sunt: ")
    text = complex_list_to_text(result)
    print(text)
    input("press enter to continue...")

def ui_delete_in_pos(myListManager):
    message = "->Dati pozitia (1->" + str(len(myListManager.getList())) + ") de pe care sa fie sters elementul: "
    position = read_index(1, len(myListManager.getList()), message) - 1
    myListManager.pop(position)
    print("Elementul a fost sters. Lista actuala este: ")
    text = complex_list_to_text(myListManager.getList())
    print(text)
    input("press enter to continue...")
def ui_delete_interval(myListManager):
    message = "->Dati limitele intervalului (1->"+str(len(myListManager.getList())) + ") de pe care sa fie sterse elementele: "
    (start, final) = read_interval(1, len(myListManager.getList()), message)
    
    myListManager.delete((start-1), final)

    print("Elementele au fost sterse. Lista actuala este: ")
    text = complex_list_to_text(myListManager.getList())
    print(text)
    input("press enter to continue...")  
def ui_replace_all_appearances(myListManager):
    this = read_complex_number("->Dati numarul complex care sa fie inlocuit: ")
    that = read_complex_number("->Dati numarul complex cu care sa fie inlocuit: ")

    newlist = replace_all_appearances(myListManager.getList(), this, that)
    if newlist == myListManager.getList():
        print("Numarul ", end="")
        print(this, end="")
        print(" nu exista in lista.")
        input("press enter to continue...")
    else:
        myListManager.setList(newlist)
        print("Numarul a fost inlocuit cu succes. Lista actuala este: ")
        text = complex_list_to_text(myListManager.getList())
        print(text)
        input("press enter to continue...")

def ui_get_sum_over_subsequence(myListManager):
    message = "->Dati limitele intervalului (1->"+str(len(myListManager.getList())) + "): "

    start, final = read_interval(1, len(myListManager.getList()), message)
    result = get_sum_over_subsequence(myListManager, start-1, final-1)

    print("Suma numerelor din subsecventa este: ")
    print(result, end="")
    print()
    input("press enter to continue...")  
def ui_get_product_over_subsequence(myListManager):
    message = "->Dati limitele intervalului (1->"+str(len(myListManager.getList())) + "): "

    start, final = read_interval(1, len(myListManager.getList()), message)
    result = get_product_over_subsequence(myListManager, start-1, final-1)

    print("Produsul numerelor din subsecventa este: ")
    print(result, end="")
    print()
    input("press enter to continue...")
def ui_sorted_list(myListManager):
    mylist = myListManager.getList()
    sort(mylist, first_smaller_imaginary)
    print("Lista sortata descrescator dupa partea imaginara este: ")
    text = complex_list_to_text(mylist)
    print(text)
    input("press enter to continue...")

def ui_filter_prime_numbers(myListManager):
    lenStart = len(myListManager.getList())
    newList = get_all_without_property(myListManager.getList(), real_part_prime)
    myListManager.setList(newList)
    lenAfter = len(myListManager.getList())
    if lenStart == lenAfter:
        print("Nu exista numere cu partea reala numar prim.")
    else:
        print("Filtrarea numerelor s-a realizat cu succes. Lista actuala este: ")
        text = complex_list_to_text(myListManager.getList())
        print(text)
    input("press enter to continue...")
def ui_filter_module_sign(myListManager):
    try:
        text = input("->Introduceti semnul(<, >, =) si numarul cu care se va face comparatia: ")
        words = text.split()
        sign = words[0]
        number = int(words[1])
        if sign != "<" and sign != ">" and sign != "=":
            raise ValueError
        
        lenStart = len(myListManager.getList())
        delete_all_compared_to_number_and_sign(myListManager, number, sign)
        lenAfter = len(myListManager.getList())
        if lenStart == lenAfter:
            print("Nu exista numere cu proprietatea data.")
        else:
            print("Filtrarea numerelor s-a realizat cu succes. Lista actuala este: ")
            text = complex_list_to_text(myListManager.getList())
            print(text)
        input("press enter to continue...")
    except ValueError:
        ui_filter_module_sign(myListManager.getList())
    except IndexError:
        ui_filter_module_sign(myListManager.getList())

def ui_undo(myListManager):
    try:
        myListManager.undo()
        print("Ultima operatie a fost resetata cu succes! Lista actuala este: ")
        text = complex_list_to_text(myListManager.getList())
        print(text)
        input("press enter to continue...")  
    except IndexError:
        print("Nu s-a putut efectua operatia de undo!")
        input("press enter to continue...")  

def ui_redo(myListManager):
    try:
        myListManager.redo()
        print("Ultima operatie undo a fost resetata cu succes! Lista actuala este: ")
        text = complex_list_to_text(myListManager.getList())
        print(text)
        input("press enter to continue...")  
    except IndexError:
        print("Nu s-a putut efectua operatia de redo!")
        input("press enter to continue...")  


