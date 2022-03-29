import unittest

from Project.____Domain.Entities.Book import Book
from Project.____Domain.Entities.Client import Client
from Project.____Domain.Entities.Event import Event


class TestEvent(unittest.TestCase):
    def test_getters(self):
        client = Client("Bejan", "Andrei", "0743155516")
        client2 = Client("Beji", "Andrei", "0743155516")
        book = Book("Da Vinci Code", "Dan Brown")
        book2 = Book("Da Vinci Code part 2", "Dan Brown")
        event = Event("borrow", client, book)
        event2 = Event("return", client2, book2)

        self.assertEqual(event.getType(),"borrow")
        self.assertEqual(event.getDate(), event2.getDate())
        self.assertEqual(event.getBook(), book)
        self.assertEqual(event.getClient(), client)
    def test_setters(self):
        client = Client("Bejan", "Andrei", "0743155516")
        client2 = Client("Beji", "Andrei", "0743155516")
        book = Book("Da Vinci Code", "Dan Brown")
        book2 = Book("Da Vinci Code part 2", "Dan Brown")
        event = Event("borrow", client, book)
        event2 = Event("return", client2, book2)

        event.setType("return")
        event.setTime(event2.getTime())
        event.setClient(client2)
        event.setBook(book2)

        self.assertEqual(event, event2)