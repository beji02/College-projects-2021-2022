from Project.____Domain.Entities.Event import Event
from Project._____Utils.Exceptions import FileError
from Project.___Repository.EventRepo import EventRepository


class EventFileRepository(EventRepository):

    def __init__(self, FileName, ClientRepo, BookRepo):
        EventRepository.__init__(self)
        self.__file_name = FileName
        self.__client_repo = ClientRepo
        self.__book_repo = BookRepo
        self.load_from_file()

    def load_from_file(self):
        """
        preia informatia din fisier si o salveam in memorie
        :return: None
        """
        EventRepository.getList(self).clear()

        try:
            f = open(self.__file_name, "r")
        except OSError:
            return
        try:
            for line in f:
                res = line.split()
                event = Event(res[0],
                                self.__client_repo.findClient(int(res[1])),
                                self.__book_repo.findBook(int(res[2])),
                                res[3],
                                res[4]
                                )
                EventRepository.getList(self).append(event)
        finally:
            f.close()
    def store_to_file(self):
        f = open(self.__file_name, "w")
        try:
            for el in self.getList():
                text = '{:<15}'.format(el.getType()) \
                       + '{:<15}'.format(el.getClient().getId()) \
                       + '{:<30}'.format(el.getBook().getId()) \
                       + '{:<15}'.format(el.getDate()) \
                       + '{:<15}'.format(el.getTime()) \
                       + "\n"
                f.write(text)
        except IOError:
            raise FileError
        finally:
            f.close()


    # def load_from_file(self):
    #     """
    #     preia informatia din fisier si o salveam in memorie
    #     :return: None
    #     """
    #     EventRepository.getList(self).clear()
    #
    #     try:
    #         f = open(self.__file_name, "r")
    #     except OSError:
    #         return
    #     try:
    #         lines = f.readlines()
    #         n = len(lines) // 5
    #         for i in range(n):
    #             event = Event(lines[i*5+0].strip(),
    #                             self.__client_repo.findClient(int(lines[i*5+1].strip())),
    #                             self.__book_repo.findBook(int(lines[i*5+2].strip())),
    #                             lines[i*5+3].strip(),
    #                             lines[i*5+4].strip()
    #                             )
    #             EventRepository.getList(self).append(event)
    #     finally:
    #         f.close()
    # def store_to_file(self):
    #     f = open(self.__file_name, "w")
    #     try:
    #         for el in self.getList():
    #             text = '{:<15}'.format(el.getType()) +"\n" \
    #                    + '{:<15}'.format(el.getClient().getId()) +"\n"  \
    #                    + '{:<30}'.format(el.getBook().getId())  +"\n" \
    #                    + '{:<15}'.format(el.getDate()) +"\n"  \
    #                    + '{:<15}'.format(el.getTime()) +"\n"
    #             f.write(text)
    #     except IOError:
    #         raise FileError
    #     finally:
    #         f.close()


    def store(self, newEvent):
        """
        salveaza un nou eveniment in memorie
        :param newEvent: Event: noul eveniment
        :return: None
        """
        EventRepository.store(self, newEvent)
        self.store_to_file()
    def delete(self, Event):
        """
        sterge un obiect eveniment din memorie si din fisier
        :param Event: Event: evenimentul care va fi sters
        :return: None
        """
        EventRepository.delete(self, Event)
        self.store_to_file()
    # def clear(self):
    #     EventRepository.getList(self).clear()
    #
    #     f = open(self.__file_name, "w")
    #     try:
    #         for el in self.getList():
    #             text = '{:<15}'.format(el.getType()) \
    #                    + '{:<15}'.format(el.getClient().getId()) \
    #                    + '{:<30}'.format(el.getBook().getId()) \
    #                    + '{:<15}'.format(el.getDate()) \
    #                    + '{:<15}'.format(el.getTime()) \
    #                    + "\n"
    #             f.write(text)
    #     except IOError:
    #         raise FileError
    #     finally:
    #         f.close()


# def test_store():
#     repo_books = BookRepository()
#     repo_clients = ClientRepository()
#
#     book = Book("test", "test")
#     client = Client("Bejan", "Andrei", "0743155516")
#     newEvent = Event("borrow", client, book)
#
#     repo_books.append(book)
#     repo_clients.addClient(client)
#
#     repo = EventFileRepository("events.txt", repo_clients, repo_books)
#
#     repo.store(newEvent)
#     list = repo.getAll()
#     assert list[0] == newEvent
#
#     repo.load_from_file()
#     list = repo.getAll()
#     assert list[0] == newEvent
#     repo.delete(newEvent)
# test_store()
#
# class TestEventFileRepository(unittest.TestCase):
#
#     def setUp(self) -> None:
#         self.__book = Book("test", "test")
#         repo_books = BookRepository()
#         repo_books.append(self.__book)
#
#         self.__client = Client("Bejan", "Andrei", "0743155516")
#         repo_clients = ClientRepository()
#         repo_clients.addClient(self.__client)
#
#         self.__new_event = Event("borrow", self.__client, self.__book)
#         self.__repo_events = EventFileRepository("testEvents.txt", repo_clients, repo_books)
#
#     def test_store(self):
#         self.__repo_events.store(self.__new_event)
#         list = self.__repo_events.getAll()
#         self.assertTrue(list[0] == self.__new_event)
#
#         self.__repo_events.load_from_file()
#         list = self.__repo_events.getAll()
#         self.assertTrue(list[0] == self.__new_event)
#
#
#
#     def tearDown(self) -> None:
#         self.__repo_events.clear()

