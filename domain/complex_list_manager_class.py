import os
import sys
sys.path.append(os.getcwd() + "\\")
from utils.utils import get_all_without_property, get_subsequence, copy_list, copy_list_list
from domain.complex_number_class import NrComplex

class ListManager():
    def __init__(self, list=[], undo_list=[], redo_list=[]):
        """initializeaza managerul unei listei care contine si lista de unde si redo

        Parameters
        ----------
        list : list, optional
            lista curenta, by default []
        undo_list : list, optional
            lista listelor de undo, by default []
        redo_list : list, optional
            lista listelor de redo, by default []
        """
        self.__list__ = copy_list(list)
        self.__undo_list__ = copy_list_list(undo_list)
        self.__redo_list__ = copy_list_list(redo_list)
    def __eq__(self, other):
        """defineste operatia de egalitate intre 2 Manageri de liste

        Parameters
        ----------
        other : ListManager
            celalalt manager

        Returns
        -------
        Bool
            True daca au aceleasi valori in memorie
        """
        return self.getList() == other.getList() and self.__getUndoList__() == other.__getUndoList__() and self.__getRedoList__() == other.__getRedoList__()
    def __str__(self):
        """formateaza listManagerul pt afisare

        Returns
        -------
        str
            textul corespunzator managerului
        """
        text = ""
        text = text + "Lista actuala este: " + str(self.getList())
        if self.__getUndoList__():
            text = text + "\n"
            text = text + "Prima lista din undo este: " + str(self.__getUndoList__()[-1])
        if self.__getRedoList__():
            text = text + "\n"
            text = text + "Prima lista din redo este: " + str(self.__getRedoList__()[-1])
            
        return text
    def __getList__(self):
        return self.__list__
    def __getUndoList__(self):
        return self.__undo_list__
    def __getRedoList__(self):
        return self.__redo_list__
    def __setList__(self, newList):
        self.__list__ = newList
    def append(self, newItem):
        """adauga un nr la sfarsitul listei curente

        Parameters
        ----------
        newItem : object
            noul element introdus in lista
        """
        undoList = self.__getUndoList__()
        redoList = self.__getRedoList__()
        list = self.__getList__()

        undoList.append(copy_list(list))
        list.append(newItem)
        redoList.clear()
    def insert(self, pos, newItem):
        undoList = self.__getUndoList__()
        redoList = self.__getRedoList__()
        list = self.__getList__()

        undoList.append(copy_list(list))
        list.insert(pos, newItem)
        redoList.clear()
    def delete(self, pos1, pos2):
        undoList = self.__getUndoList__()
        redoList = self.__getRedoList__()
        list = self.__getList__()

        undoList.append(copy_list(list))
        del list[pos1:pos2]
        redoList.clear()
    def pop(self, pos):
        undoList = self.__getUndoList__()
        redoList = self.__getRedoList__()
        list = self.__getList__()

        undoList.append(copy_list(list))
        list.pop(pos)
        redoList.clear()
    def setList(self, newList):
        undoList = self.__getUndoList__()
        redoList = self.__getRedoList__()
        list = self.__getList__()

        undoList.append(copy_list(list))
        self.__setList__(copy_list(newList))
        redoList.clear()
    def getList(self):
        return copy_list(self.__getList__())   
    def undo(self):
        """revine la ultima lista din memorie

        Raises
        ------
        IndexError
            daca lista de undo este goala
        """
        list = self.getList()
        undo_list = self.__getUndoList__()
        redo_list = self.__getRedoList__()

        if not undo_list:
            raise IndexError
        
        redo_list.append(copy_list(list))
        self.__setList__(undo_list[-1])
        undo_list.pop()   
    def redo(self):
        """revine la lista posterioare

        Raises
        ------
        IndexError
            daca nu lista de redo este goala
        """
        list = self.getList()
        undo_list = self.__getUndoList__()
        redo_list = self.__getRedoList__()

        if not redo_list:
            raise IndexError
        
        undo_list.append(copy_list(list))
        self.__setList__(redo_list[-1])
        redo_list.pop()
def tests():
    def test_getList():
        tests = [
            ListManager([1, 2, 3], [], []),
            ListManager(),
            ListManager([1, 2, 3], [[1, 2]], [[1, 3]])
        ]
        correct_ans = [
            [1, 2, 3],
            [],
            [1, 2, 3],
        ]
        result = zip(tests, correct_ans)
        for case in result:
            input = case[0]
            answer = case[1]

            assert input.getList() == answer
    test_getList()
    def test_append():
        tests = [
            (ListManager([1, 2, 3], [], []), 1),
            (ListManager(), -100),
            (ListManager([1, 2, 3], [[1, 2]], [[1, 3]]), 0),
        ]
        correct_ans = [
            ListManager([1, 2, 3, 1], [[1, 2, 3]]),
            ListManager([-100], [[]]),
            ListManager([1, 2, 3, 0], [[1, 2], [1, 2, 3]], [])
        ]
        result = zip(tests, correct_ans)
        for case in result:
            input = case[0]
            myManager = input[0]
            number = input[1]
            answer = case[1]
            myManager.append(number)
            
            assert myManager == answer
    test_append()
    def test_insert():
        tests = [
            (ListManager([1, 2, 3], [], []), 2, 1),
            (ListManager(), 0, -100),
            (ListManager([1, 2, 3], [[1, 2]], [[1, 3]]), 3, 0),
        ]
        correct_ans = [
            ListManager([1, 2, 1, 3], [[1, 2, 3]]),
            ListManager([-100], [[]]),
            ListManager([1, 2, 3, 0], [[1, 2], [1, 2, 3]], [])
        ]
        result = zip(tests, correct_ans)
        for case in result:
            input = case[0]
            myManager = input[0]
            pos = input[1]
            number = input[2]
            answer = case[1]
            myManager.insert(pos, number)
            
            assert myManager == answer
    test_insert()
    def test_delete():
        tests = [
            (ListManager([1, 2, 3], [], []), 0, 3),
            (ListManager([-100]), 0, 1),
            (ListManager([1, 2, 3], [[1, 2]], [[1, 3]]), 1, 2),
        ]
        correct_ans = [
            ListManager([], [[1, 2, 3]]),
            ListManager([], [[-100]]),
            ListManager([1, 3], [[1, 2], [1, 2, 3]], [])
        ]
        result = zip(tests, correct_ans)
        for case in result:
            input = case[0]
            myManager = input[0]
            pos1 = input[1]
            pos2 = input[2]
            answer = case[1]
            myManager.delete(pos1, pos2)
            
            assert myManager == answer
    test_delete()
    def test_pop():
        tests = [
            (ListManager([1, 2, 3], [], []), 2),
            (ListManager([-100]), 0),
            (ListManager([1, 2, 3], [[1, 2]], [[1, 3]]), 1),
        ]
        correct_ans = [
            ListManager([1, 2], [[1, 2, 3]]),
            ListManager([], [[-100]]),
            ListManager([1, 3], [[1, 2], [1, 2, 3]], []),
        ]
        result = zip(tests, correct_ans)
        for case in result:
            input = case[0]
            myManager = input[0]
            pos = input[1]
            answer = case[1]
            myManager.pop(pos)
            
            assert myManager == answer
    test_pop()
    def test_setList():
        tests = [
            (ListManager([1, 2, 3], [], []), [1, 1, 1, 1]),
            (ListManager([-100]), [1, 1, 1, 1]),
            (ListManager([1, 2, 3], [[1, 2]], [[1, 3]]), [1, 1, 1, 1]),
        ]
        correct_ans = [
            ListManager([1, 1, 1, 1], [[1, 2, 3]]),
            ListManager([1, 1, 1, 1], [[-100]]),
            ListManager([1, 1, 1, 1], [[1, 2], [1, 2, 3]], [])
        ]
        result = zip(tests, correct_ans)
        for case in result:
            input = case[0]
            myManager = input[0]
            newList = input[1]
            answer = case[1]
            myManager.setList(newList)
            newList.clear()
            assert myManager == answer
    test_setList()
    def test_undo():
        tests = [
            ListManager([1, 2, 3], [[-100]]),
            ListManager([-100], [[-2000]]),
            ListManager([1, 2, 3], [[1, 2]], [[1, 3]])
        ]
        correct_ans = [
            ListManager([-100], [], [[1, 2, 3]]),
            ListManager([-2000], [], [[-100]]),
            ListManager([1, 2], [], [[1, 3], [1, 2, 3]])
        ]
        result = zip(tests, correct_ans)
        for case in result:
            input = case[0]
            answer = case[1]

            input.undo()
            assert input == answer
    test_undo()
    def test_redo():
        tests = [
            ListManager([1, 2, 3], [], [[-100]]),
            ListManager([-100], [], [[-2000]]),
            ListManager([1, 2, 3], [[1, 2]], [[1, 3]])
        ]
        correct_ans = [
            ListManager([-100], [[1, 2, 3]], []),
            ListManager([-2000], [[-100]], []),
            ListManager([1, 3], [[1, 2], [1, 2, 3]], [])
        ]
        result = zip(tests, correct_ans)
        for case in result:
            input = case[0]
            answer = case[1]

            input.redo()
            assert input == answer
    test_redo()
tests()



def complex_list_to_text(mylist):
    """afiseaza o lista de numere complexe

    Parameters
    ----------
    mylist : list of tuples
        lista de numere complexe
    """
    text = ""
    text = text + "["
    last = len(mylist) - 1
    for i, el in enumerate(mylist):
        text = text + str(el)
        if i != last:
            text = text + ", "
    text = text + "]"
    return text
def complex_list_to_imaginary_text(mylist):
    """afiseaza o lista de numere complexe

    Parameters
    ----------
    mylist : list of tuples
        lista de numere complexe
    """

    text = ""
    text = text + "["
    last = len(mylist) - 1
    for i, el in enumerate(mylist):
        text = text + str(el.imaginary())
        if i != last:
            text = text + ", "
    text = text + "]"
    return text



def add_complex_number(myListManager, complex_number, pos = None):
    """adauga un numar complex la lista actuala

    Parameters
    ----------
    mylist : list of tuples
        lista de nr complexe
    complex_number : tuple
        noul numar care se adauga
    pos : int, optional
        locul in care sa fie adaugat, by default -1
    """
    if pos is None:
        myListManager.append(complex_number)
    else:
        myListManager.insert(pos, complex_number)
def test_add_complex_number():
    inputs = [
        #inputs: mylist, complex_number, pos = -1
        ([[1, 2], [2, 3], [3, 4], [4, 0], [0, 5]], [100, 100]),
        ([[1, 2], [2, 3], [3, 4], [4, 0], [0, 5]], [100, 100], 0),
        ([[1, 2], [2, 3], [3, 4], [4, 0], [0, 5]], [100, 100], 3),
        ([[1, 2], [2, 3], [3, 4], [4, 0], [0, 5]], [100, 100], 5),
        ([[0, 5]], [100, 100]),
        ([[0, 5]], [100, 100], 0),
        ([[0, 5]], [100, 100], 1),
        ([], [100, 100]),
        ([], [100, 100], 0),
    ]
    correct_answers = [
        #mylist result
        [[1, 2], [2, 3], [3, 4], [4, 0], [0, 5], [100, 100]],
        [[100, 100], [1, 2], [2, 3], [3, 4], [4, 0], [0, 5]],
        [[1, 2], [2, 3], [3, 4], [100, 100], [4, 0], [0, 5]],
        [[1, 2], [2, 3], [3, 4], [4, 0], [0, 5], [100, 100]],
        [[0, 5], [100, 100]],
        [[100, 100], [0, 5]],
        [[0, 5], [100, 100]],
        [[100, 100]],
        [[100, 100]],
    ]

    result = zip(inputs, correct_answers)
    for el in result:
        input = el[0]
        correct_ans = el[1]
        mylist = input[0]
        mynumber = input[1]

        for i in range (len(mylist)):
            mylist[i] = NrComplex(mylist[i][0], mylist[i][1])
        mynumber = NrComplex(mynumber[0], mynumber[1])
        myManager = ListManager(mylist)
        
        for i in range (len(correct_ans)):
            correct_ans[i] = NrComplex(correct_ans[i][0], correct_ans[i][1])
        
        if len(input) == 3:
            pos = input[2]
            add_complex_number(myManager, mynumber, pos)
        else:
            add_complex_number(myManager, mynumber)
        
        assert len(myManager.getList()) == len(correct_ans)
        final = zip(myManager.getList(), correct_ans)
        for nr in final:
            a = nr[0]
            b = nr[1]
            assert a == b
test_add_complex_number()

def get_module_less_than_10(myListManager):
    """returneaza o noua lista cu numerele ale caror modul este mai mic decat 10

    Parameters
    ----------
    mylist : list of tuples
        lista de nr complexe

    Returns
    -------
    list of tuple
        lista gasita
    """
    newlist = []
    for el in myListManager.getList():
        if el.abs() < 10:
            newlist.append(el)
    return newlist
def test_get_module_less_than_10():
    inputs = [
        [(1, 2), (2, 3), (30, 40), (4, 0), (3, 5), (8, 6), (8, 5)],
        [(0, 5)],
        [(10, 0)],
        [(0, 100)],
        [(6, 8)],
        [],
    ]
    correct_answers = [
        [(1, 2), (2, 3), (4, 0), (3, 5), (8, 5)],
        [(0, 5)],
        [],
        [],
        [],
        [],
    ]
    result = zip(inputs, correct_answers)
    for el in result:
        mylist = el[0]
        correct_ans = el[1]

        for i in range (len(mylist)):
            mylist[i] = NrComplex(mylist[i][0], mylist[i][1])
        myManager = ListManager(mylist)

        for i in range (len(correct_ans)):
            correct_ans[i] = NrComplex(correct_ans[i][0], correct_ans [i][1])
        
        newlist = get_module_less_than_10(myManager)

        assert len(newlist) == len(correct_ans)
        final = zip(newlist, correct_ans)
        for nr in final:
            a = nr[0]
            b = nr[1]
            assert a == b
test_get_module_less_than_10()

def get_module_equal_10(myListManager):
    """returneaza o noua lista cu numerele ale caror modul este egal cu 10

    Parameters
    ----------
    mylist : list of tuples
        lista de nr complexe

    Returns
    -------
    list of tuple
        lista gasita
    """
    newlist = []
    for el in myListManager.getList():
        if el.abs() == 10:
            newlist.append(el)
    return newlist
def test_get_module_equal_10():
    inputs = [
        [(1, 2), (2, 3), (30, 40), (4, 0), (3, 5), (8, 6), (8, 5)],
        [(0, 5)],
        [(8, 6), (2, 3), (6, 8)],
        [(8, 6), (6, 8), (6, 8), (6, 8)],
        [(6, 8)],
        [],
    ]
    correct_answers = [
        [(8, 6)],
        [],
        [(8, 6), (6, 8)],
        [(8, 6), (6, 8), (6, 8), (6, 8)],
        [(6, 8)],
        [],
    ]
    result = zip(inputs, correct_answers)
    for el in result:
        mylist = el[0]
        correct_ans = el[1]

        for i in range (len(mylist)):
            mylist[i] = NrComplex(mylist[i][0], mylist[i][1])
        myManager = ListManager(mylist)

        for i in range (len(correct_ans)):
            correct_ans[i] = NrComplex(correct_ans[i][0], correct_ans [i][1])
        
        newlist = get_module_equal_10(myManager)

        assert len(newlist) == len(correct_ans)
        final = zip(newlist, correct_ans)
        for nr in final:
            a = nr[0]
            b = nr[1]
            assert a == b
test_get_module_equal_10()

def get_sum_over_subsequence(myListManager, start, final):
    """calculeaza suma numerelor complexe dintr-o subsecventa a listei

    Parameters
    ----------
    mylist : list of tuples
        lista actuala
    start : int
        indexul de start al subsecv
    final : int
        indexul de final al subsecv

    Returns
    -------
    tuple
        nr complex = sum(mylist[start:final])
    """
    if not (0 <= start and start <= final and final < len(myListManager.getList())):
        return NrComplex()
    newlist = get_subsequence(myListManager.getList(), start, final)
    sum = NrComplex()
    for el in newlist:
        sum = sum + el
    return sum  
def test_get_sum_over_subsequence():
    inputs = [
        ([(1, 2), (2, 3), (8, 5), (1, 1), (1, 1)], 0, 2),
        ([(0, 5)], 0, 0),
        ([(6, 8), (6, 8), (6, 8), (6, 8)], 0, 3),
        ([], 0, 0),
    ]
    correct_answers = [
        (11, 10),
        (0, 5),
        (24, 32),
        (0, 0),
    ]
    
    for i, test in enumerate(inputs):
        testlist = test[0]
        for j in range(len(testlist)):
            testlist[j] = NrComplex(testlist[j][0], testlist[j][1])
        myManager = ListManager(testlist)
        
        correct_answers[i] = NrComplex(correct_answers[i][0], correct_answers[i][1])
        
        start = test[1]
        final = test[2]
        result = get_sum_over_subsequence(myManager, start, final)
        assert(result == correct_answers[i])
test_get_sum_over_subsequence()

def get_product_over_subsequence(myListManager, start, final):
    """calculeaza produsul numerelor complexe dintr-o subsecventa a listei

    Parameters
    ----------
    mylist : list of tuples
        lista actuala
    start : int
        indexul de start al subsecv
    final : int
        indexul de final al subsecv

    Returns
    -------
    tuple
        nr complex = product(mylist[start:final])
    """
    if not (0 <= start and start <= final and final < len(myListManager.getList())):
        return NrComplex()
    newlist = get_subsequence(myListManager.getList(), start, final)
    product = NrComplex(1, 0)
    for el in newlist:
        product = product * el
    return product
def test_get_product_over_subsequence():
    inputs = [
        ([(1, 2), (2, 3), (8, 5), (1, 1), (1, 1)], 0, 2),
        ([(0, 5)], 0, 0),
        ([(6, 8), (6, 8), (6, 8), (6, 8)], 2, 3),
        ([], 0, 0),
    ]
    correct_answers = [
        (-67, 36),
        (0, 5),
        (-28, 96),
        (0, 0),
    ]
    for i, test in enumerate(inputs):
        testlist = test[0]
        for j in range(len(testlist)):
            testlist[j] = NrComplex(testlist[j][0], testlist[j][1])
        myManager = ListManager(testlist)
        correct_answers[i] = NrComplex(correct_answers[i][0], correct_answers[i][1])
        
        start = test[1]
        final = test[2]
        result = get_product_over_subsequence(myManager, start, final)
        
        assert(result == correct_answers[i])
test_get_product_over_subsequence()

def delete_all_compared_to_number_and_sign(myListManager, number, sign):
    """filtreaza toate numerele cu modulul </=/> decat un numar dat

    Parameters
    ----------
    mylist : list of tuples
        lista de nr complexe
    number : int
        numarul cu care se va face compararea
    sign : str
        un semn <,>,= sub format string
    """
    def module_less_than(a):
        if a.abs() < number:
            return True
        return False
    def module_greater_than(a):
        if a.abs() > number:
            return True
        return False
    def module_equal_to(a):
        if a.abs() == number:
            return True
        return False
    dict_signs = {
        "<" : module_less_than,
        ">" : module_greater_than,
        "=" : module_equal_to,
    }
    newList = get_all_without_property(myListManager.getList(), dict_signs[sign])
    myListManager.setList(newList)
def test_delete_all_compared_to_number_and_sign():
    inputs = [
        ([(1, 2), (2, 3), (8, 5), (1, 1), (1, 1)], 5, "<"),
        ([(0, 5)], 5, "="),
        ([(6, 8), (6, 8), (6, 8), (6, 8)], 6, ">"),
        ([], 0, "="),
    ]
    correct_answers = [
        [(8, 5)],
        [],
        [],
        [],
    ]
    for i, test in enumerate(inputs):
        testlist = test[0]
        number = test[1]
        sign = test[2]

        for j in range(len(testlist)):
            testlist[j] = NrComplex(testlist[j][0], testlist[j][1])
        myManager = ListManager(testlist)
        for j in range(len(correct_answers[i])):
            correct_answers[i][j] = NrComplex(correct_answers[i][j][0], correct_answers[i][j][1])

        delete_all_compared_to_number_and_sign(myManager, number, sign)
        assert(len(myManager.getList()) == len(correct_answers[i]))
        for j, el in enumerate(myManager.getList()):
            assert(el == correct_answers[i][j])
test_delete_all_compared_to_number_and_sign()



generated_list = [
    NrComplex(-1, 2),
    NrComplex(3, -4), 
    NrComplex(8, 6),
    NrComplex(6, 10),
    NrComplex(6, -8),
    NrComplex(1, 0),
    NrComplex(-2, 0),
    NrComplex(0, 3),
    NrComplex(0, -4),
    NrComplex(-10, 10),
]