from Project.____Domain.Entities.Book import Book
from Project.____Domain.Validators.Validator import Validator
from Project._____Utils.Exceptions import bookNotInMemError, duplicatedBookError, noBooksInMemError, shouldNotBeRaisedError
from Project.___Repository.BookRepo import BookRepository
class BookService:
    def __init__(self, bookRepo, validator):
        """
        initializeaza un nou service pentru carti care are acces la repositoriul de carti si la un validator
        :param bookRepo: repositoriul cu carti
        :param validator: validatorul de obiecte
        """
        self.__bookRepo = bookRepo
        self.__validator = validator

    def adauga_carte(self, title, author, description, k_copies=1):
        """
        adauga o carte nou in memorie
        :param title: str: titlu
        :param author: str: autor
        :param description: str: descriere
        :param k_copies: int: nr exemplare
        :return: none
        :raises: duplicatedBookError daca cartea e deja in memorie
        """
        new_book = Book(title, author, description, k_copies)
        self.__validator.validateBook(new_book)

        book_in_memory = self.__bookRepo.find(new_book)
        if book_in_memory is not None:
            raise duplicatedBookError

        self.__bookRepo.append(new_book)
    def sterge_carte(self, title, author):
        """
        sterge o carte din memorie
        :param title: str: titlu
        :param author: str: autor
        :return: none
        :raises: bookNotInMemError daca cartea nu e in memorie
        """
        new_book = Book(title, author)
        self.__validator.validateBook(new_book)

        book_in_memory = self.__bookRepo.find(new_book)
        if book_in_memory is None:
            raise bookNotInMemError

        self.__bookRepo.remove(book_in_memory)
    def modifica_carte(self, title, author, newTitle=None, newAuthor=None, new_k_copies=None, new_desc=None):
        """
        modifica un camp dintr-o carte din memorie
        :param title: str: titlu
        :param author: str: autor
        :param newTitle: str: titlu nou
        :param newAuthor: str: autor nou
        :param new_k_copies: int: nr exemplare nou
        :param new_desc: str: descriere noua
        :return: none
        :raises: bookNotInMemError daca cartea nu e in memorie
        """
        new_book = Book(title, author)
        self.__validator.validateBook(new_book)

        book_in_memory = self.__bookRepo.find(new_book)
        if book_in_memory is None:
            raise bookNotInMemError

        self.__bookRepo.remove(book_in_memory)
        if newTitle is not None:
            try_book = Book(newTitle, author)
            self.__validator.validateBook(try_book)
            if self.__bookRepo.find(try_book) is not None:
                raise duplicatedBookError

            book_in_memory.setTitle(newTitle)
        elif newAuthor is not None:
            try_book = Book(title, newAuthor)
            self.__validator.validateBook(try_book)
            if self.__bookRepo.find(try_book) is not None:
                raise duplicatedBookError

            book_in_memory.setAuthor(newAuthor)
        elif new_k_copies is not None:
            book_in_memory.setTotalCopies(new_k_copies)
        elif new_desc is not None:
            book_in_memory.setDescription(new_desc)
        else:
            raise shouldNotBeRaisedError
        self.__bookRepo.append(book_in_memory)

    def cauta_exemplare_carte(self, title, author):
        """
        returneaza numarul de exemplare dintr-o carte
        :param title: str: titlu
        :param author: str: autor
        :return: int: nr exemplare
        :raises: bookNotInMemError daca cartea nu exista in memorie
        """
        new_book = Book(title, author)
        self.__validator.validateBook(new_book)

        book_in_memory = self.__bookRepo.find(new_book)
        if book_in_memory is None:
            raise bookNotInMemError

        k_copies = book_in_memory.getTotalCopies()
        return k_copies
    # def raport_carti_inchiriate(self):
    #     """
    #     creeaza un raport cu cartile sortate dupa nr de inchirieri
    #     :return: str: un text cu toate cartile sortate
    #     """
    #     if len(self.__bookRepo.getAll()) == 0:
    #         raise noBooksInMemError
    #
    #     self.__bookRepo.sort_by(byBorrows=1, reverse=True)
    #     raport = self.__bookRepo.get_report()
    #     return raport


# def test_adauga_carte():
#     validator = Validator()
#     bookRepository = BookRepository()
#     bookService = BookService(bookRepository, validator)
#     bookService.adauga_carte("Ana", "Maria", "pisici", 10)
#
#     assert len(bookRepository.getAll()) == 1
#
#     try:
#         bookService.adauga_carte("Ana", "Maria", "pisici", 10)
#         assert False
#     except duplicatedBookError:
#         assert True
# def test_sterge_carte():
#     validator = Validator()
#     bookRepository = BookRepository()
#     bookService = BookService(bookRepository, validator)
#     bookService.adauga_carte("Ana", "Maria", "pisici", 10)
#     bookService.sterge_carte("Ana", "Maria")
#
#     assert len(bookRepository.getAll()) == 0
#
#     try:
#         bookService.sterge_carte("Ana", "Maria")
#         assert False
#     except bookNotInMemError:
#         assert True
# def test_modifica_carte():
#     validator = Validator()
#     bookRepository = BookRepository()
#     bookService = BookService(bookRepository, validator)
#     bookService.adauga_carte("Ana", "Maria", "pisici", 10)
#
#     bookService.modifica_carte("Ana", "Maria", "Pisici")
#
#     assert bookRepository.getAll()[0].getTitle() == "Pisici"
#
#     try:
#         bookService.modifica_carte("Ana", "Maria")
#         assert False
#     except bookNotInMemError:
#         assert True
# def test_cautare():
#     validator = Validator()
#     bookRepository = BookRepository()
#     bookService = BookService(bookRepository, validator)
#     bookService.adauga_carte("Ana", "Maria", "pisici", 10)
#
#     assert bookService.cauta_exemplare_carte("Ana", "Maria") == 10
#
#     try:
#         bookService.sterge_carte("Ana", "nush")
#         assert False
#     except bookNotInMemError:
#         assert True
# def test_raport():
#     validator = Validator()
#     bookRepository = BookRepository()
#     bookService = BookService(bookRepository, validator)
#     bookService.adauga_carte("Ana", "Maria", "pisici", 10)
#
#     assert bookService.raport_carti_inchiriate() is not None
#
#     try:
#         bookService.sterge_carte("Ana", "Maria")
#         bookService.raport_carti_inchiriate()
#         assert False
#     except noBooksInMemError:
#         assert True
#
#
# test_adauga_carte()
# test_sterge_carte()
# test_modifica_carte()
# test_cautare()
# test_raport()