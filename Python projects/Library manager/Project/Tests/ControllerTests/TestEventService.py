import unittest

from Project.__Controller.EventService import EventService
from Project.____Domain.Validators.Validator import Validator
from Project.__Controller.Generator import Generator

class TestEventService(unittest.TestCase):
    def test_inchiriere_carte(self):
        validator = Validator()
        generator = Generator()
        bookRepository, clientRepository, eventRepository = generator.generateData()
        eventService = EventService(eventRepository, bookRepository, clientRepository, validator)

        id = clientRepository.getAll()[0].getId()
        lenght = len(eventRepository.getAll())
        eventService.inchiriere_carte(id, "test", "test")

        self.assertEqual(lenght + 1, len(eventRepository.getAll()))
    def test_verify_book_borrowed(self):
        validator = Validator()
        generator = Generator()
        bookRepository, clientRepository, eventRepository = generator.generateData()
        eventService = EventService(eventRepository, bookRepository, clientRepository, validator)

        id = clientRepository.getAll()[0].getId()
        eventService.inchiriere_carte(id, "test", "test")
        self.assertIs(eventService.verify_book_borrowed(clientRepository.getClient(id),
                                                 bookRepository.getBook("test", "test")), None)
    def test_returnare_carte(self):
        validator = Validator()
        generator = Generator()
        bookRepository, clientRepository, eventRepository = generator.generateData()
        eventService = EventService(eventRepository, bookRepository, clientRepository, validator)

        id = clientRepository.getAll()[0].getId()
        before = clientRepository.findClient(id).getPresentBorrows()
        eventService.inchiriere_carte(id, "test", "test")
        eventService.returnare_carte(id, "test", "test")
        self.assertEqual(before, clientRepository.findClient(id).getPresentBorrows())