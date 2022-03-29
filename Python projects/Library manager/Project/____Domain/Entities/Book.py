class Book:
    __new_id = 0

    @staticmethod
    def __generate_new_id():
        """
        creeaza un id unic pentru fiecare obiect de tip book
        :return: int: id unic
        """
        new_id = Book.__new_id
        Book.__new_id = Book.__new_id + 1
        return new_id

    def __init__(self, title, author, description = "", k_copies = 1, k_borrows = 0, k_av = None, id = None):
        """
        obiectul caracterizeaza o carte din realitate
        :param title: str: titlul cartii
        :param author: str: numele autorului
        :param description: str: descrierea cartii
        :param k_copies: int: nr de exemplare ale cartii
        :param k_borrows: int: de cate ori a fost imprumutata o carte
        """
        if id is None:
            self.__id = Book.__generate_new_id()
        else:
            self.__id = id
        self.__title = title
        self.__author = author
        self.__desc = description
        self.__k_total_copies = k_copies
        if k_av is None:
            self.__k_av_copies = k_copies
        else:
            self.__k_av_copies = k_av
        self.__k_borrows = k_borrows

    def __str__(self):
        """
        afiseaza pe 5 coloane id-ul, titlul, autorul, nr de copii si de cate ori a fost imprumutata o carte anume
        :return: str: sirul de caractere descris
        """
        text = '{:<30}'.format(self.getId()) \
             + '{:<35}'.format(self.getTitle()) \
             + '{:<30}'.format(self.getAuthor()) \
             + '{:<30}'.format(self.getTotalCopies()) \
             + '{:<30}'.format(self.getBorrows())
        return text
    def __eq__(self, other):
        """
        defineste egalitatea dintre 2 carti
            daca au acelasi titlu si acelasi autor
        :param other: Book: alta carte cu care se compara
        :return:
        """
        if self.getTitle() == other.getTitle() \
                and self.getAuthor() == other.getAuthor():
            return True
        return False

    def getId(self):
        """
        :return: int: returneaza idul unei carti
        """
        return self.__id
    def getTitle(self):
        """
        :return: str: returneaza titlul unei carti
        """
        return self.__title
    def getAuthor(self):
        """
        :return: str: returneaza autorul unei carti
        """
        return self.__author
    def getDescription(self):
        """
        :return: str: returneaza descrierea unei carti
        """
        return self.__desc
    def getTotalCopies(self):
        """
        :return: int: nr total de exemplare ale carti
        """
        return self.__k_total_copies
    def getAvailableCopies(self):
        """
        returneaza nr de exemplare care se pot inchiria la momentul actual
        :return:
        """
        return self.__k_av_copies
    def getBorrows(self):
        """
        :return: int: nr de imprumuturi ale carti
        """
        return self.__k_borrows

    def setTitle(self, newTitle):
        """
        permite sa schimbe titlul unei carti
        :param newTitle: str
        :return: none
        """
        self.__title = newTitle
    def setAuthor(self, newAuthor):
        """
        permite sa schimbe autorul unei carti
        :param newAuthor: str
        :return: none
        """
        self.__author = newAuthor
    def setTotalCopies(self, newNr):
        """
        permite sa schimbe nr de exemplare ale cartii
        :param newNr: int
        :return: none
        """
        self.__k_total_copies = newNr
    def setDescription(self, newDescr):
        """
        permite sa schimbe descrierea unei carti
        :param newDescr: str
        :return: none
        """
        self.__desc = newDescr
    def setAvailableCopies(self, newVal):
        """
        seteaza nr de exemplare care se pot imprumuta in acest moment
        :param newVal: int: nou nr de exemplare care se pot imprumuta
        :return: none
        """
        self.__k_av_copies = newVal
    def setBorrows(self, newVal):
        """
        seteaza nr de cate ori a fost imprumutata cartea
        :param newVal: int: nr de imprumuturi
        :return: none
        """
        self.__k_borrows = newVal

    def isAvailable(self):
        """
        verifica daca cartea poate fi imprumutata
        :return: True daca se poate imprumuta
                 False altfel
        """
        if self.getAvailableCopies() > 0:
            return True
        return False
    def borrow(self):
        """
        simuleaza actiunea de a imprumuta
            decrementeaza nr de copii disponibile
            incrementeaza nr de imprumuturi ale cartii
        :return: none
        """
        self.setAvailableCopies(self.getAvailableCopies() - 1)
        self.setBorrows(self.getBorrows() + 1)
    def retur(self):
        """
        simuleaza actiunea de a returna o carte
            incrementeaza nr de copii disponibile
        :return: none
        """
        self.setAvailableCopies(self.getAvailableCopies() + 1)
# def test_init_id_title_author_descrp_copis_borrows():
#     title = "10 Negrii Mititei"
#     author = "Agatha Christie"
#     desc = "Zece negri mititei au mancat la cina oua.\nUnul insa s-a-necat si-au rămas doar noua."
#
#     mybook = Book(title, author, desc)
#     # print(mybook)
#     assert mybook.getId() == 0
#     assert mybook.getTitle() == title
#     assert mybook.getAuthor() == author
#     assert mybook.getDescription() == desc
#     assert mybook.getTotalCopies() == 1
#     assert mybook.getBorrows() == 0
#
#     title = title + "Demo"
#     mybook = Book(title, author, desc, k_copies = 100)
#     assert mybook.getId() == 1
#     assert mybook.getTitle() == title
#     assert mybook.getAuthor() == author
#     assert mybook.getDescription() == desc
#     assert mybook.getTotalCopies() == 100
#     assert mybook.getBorrows() == 0
#
# def test_change_title_author_copies_descrp():
#     title = "10 Negrii Mititei"
#     author = "Agatha Christie"
#     desc = "Zece negri mititei au mancat la cina oua.\nUnul insa s-a-necat si-au rămas doar noua."
#
#     mybook = Book(title, author, desc)
#     # print(mybook)
#     assert mybook.getId() == 2
#     assert mybook.getTitle() == title
#     assert mybook.getAuthor() == author
#     assert mybook.getDescription() == desc
#     assert mybook.getTotalCopies() == 1
#     assert mybook.getBorrows() == 0
#
#     mybook.setTitle("test")
#     mybook.setAuthor("test")
#     mybook.setTotalCopies(10)
#     mybook.setDescription("test\ntest")
#
#     assert mybook.getTitle() == "test"
#     assert mybook.getAuthor() == "test"
#     assert mybook.getTotalCopies() == 10
#     assert mybook.getDescription() == "test\ntest"
#
# test_init_id_title_author_descrp_copis_borrows()
# test_change_title_author_copies_descrp()
# # title = "10 Negrii Mititei"
# # author = "Agatha Christie"
# # desc = "Zece negri mititei au mancat la cina oua.\nUnul insa s-a-necat si-au rămas doar noua."
# # testbook = Book(title, author, desc)
# # print(testbook)

