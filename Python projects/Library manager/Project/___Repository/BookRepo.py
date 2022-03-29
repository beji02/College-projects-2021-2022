from Project.____Domain.Entities.Book import Book
from Project._____Utils.Exceptions import bookNotInMemError
from Project._____Utils.Utils import copy_list

class BookRepository:
    def __init__(self):
        """
        initializeaza un nou repository de carti
        contine doar o lista de carti
        """
        self.__list_of_books = []

    def getList(self):
        """
        returneaza adevarata lista de carti
        :return: list
        """
        return self.__list_of_books
    def getAll(self):
        """
        returneaza o copie a listei de carti
        :return: list
        """
        return copy_list(self.__list_of_books)

    # def sort_by(self, byTitle = None, byCopies = None, byBorrows = None, reverse = False):
    #     """
    #     sorteaza lista de carti din memorie dupa un parametru
    #     :param byTitle: sorteaza dupa titlu
    #     :param byCopies: sorteaza dupa nrexemplare
    #     :param byBorrows: sorteaza dupa nr imprumuturi
    #     :param reverse: sorteaza descrescator
    #     :return: none
    #     """
    #     books = self.__get_list()
    #     if byTitle is not None:
    #         books.sort(key=lambda x: x.getTitle(), reverse = reverse)
    #     elif byCopies is not None:
    #         books.sort(key=lambda x: x.getTotalCopies(), reverse = reverse)
    #     elif byBorrows is not None:
    #         books.sort(key=lambda x: x.getBorrows(), reverse = reverse)
    # def get_report(self):
    #     """
    #     creeaza un text care semnifica lista de carti din memorie
    #     :return: str: textul care include lista
    #     """
    #     table = '{:<30}'.format("ID") \
    #             + '{:<35}'.format("TITLU") \
    #             + '{:<30}'.format("AUTOR") \
    #             + '{:<30}'.format("NR EXEMPLARE") \
    #             + '{:<30}'.format("DE CATE ORI A FOST IMPRUMUTATA")
    #     for book in self.getAll():
    #         table = table + "\n" + str(book)
    #     return table

    def find(self, book):
        """
        cauta o carte in lista
        :param book: Book
        :return: cartea din memorie daca exista sau None altfel
        """
        books = self.getAll()
        for book_in_mem in books:
            if book_in_mem == book:
                return book_in_mem
        return None

    def findBookRec(self, id, book_list = None):
        """
        returneaza clientul cu idul id daca exista, daca nu returneaza None
        :param id: id ul clientului cautat
        :return: client: obiectul cautat din lista
        """
        if book_list is None:
            book_list = self.getAll()
        if len(book_list) == 0:
            return None
        book = book_list[0]
        if book.getId() == id:
            return book
        else:
            return self.findBookRec(id, book_list[1:])

    def findBook(self, id):
        """
        returneaza clientul cu idul id daca exista, daca nu returneaza None
        :param id: id ul clientului cautat
        :return: client: obiectul cautat din lista
        """
        book_list = self.getList()
        for book in book_list:
            if book.getId() == id:
                return book
        return None
    def getBook(self, title, author):
        """
        cauta o carte in lista
        :param book: Book
        :return: cartea din memorie daca exista sau None altfel
        """
        books = self.getAll()
        for book_in_mem in books:
            if book_in_mem.getTitle() == title and \
                book_in_mem.getAuthor() == author:
                return book_in_mem
        raise bookNotInMemError
    def append(self, book):
        """
        adauga o carte la sf listei
        :param book: Book
        :return: none
        """
        self.getList().append(book)
    def remove(self, book_in_mem):
        """
        sterge o carte din memorie
        :param book_in_mem: Book
        :return: none
        """
        self.getList().remove(book_in_mem)

def generate_books_repo():
    """
    genereaza o lista de carti
    :return: book repo
    """
    repo = BookRepository()
    title = "10 Negrii Mititei"
    author = "Agatha Christie"
    desc = "Zece negri mititei au mancat la cina oua.\nUnul insa s-a-necat si-au rămas doar noua."
    mybook = Book(title, author, desc, k_copies=10, k_borrows=9)
    repo.append(mybook)

    title = "Craciunul lui Poirot"
    mybook = Book(title, author, desc, k_copies=4, k_borrows=10)
    repo.append(mybook)

    title = "Crima din Orient Express"
    mybook = Book(title, author, desc, k_copies=3, k_borrows=3)
    repo.append(mybook)

    title = "Misterul din Caraibe"
    mybook = Book(title, author, desc, k_copies=0, k_borrows=4)
    repo.append(mybook)

    title = "test"
    author = "test"
    mybook = Book(title, author, desc, k_copies=10, k_borrows=20)
    repo.append(mybook)

    return repo
#
#
#
# def test_get_list():
#     list = [
#         Book("test", "test", "test", 10, k_borrows=1),
#         Book("test1", "test", "test", 20, k_borrows=2),
#         Book("test2", "test", "test", 30, k_borrows=3),
#         Book("test3", "test", "test", 30, k_borrows=4),
#     ]
#     repo = BookRepository()
#     for el in list:
#         repo.append(el)
#
#     assert repo.getAll() == list
#
# # def test_sort_by():
# #     list = [
# #         Book("test", "test", "test", 10, k_borrows=1),
# #         Book("test1", "test", "test", 20, k_borrows=2),
# #         Book("test2", "test", "test", 30, k_borrows=3),
# #         Book("test3", "test", "test", 30, k_borrows=4),
# #     ]
# #     list2 = [
# #         Book("test3", "test", "test", 30, k_borrows=4),
# #         Book("test2", "test", "test", 30, k_borrows=3),
# #         Book("test1", "test", "test", 20, k_borrows=2),
# #         Book("test", "test", "test", 10, k_borrows=1),
# #     ]
# #     repo = BookRepository()
# #     for el in list:
# #         repo.append(el)
# #     repo.sort_by(byTitle=1, reverse = True)
# #     assert repo.getAll() == list2
# def test_find():
#     actual_book = Book("test", "test", "test", 10, k_borrows=1)
#     list = [
#         actual_book,
#         Book("test1", "test", "test", 20, k_borrows=2),
#         Book("test2", "test", "test", 30, k_borrows=3),
#         Book("test3", "test", "test", 30, k_borrows=4),
#     ]
#     mybook = Book("test", "test", "test", 10, k_borrows=1)
#
#     repo = BookRepository()
#     for el in list:
#         repo.append(el)
#     assert repo.find(mybook) == actual_book
# def test_append():
#     actual_book = Book("test", "test", "test", 10, k_borrows=1)
#     list = [
#         Book("test1", "test", "test", 20, k_borrows=2),
#         Book("test2", "test", "test", 30, k_borrows=3),
#         Book("test3", "test", "test", 30, k_borrows=4),
#     ]
#     repo = BookRepository()
#     for el in list:
#         repo.append(el)
#     repo.append(actual_book)
#
#     l = repo.getAll()[-1]
#     assert l == actual_book
# def test_remove():
#     actual_book = Book("test", "test", "test", 10, k_borrows=1)
#     list = [
#         actual_book,
#         Book("test1", "test", "test", 20, k_borrows=2),
#         Book("test2", "test", "test", 30, k_borrows=3),
#         Book("test3", "test", "test", 30, k_borrows=4),
#     ]
#     repo = BookRepository()
#     for el in list:
#         repo.append(el)
#     repo.remove(actual_book)
#
#     assert repo.find(actual_book) == None
#
# #test_sort_by()
# test_get_list()
# test_find()
# test_append()
# test_remove()

