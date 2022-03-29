import unittest

from Project.___Repository.BookRepo import BookRepository
from Project.____Domain.Entities.Book import Book


class TestBookRepo(unittest.TestCase):
    def test_getAll(self):
        list = [
            Book("test", "test", "test", 10, k_borrows=1),
            Book("test1", "test", "test", 20, k_borrows=2),
            Book("test2", "test", "test", 30, k_borrows=3),
            Book("test3", "test", "test", 30, k_borrows=4),
        ]
        repo = BookRepository()
        for el in list:
            repo.append(el)

        self.assertEqual(repo.getAll(), list)
    def test_find(self):
        actual_book = Book("test", "test", "test", 10, k_borrows=1)
        list = [
            actual_book,
            Book("test1", "test", "test", 20, k_borrows=2),
            Book("test2", "test", "test", 30, k_borrows=3),
            Book("test3", "test", "test", 30, k_borrows=4),
        ]
        mybook = Book("test", "test", "test", 10, k_borrows=1)

        repo = BookRepository()
        for el in list:
            repo.append(el)
        self.assertEqual(repo.find(mybook), actual_book)
    def test_append(self):
        actual_book = Book("test", "test", "test", 10, k_borrows=1)
        list = [
            Book("test1", "test", "test", 20, k_borrows=2),
            Book("test2", "test", "test", 30, k_borrows=3),
            Book("test3", "test", "test", 30, k_borrows=4),
        ]
        repo = BookRepository()
        for el in list:
            repo.append(el)
        repo.append(actual_book)

        l = repo.getAll()[-1]
        self.assertEqual(l, actual_book)
    def test_remove(self):
        actual_book = Book("test", "test", "test", 10, k_borrows=1)
        list = [
            actual_book,
            Book("test1", "test", "test", 20, k_borrows=2),
            Book("test2", "test", "test", 30, k_borrows=3),
            Book("test3", "test", "test", 30, k_borrows=4),
        ]
        repo = BookRepository()
        for el in list:
            repo.append(el)
        repo.remove(actual_book)

        self.assertEqual(repo.find(actual_book), None)

    def test_findClientRec(self):
        actual_book = Book("test", "test", "test", 10, k_borrows=1)
        list = [
            actual_book,
            Book("test1", "test", "test", 20, k_borrows=2),
            Book("test2", "test", "test", 30, k_borrows=3),
            Book("test3", "test", "test", 30, k_borrows=4),
        ]
        mybook = Book("test", "test", "test", 10, k_borrows=1)

        repo = BookRepository()
        for el in list:
            repo.append(el)
        self.assertEqual(repo.findBookRec(actual_book.getId()), actual_book)
        self.assertIs(repo.findBookRec(mybook.getId()), None)


