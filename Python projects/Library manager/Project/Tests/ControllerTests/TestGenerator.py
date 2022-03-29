import unittest
from Project.__Controller.Generator import Generator

class TestGenerator(unittest.TestCase):
    def test_generate_book_repository(self):
        book_repo = Generator.generate_book_repository()
        all = book_repo.getAll()
        self.assertEqual(len(all), 5)
    def test_generate_client_repository(self):
        client_repo = Generator.generate_client_repository()
        all = client_repo.getAll()
        self.assertEqual(len(all), 4)
    def test_generate_event_repository(self):
        book_repo = Generator.generate_book_repository()
        client_repo = Generator.generate_client_repository()

        event_repo = Generator.generate_event_repository(book_repo, client_repo)
        all = event_repo.getAll()
        self.assertEqual(len(all), 8)