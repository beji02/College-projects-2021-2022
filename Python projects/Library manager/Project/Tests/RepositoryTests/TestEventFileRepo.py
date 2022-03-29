import unittest
import os
from Project.___Repository.BookRepo import BookRepository
from Project.___Repository.ClientRepo import ClientRepository
from Project.___Repository.EventFileRepo import EventFileRepository
from Project.____Domain.Entities.Book import Book
from Project.____Domain.Entities.Client import Client
from Project.____Domain.Entities.Event import Event


class TestEventFileRepo(unittest.TestCase):
    def test_store(self):
        repo_books = BookRepository()
        repo_clients = ClientRepository()

        book = Book("test", "test")
        client = Client("Bejan", "Andrei", "0743155516")
        newEvent = Event("borrow", client, book)

        repo_books.append(book)
        repo_clients.addClient(client)

        repo = EventFileRepository("testevents.txt", repo_clients, repo_books)

        repo.store(newEvent)
        list = repo.getAll()
        self.assertEqual(list[0], newEvent)

        repo.load_from_file()
        list = repo.getAll()
        self.assertEqual(list[0], newEvent)
        repo.delete(newEvent)
    def test_load_from_file(self):
        repo_books = BookRepository()
        repo_clients = ClientRepository()

        book = Book("test", "test")
        client = Client("Bejan", "Andrei", "0743155516")
        newEvent = Event("borrow", client, book)

        repo_books.append(book)
        repo_clients.addClient(client)

        repo = EventFileRepository("testevents.txt", repo_clients, repo_books)

        repo.store(newEvent)
        list = repo.getAll()
        repo2 = EventFileRepository("testevents.txt", repo_clients, repo_books)
        self.assertEqual(repo2.getAll(), list)
    def test_delete(self):
        repo_books = BookRepository()
        repo_clients = ClientRepository()

        book = Book("test", "test")
        client = Client("Bejan", "Andrei", "0743155516")
        newEvent = Event("borrow", client, book)

        repo_books.append(book)
        repo_clients.addClient(client)

        repo = EventFileRepository("testevents.txt", repo_clients, repo_books)

        repo.store(newEvent)
        repo.delete(newEvent)
        list = repo.getAll()
        self.assertFalse(list)

        repo.load_from_file()
        list = repo.getAll()
        self.assertFalse(list)
    # def test_clear(self):
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
    #     repo = EventFileRepository("testevents.txt", repo_clients, repo_books)
    #
    #     repo.store(newEvent)
    #     repo.clear()
    #     repo.load_from_file()
    #     list = repo.getAll()
    #     self.assertFalse(list)

    def tearDown(self):
        os.remove("testevents.txt")
