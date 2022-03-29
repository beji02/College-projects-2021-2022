from Project.____Domain.Entities.Book import Book
from Project.____Domain.Entities.Client import Client
from Project.____Domain.Entities.Event import Event
from Project._____Utils.Utils import copy_list

class EventRepository():
    def __init__(self):
        """
        creeaza un repositori cu evenimente (borrow/ return)
        contine doar o lista de evenimente
        """
        self.__list_of_events = []

    def getList(self):
        """
        returneaza adresa catre lista de evenimente
        :return: list of events: lista cu evenimente din memorie
        """
        return self.__list_of_events
    def __setList(self, newList):
        """
        seteaza o noua lista ca lista de evenimente actuala
        :param newList: o lista de evenimente noua
        :return: none
        """
        self.__list_of_events = copy_list(newList)

    def store(self, newEvent):
        """
        adauga un nou eveniment in lista
        :param newEvent: evenimentul nou
        :return: none
        """
        self.getList().append(newEvent)
    def delete(self, Event):
        """
        sterge un eveniment din repository
        :param Event: evenimentul care urmeaza sa fie sters
        :return: none
        """
        self.getList().remove(Event)
    def find(self, Event):
        """
        verifica daca un eveniment se afla in repository
        :param Event: evenimentul cautat
        :return: True daca exista in memorie
                 False altfel
        """
        if Event in self.getList():
            return True
        return False
    def getAll(self):
        """
        returneaza o copie a listei din repository
        :return: list of events: copia listei cu evenimente
        """
        return copy_list(self.getList())

#
# def test_find():
#     repo = EventRepository()
#     book = Book("test", "test")
#     client = Client("Bejan", "Andrei", "0743155516")
#     newEvent = Event("borrow", client, book)
#
#     repo.store(newEvent)
#     assert repo.find(newEvent) == True
#     repo.delete(newEvent)
#     assert repo.find(newEvent) == False
# def test_delete():
#     repo = EventRepository()
#     book = Book("test", "test")
#     client = Client("Bejan", "Andrei", "0743155516")
#     newEvent = Event("borrow", client, book)
#
#     repo.store(newEvent)
#     repo.delete(newEvent)
#     assert len(repo.getAll()) == 0
# def test_getAll():
#     repo = EventRepository()
#     book = Book("test", "test")
#     client = Client("Bejan", "Andrei", "0743155516")
#     newEvent = Event("borrow", client, book)
#
#     repo.store(newEvent)
#     list = repo.getAll()
#     assert list[0] == newEvent
# def test_store():
#     repo = EventRepository()
#     book = Book("test", "test")
#     client = Client("Bejan", "Andrei", "0743155516")
#     newEvent = Event("borrow", client, book)
#
#     repo.store(newEvent)
#     list = repo.getAll()
#     assert list[0] == newEvent
#
# test_store()
# test_getAll()
# test_delete()
# test_find()