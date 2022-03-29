import unittest

from Project.___Repository.EventRepo import EventRepository
from Project.____Domain.Entities.Book import Book
from Project.____Domain.Entities.Client import Client
from Project.____Domain.Entities.Event import Event



class TestEventRepository(unittest.TestCase):
    def test_find(self):
        repo = EventRepository()
        book = Book("test", "test")
        client = Client("Bejan", "Andrei", "0743155516")
        newEvent = Event("borrow", client, book)

        repo.store(newEvent)
        self.assertEqual(repo.find(newEvent), True)
        repo.delete(newEvent)
        self.assertEqual(repo.find(newEvent), False)
    def test_delete(self):
        repo = EventRepository()
        book = Book("test", "test")
        client = Client("Bejan", "Andrei", "0743155516")
        newEvent = Event("borrow", client, book)

        repo.store(newEvent)
        repo.delete(newEvent)
        self.assertEqual(len(repo.getAll()), 0)
    def test_getAll(self):
        repo = EventRepository()
        book = Book("test", "test")
        client = Client("Bejan", "Andrei", "0743155516")
        newEvent = Event("borrow", client, book)

        repo.store(newEvent)
        list = repo.getAll()
        self.assertEqual(list[0], newEvent)
    def test_store(self):
        repo = EventRepository()
        book = Book("test", "test")
        client = Client("Bejan", "Andrei", "0743155516")
        newEvent = Event("borrow", client, book)

        repo.store(newEvent)
        list = repo.getAll()
        self.assertEqual(list[0], newEvent)
