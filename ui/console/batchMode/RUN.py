import os
import sys
sys.path.append(os.getcwd() + "\\")
from domain.complex_list_manager_class import ListManager, generated_list, add_complex_number, complex_list_to_text
from domain.complex_number_class import NrComplex


def tryCommandAdd(myListManager, cuv1, cuv2):
    try:
        text = cuv1
        if text == "":
            raise ValueError()
        mynr = NrComplex(text = text)
        try:
            newel = mynr
            index = int(cuv2)
            if index < 0 or index > len(myListManager.getList()):
                raise ValueError()
            add_complex_number(myListManager, newel, index)
            print("Numarul a fost adaugat cu succes.")
            return
        except ValueError:
            print("Nu respecta intervalul.")
            return
    except ValueError:
        print("Numarul complex nu are forma ceruta.")
        return
    except IndexError:
        print("Adauga numarul complex sub forma ceruta!!")
        return
def tryCommandDelete(myListManager, cuv1, cuv2):
    try:
        start = int(cuv1)
        final = int(cuv2)
        if start < 0 or start > final or final > len(myListManager.getList()):
            raise ValueError()

        myListManager.delete(start, final+1)
        print("Elementele au fost sterse.")
        return
    except ValueError:
        print("Pozitiile nu respecta intervalul dat sau nu sunt in ordine crescatoare.")
        return
    except IndexError:
        print("Pozitiile nu respecta intervalul dat.")
        return
def tryCommandPrint(myListManager):
    print("Lista actuala este: ")
    text = complex_list_to_text(myListManager.getList())
    print(text)
def tryCommandUndo(myListManager):
    try:
        myListManager.undo()
        print("Ultima operatie a fost resetata cu succes!")
        return
    except IndexError:
        print("Nu s-a putut efectua operatia de undo!")
        return

menuCommands = {
    "add" : (tryCommandAdd, 2),
    "delete" : (tryCommandDelete, 2),
    "print" : (tryCommandPrint, 0),
    "undo" : (tryCommandUndo, 0),
}

def runBatchMode():
    myListManager = ListManager()
    if __name__ == '__main__':
        myListManager = ListManager(generated_list)
    while True:
        print("Operatii posibile: add nrComplex pos; print; delete pos1 pos2; undo; SAU scrie 'end' pentru a inchide.")
        commands = input("Introduceti lista de comenzi separate prin punct si virgula: ")
        if commands == "end":
            break
        v = commands.split("; ")
        for el in v:
            vars = el.split(" ")
            if vars[0] in menuCommands:
                if len(vars) - 1 != menuCommands[vars[0]][1]:
                    print("Prea putini parametrii pentru comanda " + vars[0])
                else:
                    if vars[0] == "add" or vars[0] == "delete":
                        menuCommands[vars[0]][0](myListManager, vars[1], vars[2])
                    else:
                        menuCommands[vars[0]][0](myListManager)
            else:
                print("Functie gresita.")

if __name__ == '__main__':
    runBatchMode()
    
