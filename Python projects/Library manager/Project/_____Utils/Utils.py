from random import seed
from random import randint
import random, string

def copy_list(list):
    """
    returneaza o copie a listei date ca parametru
    :param list: lista sa se copieze
    :return: copia listei
    """
    newlist = []
    for el in list:
        newlist.append(el)
    return newlist
def test_copy():
    list = [1, 2, 3, 4]
    a = copy_list(list)
    list[1] = 100
    assert(a == [1, 2, 3, 4])
test_copy()

seed(1)
def random_word(max_len):
    """
    returneaza un cuvant de maxim 'max_len' litere mici
    :param max_len: int: lungimea maxima de litere
    :return: str: cuvantul generat random
    """
    len = randint(1, max_len)

    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(len))
def random_word_with_numbers(len):
    """
    returneaza un cuvant alcatuit din 'len' numere zecimale
    :param len: int: lungimea cuvantului
    :return: str: cuvantul generat random
    """
    numbers = '0123456789'
    return ''.join(random.choice(numbers) for i in range(len))

def mycmp(a, b):
    return (a<b)

def myBubbleSort(list, key=lambda x: x, reversed=False, cmp=mycmp):
    """
    sorteaza in mod crescator elementele unei liste dupa metoda bubble sort
    :param list: lista de obiecte
    :param key: method: cheia dupa care se sorteaza
    :param reversed: boolean: True daca se doreste sortarea descrescatoare, False altfel
    :return: lista sortata
    """
    sorted = False
    while not sorted:
        sorted = True
        for i in range(len(list) - 1):
            if not reversed and cmp(key(list[i + 1]), key(list[i])):
                list[i], list[i + 1] = list[i + 1], list[i]
                sorted = False
            elif reversed and cmp(key(list[i]), key(list[i + 1])):
                list[i], list[i + 1] = list[i + 1], list[i]
                sorted = False
    return list
def test_myBubbleSort():
    def mycmp(a, b):
        return (1/a < 1/b)
    list = [1, 2, 4, 3, 3, 2, 1, 6, 76,4 ,3, 5, 6]
    list = myBubbleSort(list, key=lambda x: 1/x, cmp=mycmp)
    assert(list == sorted(list))
test_myBubbleSort()

def myShellSort(list, key=lambda x: x, reversed=False, cmp=mycmp):
    """
        sorteaza in mod crescator elementele unei liste dupa metoda shell sort
        :param list: lista de obiecte
        :param key: method: cheia dupa care se sorteaza
        :param reversed: boolean: True daca se doreste sortarea descrescatoare, False altfel
        :return: lista sortata
    """

    n = len(list)
    gap = n // 2

    while gap > 0:
        for i in range(gap, n):
            aux = list[i]
            j = i
            while j >= gap and ((cmp(key(aux), key(list[j-gap])) and not reversed) or cmp(key(list[j-gap]), key(aux)) and reversed):
                list[j] = list[j - gap]
                j -= gap
            list[j] = aux
        gap //= 2

    return list
def test_myShellSort():
    def test_cmp(a, b):
        return (a>b)
    list = [1, 2, 4, 3, 3, 2, 1, 6, 76,4 ,3, 5, 6]
    list = myBubbleSort(list, key=lambda x: x%5, reversed=False, cmp=test_cmp)
    assert(list == sorted(list, key=lambda x: x%5, reverse=True))
    assert(list == sorted(list, key=lambda x: x%5, reverse=True))
test_myShellSort()









