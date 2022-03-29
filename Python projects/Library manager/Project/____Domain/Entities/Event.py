from datetime import datetime, date

from ____Domain.Entities.Book import Book
from Project.____Domain.Entities.Client import Client


class Event:
    def __init__(self, type, client, book, mydate=None, mytime=None):
        """
        initializeaza un nou eveniment care contine
        informatii despre tipul evenimentului, data si ora, client si carte
        :param type: str: tipul noului eveniment: borrow/return
        :param client: Client: clientul implicat in eveniment
        :param book: Book: cartea implicata in eveniment
        """
        self.__type = type
        if mydate is None:
            self.__date = date.today().strftime("%d/%m/%Y")
        else:
            self.__date = mydate
        if mytime is None:
            self.__time = datetime.now().strftime("%H:%M:%S")
        else:
            self.__time = mytime
        self.__client = client
        self.__book = book


    def __str__(self):
        """
        formateaza evenimentul pentru afisarea sub forma de string
        :return: str: reprezentarea sub forma de text a evenimentului
        """
        text = '{:<15}'.format(self.getType()) \
                + '{:<15}'.format(self.getClient().getId()) \
                + '{:<30}'.format(self.getBook().getTitle()) \
                + '{:<30}'.format(self.getBook().getAuthor()) \
                + '{:<15}'.format(self.getDate()) \
                + '{:<15}'.format(self.getTime())
        return text
    def __eq__(self, other):
        """
        defineste egalitatea dintre 2 evenimente daca toate campurile celor 2 evenimente sunt identice
        :param other: Event: evenimentul cu care se compara
        :return: True daca sunt egale
                 False altfel
        """
        if self.getType() == other.getType() and \
            self.getDate() == other.getDate() and \
            self.getTime() == other.getTime() and \
            self.getClient() == other.getClient() and \
            self.getBook() == other.getBook():
            return True
        return False

    def getType(self):
        """
        returneaza tipul evenimentului: borrow/return
        :return: str
        """
        return self.__type
    def getDate(self):
        """
        returneaza data evenimentului
        :return: str: data event
        """
        return self.__date
    def getTime(self):
        """
        returneaza timpul la care s-a intamplat evenimentul
        :return: str: ora:min:sec
        """
        return self.__time
    def getClient(self):
        """
        returneaza clientul implicat in event
        :return: Client: clientul implicat
        """
        return self.__client
    def getBook(self):
        """
        returneaza cartea implicata in event
        :return: Book: cartea implicata
        """
        return self.__book

    def setType(self, type):
        """
        seteaza un nou tip evenimentului
        :param type: str: borrow/return
        :return: none
        """
        self.__type = type
    def setDate(self, date):
        """
        seteaza o noua data evenimentului
        :param date: str: noua data
        :return: none
        """
        self.__date = date
    def setTime(self, time):
        """
        seteaza un nou moment al zilei evenimentului
        :param time: str: noul moment al zile
        :return: none
        """
        self.__time = time
    def setClient(self, client):
        """
        seteaza un nou client unui eveniment
        :param client: Client: noul client
        :return: none
        """
        self.__client = client
    def setBook(self, book):
        """
        seteaza o noua carte evenimentului
        :param book: Book: noua carte
        :return: none
        """
        self.__book = book


# def test_getters_setters():
#     client = Client("Bejan", "Andrei", "0743155516")
#     client2 = Client("Beji", "Andrei", "0743155516")
#     book = Book("Da Vinci Code", "Dan Brown")
#     book2 = Book("Da Vinci Code part 2", "Dan Brown")
#     event = Event("borrow", client, book)
#     event2 = Event("return", client2, book2)
#
#     assert event.getType() == "borrow"
#     assert event.getDate() == event2.getDate()
#     assert event.getBook() == book
#     assert event.getClient() == client
#
#     event.setType("return")
#     event.setTime(event2.getTime())
#     event.setClient(client2)
#     event.setBook(book2)
#
#     assert event == event2
# def test_eq():
#     client = Client("Bejan", "Andrei", "0743155516")
#     book = Book("Da Vinci Code", "Dan Brown")
#
#     event = Event("borrow", client, book)
#     event2 = Event("return", client, book)
#
#     assert event != event2
#
# test_getters_setters()
# test_eq()
#
# # client = Client("Bejan", "Andrei", "0743155516")
# # book = Book("Da Vinci Code", "Dan Brown")
# # event = Event("borrow", client, book)
# # event2 = Event("return", client, book)
# # print(event)
# # print(event2)
# # print(event == event2)