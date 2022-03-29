import unittest

from Project.__Controller.BookService import BookService
from Project.___Repository.BookRepo import BookRepository
from Project.____Domain.Validators.Validator import Validator
from Project._____Utils.Exceptions import duplicatedBookError, bookNotInMemError, noBooksInMemError


class TestBookService(unittest.TestCase):
    def test_adauga_carte(self):
        validator = Validator()
        bookRepository = BookRepository()
        bookService = BookService(bookRepository, validator)
        bookService.adauga_carte("Ana", "Maria", "pisici", 10)

        self.assertEqual(len(bookRepository.getAll()), 1)

        try:
            bookService.adauga_carte("Ana", "Maria", "pisici", 10)
            self.assertTrue(False)
        except duplicatedBookError:
            self.assertTrue(True)
    def test_sterge_carte(self):
        """ specificatiile dupa care testam
        sterge o carte din memorie
        :param title: str: titlu
        :param author: str: autor
        :return: none
        :raises: bookNotInMemError daca cartea nu e in memorie
        """
        validator = Validator()
        bookRepository = BookRepository()
        bookService = BookService(bookRepository, validator)
        bookService.adauga_carte("Ana", "Maria", "roman", 10)

        bookService.sterge_carte("Ana", "Maria")
        self.assertEqual(len(bookRepository.getAll()), 0)


        self.assertRaises(bookNotInMemError, bookService.sterge_carte, "Ana", "Maria")
        # try:
        #     bookService.sterge_carte("Ana", "Maria")
        #     self.assertTrue(False)
        # except bookNotInMemError:
        #     self.assertTrue(True)

    def test_modifica_carte(self):
        validator = Validator()
        bookRepository = BookRepository()
        bookService = BookService(bookRepository, validator)
        bookService.adauga_carte("Ana", "Maria", "pisici", 10)

        bookService.modifica_carte("Ana", "Maria", "Pisici")

        self.assertEqual(bookRepository.getAll()[0].getTitle(), "Pisici")

        try:
            bookService.modifica_carte("Ana", "Maria")
            self.assertTrue(False)
        except bookNotInMemError:
            self.assertTrue(True)
    def test_cautare(self):
        validator = Validator()
        bookRepository = BookRepository()
        bookService = BookService(bookRepository, validator)
        bookService.adauga_carte("Ana", "Maria", "pisici", 10)

        self.assertEqual(bookService.cauta_exemplare_carte("Ana", "Maria"), 10)

        try:
            bookService.sterge_carte("Ana", "nush")
            self.assertTrue(False)
        except bookNotInMemError:
            self.assertTrue(True)
    # def test_raport(self):
    #     validator = Validator()
    #     bookRepository = BookRepository()
    #     bookService = BookService(bookRepository, validator)
    #     bookService.adauga_carte("Ana", "Maria", "pisici", 10)
    #
    #     self.assertIsNot(bookService.raport_carti_inchiriate(), None)
    #
    #     try:
    #         bookService.sterge_carte("Ana", "Maria")
    #         bookService.raport_carti_inchiriate()
    #         self.assertTrue(False)
    #     except noBooksInMemError:
    #         self.assertTrue(True)