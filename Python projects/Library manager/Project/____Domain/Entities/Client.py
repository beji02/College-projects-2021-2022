
class Client:
    __new_id = 1000

    @staticmethod
    def __generate_new_id():
        """
        creeaza un id unic pentru fiecare obiect de tip client
        :return: int: id unic
        """
        new_id = Client.__new_id
        Client.__new_id = Client.__new_id + 1
        return new_id

    def __init__(self, nume, prenume, nr_telefon, id = None, nr_imprutururi_totale = 0, nr_imprumuturi_actuale = 0):
        """
        initializeaza un nou obiect de tip client care caracterizeaza individul din realitate
        :param nume: numele clientului
        :param prenume: prenumele clientului
        :param nr_telefon: nr de telefon al clientului
        :param nr_imprutururi_totale: nr de carti imprumutate in total
        :param nr_imprumuturi_actuale: nr de carti pe care le are imprumutate in prezent
        """
        if id is None:
            self.__id = Client.__generate_new_id()
        else:
            self.__id = id
        self.__nume = nume
        self.__prenume = prenume
        self.__nr_telefon = nr_telefon
        self.__nr_imprumuturi_totale = nr_imprutururi_totale
        self.__nr_imprumuturi_actuale = nr_imprumuturi_actuale


    def __eq__(self, other):
        """
        exista egalitate intre 2 obiecte de tip client daca acestea au acelasi id
        :param other: client: clientul cu care se compara
        :return: True daca au acelasi id
        """
        if self.getId() == other.getId():
            return True
        return False
    def __str__(self):
        """
        afiseaza clientul pe 5 coloane id, nume, prenume, carti imprumutate in acest moment
        :return:
        """
        text = '{:<30}'.format(self.getId()) \
               + '{:<35}'.format(self.getName()) \
               + '{:<30}'.format(self.getFirstname()) \
               + '{:<30}'.format(self.getPhone()) \
               + '{:<30}'.format(self.getPresentBorrows())
        return text


    def getId(self):
        """
        returneaza idul clientului
        :return: int: id client
        """
        return self.__id
    def getName(self):
        """
        returneaza numele unui client
        :return: str
        """
        return self.__nume
    def getFirstname(self):
        """
        returneaza prenumele clientului
        :return: str: prenume
        """
        return self.__prenume
    def getPhone(self):
        """
        returneaza numarul de telefon al clientului
        :return: str: nr_telefon
        """
        return self.__nr_telefon
    def getTotalBorrows(self):
        """
        returneaza numarul total de imprumuturi pe care le-a facut clientul
        :return: int
        """
        return self.__nr_imprumuturi_totale
    def getPresentBorrows(self):
        """
        returneaza nr de carti pe care le are imprumutate clientul
        :return: int
        """
        return self.__nr_imprumuturi_actuale

    def setName(self, newName):
        """
        seteaza un nou nume clientului
        :param newName: str: noul nume
        :return: none
        """
        self.__nume = newName
    def setFirstname(self, newFirstName):
        """
        seteaza un nou prenume clientului
        :param newFirstName: str: noul prenume
        :return: none
        """
        self.__prenume = newFirstName
    def setPhone(self, newPhoneNumber):
        """
        seteaza un nou nr de telefon clientului
        :param newPhoneNumber: str: nr_telefon_nou
        :return: none
        """
        self.__nr_telefon = newPhoneNumber
    def setTotalBorrows(self, newTotalBorrows):
        """
        seteaza numarul total de imprumuturi ale clientului
        :param newTotalBorrows: int: nr total de imprumuturi nou
        :return: none
        """
        self.__nr_imprumuturi_totale = newTotalBorrows
    def setPresentBorrows(self, newBorrows):
        """
        seteaza un nou numar de carti pe care le are imprumutate clientul
        :param newBorrows: int: carti imprumutate in acest moment
        :return: none
        """
        self.__nr_imprumuturi_actuale = newBorrows


    def borrow(self):
        """
        simuleaza actiunea de a imprumuta o carte
            incrementeaza nr total de imprumuturi ale clientului
            incrementeaza nr de imprumuturi actuale ale clientului
        :return: none
        """
        self.setTotalBorrows(self.getTotalBorrows() + 1)
        self.setPresentBorrows(self.getPresentBorrows() + 1)
    def retur(self):
        """
        simuleaza returnarea unei carti
            decrementeaza nr de carti pe care le are clientul imprumutate la momentul actual
        :return: none
        """
        self.setPresentBorrows(self.getPresentBorrows() - 1)





def test_getters_setters():
    a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
    assert a.getId() == 1000
    assert a.getName() == "Bejan"
    assert a.getFirstname() == "Andrei"
    assert a.getPhone() == "0743155516"
    assert a.getTotalBorrows() == 10
    assert a.getPresentBorrows() == 3

    a.setName("Brita")
    a.setFirstname("Catalin")
    a.setPhone("0777444333")
    a.setTotalBorrows(3)
    a.setPresentBorrows(2)

    assert a.getId() == 1000
    assert a.getName() == "Brita"
    assert a.getFirstname() == "Catalin"
    assert a.getPhone() == "0777444333"
    assert a.getTotalBorrows() == 3
    assert a.getPresentBorrows() == 2
def test_eq():
    a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
    b = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
    assert (a == b) == False
    assert (a == a) == True




test_getters_setters()
test_eq()






