from math import sqrt
import os
import sys
sys.path.append(os.getcwd() + "\\")
from utils.utils import prim

class NrComplex:
    def __init__(self, real_part = 0, imaginary_part = 0, text = ""):
        """initializeaza un nou nr complex cu partea reala/partea imaginara sau dintr-un text

        Parameters
        ----------
        real_part : int, optional
            partea reala a nr, by default 0
        imaginary_part : int, optional
            partea imaginara a nr, by default 0
        text : str, optional
            textul corespunzator nr complex, by default ""
        """
        if text != "":
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
            self.__real = re
            self.__imaginary = im
        else:
            self.__real =  int(real_part)
            self.__imaginary = int(imaginary_part)
    def __eq__(self, other):
        """verifica daca 2 instante sunt egale

        Parameters
        ----------
        other : NrComplex
            numarul cu care se compara

        Returns
        -------
        True/False
            True daca au partile reale si partile imaginare egale intre ele, False altfel
        """
        re = self.real()
        im = self.imaginary()

        re1 = other.real()
        im1 = other.imaginary()
        return re == re1 and im == im1
    def __str__(self):
        """formateaza un nr complex pentru a putea fi afisat

        Returns
        -------
        str
            textul corespunzator nr complex
        """
        re = self.real()
        im = self.imaginary()

        if re == 0 and im == 0:
            return "0"
        elif re == 0:
            if im == 1:
                return "i"
            elif im == -1:
                return "-i"
            else:
                return str(im) + "i"
        elif im == 0:
            return str(re)
        else:
            if im < 0:
                if im == -1:
                    return str(re) + "-i"
                else:
                    return str(re) + "-" + str(abs(im)) + "i"
            elif im == 1:
                return str(re) + "+i"
            else:
                return str(re) + "+" + str(abs(im)) + "i"
    def __add__(self, other):
        """defineste operatia + intre 2 nr complexe

        Parameters
        ----------
        other : NrComplex
            al doilea operand

        Returns
        -------
        NrComplex
            Suma nr complexe
        """
        re = self.real() + other.real()
        im = self.imaginary() + other.imaginary()
        newObj = NrComplex(re, im)
        return newObj
    def __mul__(self, other):
        """defineste operatia de inmultire a 2 nr complexe

        Parameters
        ----------
        other : NrComplex
            al doilea operand

        Returns
        -------
        NrComplex
            rezultatul inmultirii
        """
        re = self.real()
        im = self.imaginary()
        re1 = other.real()
        im1 = other.imaginary()
        #(a+bi)*(c+di) = ac - bd + i(ad + bc)
        reNew = re*re1 - im*im1
        imNew = re*im1 + re1*im
        newObj = NrComplex(reNew, imNew)
        return newObj
    
    def real(self):
        """ofera acces la partea reala a nr

        Returns
        -------
        int
            parte reala
        """
        return self.__real
    def imaginary(self):
        """ofera acces la partea imaginara a nr

        Returns
        -------
        int
            parte imaginara
        """
        return self.__imaginary
    def abs(self):
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
        re = self.real()
        im = self.imaginary()

        modul = sqrt(re*re + im*im)
        return modul
    
def first_smaller_imaginary(self, other):
    """returneaza valoara de adevar a propozitiei

    Parameters
    ----------
    other : NrComplex
        al doilea operand

    Returns
    -------
    True/False
        true daca primul nr complex are partea imaginara mai mica decat cea pt al doilea op
    """
    if self.imaginary() < other.imaginary():
        return True
    return False
def real_part_prime(self):
    """returneaza true daca nr complex are partea reala nr prim

    Returns
    -------
    Bool
    """
    if prim(self.real()):
        return True
    return False

def __test_init__():
        tests_number = [(1, 2), (2, 3), (0, 3), (0, -1), (1, 0), (-1, 0), (0, 0), (-100, -100)]
        tests_text = ["", "2", "-2", "-300", "2+3i", "4i", "-4i", "-5+100i", "-5+-10i"]
        answers_text = [(0, 0), (2, 0), (-2, 0), (-300, 0), (2, 3), (0, 4), (0, -4), (-5, 100), (-5, -10)]

        for test in tests_number:
            re = test[0]
            im = test[1]
            var = NrComplex(re, im)
            assert var.real() == re and var.imaginary() == im
        
        result = zip(tests_text, answers_text)

        for el in result:
            re = el[1][0]
            im = el[1][1]
            var = NrComplex(text = el[0])
            assert var.real() == re and var.imaginary() == im    
__test_init__()

def __test_eq__():
    tests = [
        (NrComplex(-1, 0), NrComplex(0, 0)),    
        (NrComplex(-1, 0), NrComplex(-1)), 
        (NrComplex(-1, -100), NrComplex(-1)),
        (NrComplex(-1, -100), NrComplex(-1, -100)),
        (NrComplex(), NrComplex(text="0")), 
        (NrComplex(text="2+3i"), NrComplex(2, 3)),
    ]
    answers = [
        False,
        True,
        False,
        True,
        True,
        True,
    ]

    result = zip(tests, answers)
    for el in result:
        assert (el[0][0] == el[0][1]) == el[1]
__test_eq__()
