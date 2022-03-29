import os
import sys
sys.path.append(os.getcwd() + "\\")
from math import sqrt
from utils.utils import prim

def print_complex_number(nr_complex):
    """afiseaza un numar complex sub forma a+bi/a/bi

    Parameters
    ----------
    nr_complex : tuple
        numar complex unde pe prima pozitie se afla partea reala, iar pe a doua pozitie se afla partea imaginara
    """
    a = nr_complex[0]
    b = nr_complex[1]
    
    if a != 0 and b != 0:
        print(str(a) + "+" + str(b) + "i", end="")
    elif a != 0:
        print(str(a), end="")
    elif b != 0:
        print(str(b) + "i", end="")
    else:
        print("0", end="")
def format_complex_number_from_text(text):
    """transforma un text intr-un numar complex daca este posibil

    Parameters
    ----------
    text : string
        textul cu nr complex

    Returns
    -------
    tuple
        un numar complex cu partea reala pe prima pozitie si partea imaginara pe a doua pozitie
    """
    text_parti = text.split(sep="+")
    if len(text_parti) == 1:  # deci numarul are doar parte reala/imaginara
        if text_parti[0][-1] == "i":  # e imaginara??
            re = 0
            im = int(text_parti[0].split("i")[0])
        else:
            re = int(text_parti[0])
            im = 0
    else:
        re = int(text_parti[0])
        im = int(text_parti[1].split("i")[0])
    nr_complex = []
    nr_complex.append(re)
    nr_complex.append(im)
    #return (re, im)
    return nr_complex
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
    text = input(message)
    try:
        return format_complex_number_from_text(text)
    except ValueError:
        return read_complex_number(message)
    except IndexError:
        return read_complex_number(message)
def print_imaginary_part(nr_complex):
    """afiseaza doar partea imaginara a unui numar

    Parameters
    ----------
    nr_complex : tuple
        numar complex (re, im)
    """
    im = nr_complex[1]
    if im == 0:
        print(0, end="")
    else:
        print(str(im) + "i", end="")



def init_complex_nr(a = 0, b = 0):
    nr_complex = []
    nr_complex.append(a)
    nr_complex.append(b)
    return nr_complex
def set_complex_nr(nr_complex, a, b):
    nr_complex[0] = a
    nr_complex[1] = b
def get_complex_nr(nr_complex):
    return [nr_complex[0], nr_complex[1]]



def get_module(nr_complex):
    """calculeaza modulul unui numar complex

    Parameters
    ----------
    nr_complex : tuple
        nr complex (re, im)

    Returns
    -------
    float
        modulul numarului complex
    """
    re = get_complex_nr(nr_complex)[0]
    im = get_complex_nr(nr_complex)[1]

    modul = sqrt(re*re + im*im)
    return modul
def test_get_module():
    inputs = [[1, 2], [2, 3], [3, 4], [4, 0], [0, 5], [0, 0]]
    correct_answers = [sqrt(5), sqrt(13), 5, 4, 5, 0]

    for i, test in enumerate(inputs):
        output = get_module(test)
        assert(output == correct_answers[i])

def add(a, b):
    """calculeaza suma a 2 numere complexe

    Parameters
    ----------
    a : tuple
        nr complex 
    b : tuple
        nr complex

    Returns
    -------
    tuple
        nr complex = a + b
    """
    re = get_complex_nr(a)[0] + get_complex_nr(b)[0]
    im = get_complex_nr(a)[1] + get_complex_nr(b)[1]
    '''
    nr_complex = []
    nr_complex.append(re)
    nr_complex.append(im)
    #return (re, im)
    return nr_complex
    '''
    complex_nr = init_complex_nr(re, im)
    return complex_nr   
def test_add():
    inputs = [([1, 1], [2, 3]), ([3, 4], [4, 0]), ([0, 5], [0, 0])]
    correct_answers = [[3, 4], [7, 4], [0, 5]]

    for i, test in enumerate(inputs):
        nr1 = test[0]
        nr2 = test[1]
        rez = add(nr1, nr2)
        assert(rez == correct_answers[i])

def multiply(a, b):
    """calculeaza produsul a 2 nre complexe

    Parameters
    ----------
    a : tuple
        nr complex
    b : tuple
        nr complex

    Returns
    -------
    tuple
        nr complex = a*b
    """
    re = get_complex_nr(a)[0] * get_complex_nr(b)[0] - get_complex_nr(a)[1] * get_complex_nr(b)[1]
    im = get_complex_nr(a)[0] * get_complex_nr(b)[1] + get_complex_nr(a)[1] * get_complex_nr(b)[0]

    nr_complex = init_complex_nr(re, im)
    #return (re, im)
    return nr_complex
def test_multiply():
    inputs = [([1, 1], [2, 3]), ([3, 4], [4, 0]), ([0, 5], [0, 0])]
    correct_answers = [[-1, 5], [12, 16], [0, 0]]

    for i, test in enumerate(inputs):
        nr1 = test[0]
        nr2 = test[1]
        rez = multiply(nr1, nr2)
        assert(rez == correct_answers[i])

def first_smaller_imaginary(a, b):
    """returneaza true daca im(a) < im(b)

    Parameters
    ----------
    a : tuple
        nr complex
    b : tuple
        nr complex

    Returns
    -------
    bool
        valoarea de adevar a propozitiei im(a)<im(b)
    """
    if get_complex_nr(a)[1] < get_complex_nr(b)[1]:
        return True
    return False

def real_part_prime(a):
    """verifica daca partea reala a unui numar complex este numar prim

    Parameters
    ----------
    a : tuple
        nr complex

    Returns
    -------
    bool
        true daca re(a) este nr prim si false altfel
    """
    if prim(get_complex_nr(a)[0]):
        return True
    return False




test_multiply()
test_get_module()
test_add()