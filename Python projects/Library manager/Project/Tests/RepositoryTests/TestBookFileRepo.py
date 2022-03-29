import unittest
import os
from Project.___Repository.BookFileRepo import BookFileRepository
from Project.____Domain.Entities.Book import Book


class TestBookFileRepo(unittest.TestCase):
    def test_append(self):
        repo = BookFileRepository("testbooks.txt")
        book = Book("test", "test")
        repo.append(book)

        list = repo.getAll()
        self.assertEqual(list[0], book)

        repo.load_from_file()
        list = repo.getAll()

        self.assertEqual(list[0], book)
    def test_load_from_file(self):
        repo = BookFileRepository("testbooks.txt")
        book = Book("test", "test")
        repo.append(book)

        list = repo.getAll()
        self.assertEqual(list[0], book)

        repo2 = BookFileRepository("testbooks.txt")
        list = repo2.getAll()
        self.assertEqual(list[0], book)
    def test_remove(self):
        repo = BookFileRepository("testbooks.txt")
        book = Book("test", "test")

        repo.append(book)
        repo.remove(book)

        list = repo.getAll()
        self.assertFalse(list)

        repo.load_from_file()
        list = repo.getAll()
        self.assertFalse(list)

    def tearDown(self):
        os.remove("testbooks.txt")
