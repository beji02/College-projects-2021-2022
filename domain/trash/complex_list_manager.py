import os
import sys
sys.path.append(os.getcwd() + "\\")
from utils.utils import delete_all_with_property, get_subsequence
from domain.complex_number_class import NrComplex


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



def add_complex_number(mylist, complex_number, pos = -1):
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
    if pos == -1:
        mylist.append(complex_number)
    else:
        mylist.insert(pos, complex_number)
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

        for i in range (len(correct_ans)):
            correct_ans[i] = NrComplex(correct_ans[i][0], correct_ans [i][1])
        
        if len(input) == 3:
            pos = input[2]
            add_complex_number(mylist, mynumber, pos)
        else:
            add_complex_number(mylist, mynumber)
        
        assert len(mylist) == len(correct_ans)
        final = zip(mylist, correct_ans)
        for nr in final:
            a = nr[0]
            b = nr[1]
            assert a == b
test_add_complex_number()

def get_module_less_than_10(mylist):
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
    for el in mylist:
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

        for i in range (len(correct_ans)):
            correct_ans[i] = NrComplex(correct_ans[i][0], correct_ans [i][1])
        
        newlist = get_module_less_than_10(mylist)

        assert len(newlist) == len(correct_ans)
        final = zip(newlist, correct_ans)
        for nr in final:
            a = nr[0]
            b = nr[1]
            assert a == b
test_get_module_less_than_10()

def get_module_equal_10(mylist):
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
    for el in mylist:
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

        for i in range (len(correct_ans)):
            correct_ans[i] = NrComplex(correct_ans[i][0], correct_ans [i][1])
        
        newlist = get_module_equal_10(mylist)

        assert len(newlist) == len(correct_ans)
        final = zip(newlist, correct_ans)
        for nr in final:
            a = nr[0]
            b = nr[1]
            assert a == b
test_get_module_equal_10()

def get_sum_over_subsequence(mylist, start, final):
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
    if not (0 <= start and start <= final and final < len(mylist)):
        return NrComplex()
    newlist = get_subsequence(mylist, start, final)
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
        correct_answers[i] = NrComplex(correct_answers[i][0], correct_answers[i][1])
        
        start = test[1]
        final = test[2]
        result = get_sum_over_subsequence(testlist, start, final)
        assert(result == correct_answers[i])
test_get_sum_over_subsequence()

def get_product_over_subsequence(mylist, start, final):
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
    if not (0 <= start and start <= final and final < len(mylist)):
        return NrComplex()
    newlist = get_subsequence(mylist, start, final)
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
        correct_answers[i] = NrComplex(correct_answers[i][0], correct_answers[i][1])
        
        start = test[1]
        final = test[2]
        result = get_product_over_subsequence(testlist, start, final)
        
        assert(result == correct_answers[i])
test_get_product_over_subsequence()

def delete_all_compared_to_number_and_sign(mylist, number, sign):
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
    delete_all_with_property(mylist, dict_signs[sign])
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
        for j in range(len(correct_answers[i])):
            correct_answers[i][j] = NrComplex(correct_answers[i][j][0], correct_answers[i][j][1])

        delete_all_compared_to_number_and_sign(testlist, number, sign)
        assert(len(testlist) == len(correct_answers[i]))
        for j, el in enumerate(testlist):
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
    
