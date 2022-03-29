def prim(a):
    """verifica daca a este numar prim

    Parameters
    ----------
    a : int
        numarul care se verifica

    Returns
    -------
    bool
        returneaza 1 daca numarul a este prim, altfel returneaza 0
    """
    if a < 2:
        return 0
    for i in range(2, a):
        if a % i == 0:
            return 0
    return 1
def test_prim():
    tests =     [-2, -3, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
    answers =   [ 0,  0,  0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0,  0,  1,  0,  1]
    for i, el in enumerate(tests):
        assert(prim(el) == answers[i])
test_prim()

def copy_list(list):
    newlist = []
    for el in list:
        newlist.append(el)
    return newlist
def copy_list_list(list):
    newlist = []
    for el in list:
        newel = copy_list(el)
        newlist.append(newel)
    return newlist

def get_subsequence(mylist, start, final):
    """creeaza o subsecventa a unei liste

    Parameters
    ----------
    mylist : list
        o lista
    start : int
        indexul de start al subsecv
    final : int
        indexul de final al subsecv

    Returns
    -------
    list
        subsecv cautata
    """ 
    subsequence = []
    for i in range(start, final + 1):
        subsequence.append(mylist[i])
    return subsequence

def dict_to_list(nr_complex):
    return [nr_complex[0], nr_complex[1]]

def replace_all_appearances(mylist, this, that):
    """inlocuieste toate aparitiile lui this in mylist cu that

    Parameters
    ----------
    mylist : list
        o lista
    this : object
        obiectul care sa fie inlocuit
    that : object
        ob cu care se inlocuieste

    Returns
    -------
    bool
        true daca a avut loc o inlocuire
    """
    newlist = mylist
    length = len(mylist)
    for i in range(length):
        if newlist[i] == this:
            newlist[i] = that
    return newlist
def test_replace_all_appearances():
    inputs = [
        ([(1, 0), (2, 0), (4, 40), (4, 0), (3, 5), (4, 0), (8, 5)], (4, 0), (0, 4)),
        ([(1, 0), (2, 0), (4, 40), (4, 0), (3, 5), (4, 0)], (4, 0), (0, 4)),
        ([(4, 0), (3, 5), (4, 0), (8, 5)], (4, 0), (0, 4)),
        ([(3, 5), (8, 5)], (4, 0), (0, 4)),
        ([(4, 0), (4, 4), (4, 0)], (4, 0), (0, 4)),
        ([], (4, 0), (0, 4)),
        ([(4, 0), (4, 0), (4, 0)], (4, 0), (0, 4)),
    ]
    correct_answers = [
        ([(1, 0), (2, 0), (4, 40), (0, 4), (3, 5), (0, 4), (8, 5)], 1),
        ([(1, 0), (2, 0), (4, 40), (0, 4), (3, 5), (0, 4)], 1),
        ([(0, 4), (3, 5), (0, 4), (8, 5)], 1),
        ([(3, 5), (8, 5)], 0),
        ([(0, 4), (4, 4), (0, 4)], 1),
        ([], 0),
        ([(0, 4), (0, 4), (0, 4)], 1),
    ]

    for i, test in enumerate(inputs):
        mylist = test[0]
        this = test[1]
        that = test[2]
        newlist = replace_all_appearances(mylist, this, that)
        
        assert(len(newlist) == len(correct_answers[i][0]))
        for j, el in enumerate(newlist):
            assert(dict_to_list(el) == dict_to_list(correct_answers[i][0][j]))

def sort(mylist, comparison_function):
    """sorteaza lista folosind o functie de comparare a elementelor

    Parameters
    ----------
    mylist : list
        o lista
    comparison_function : function
        o functie care asigura ordinea elementelor intr-o lista
    """
    n = len(mylist)
    for i in range(n):
        for j in range(i+1, n):
            if comparison_function(mylist[i], mylist[j]):
                aux = mylist[i]
                mylist[i] = mylist[j]
                mylist[j] = aux
def test_sort():
    def comparison_function(a, b):
        if a[1] < b[1]:
            return True
        return False
    inputs = [
        [(1, 2), (2, 3), (30, 40), (4, 0), (8, 6)],
        [(0, 5)],
        [(8, 6), (2, 3), (6, 8)],
        [(6, 8), (6, 8), (6, 8)],
        [(6, 8)],
        [],
    ]
    correct_answers = [
        [(30, 40), (8, 6), (2, 3), (1, 2), (4, 0)],
        [(0, 5)],
        [(6, 8), (8, 6), (2, 3)],
        [(6, 8), (6, 8), (6, 8)],
        [(6, 8)],
        [],
    ]
    for i, test in enumerate(inputs):
        newlist = test
        sort(newlist, comparison_function)
        assert(len(newlist) == len(correct_answers[i]))
        for j, el in enumerate(newlist):
            assert(el == correct_answers[i][j])

def get_all_without_property(mylist, property_function):
    """filtreaza toate elementele cu o anumita proprietate

    Parameters
    ----------
    mylist : lista
        o lista
    property_function : function
        o functie care verifica proprietatea unui element transmis ca parametru
    """
    newlist = []
    for el in mylist:
        if not property_function(el):
            newlist.append(el)
    return newlist
def test_delete_all_without_property():
    def property_function(a):
        if prim(a[0]):
            return True
        return False
    inputs = [
        [(1, 2), (2, 3), (30, 40), (4, 0), (8, 6)],
        [(0, 5)],
        [(8, 6), (2, 3), (2, 8)],
        [(2, 8), (2, 8), (6, 8)],
        [(2, 8)],
        [],
    ]
    correct_answers = [
        [(1, 2), (30, 40), (4, 0), (8, 6)],
        [(0, 5)],
        [(8, 6)],
        [(6, 8)],
        [],
        [],
    ]
    for i, test in enumerate(inputs):
        newlist = test
        newlist = get_all_without_property(newlist, property_function)
        assert(len(newlist) == len(correct_answers[i]))
        for j, el in enumerate(newlist):
            assert(el == correct_answers[i][j])

test_replace_all_appearances()
test_sort()
test_delete_all_without_property()