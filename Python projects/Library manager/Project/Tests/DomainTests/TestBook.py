import unittest

from Project.____Domain.Entities.Book import Book


class TestBook(unittest.TestCase):
    def test_getters(self):
        title = "10 Negrii Mititei"
        author = "Agatha Christie"
        desc = "Zece negri mititei au mancat la cina oua.\nUnul insa s-a-necat si-au rămas doar noua."

        mybook = Book(title, author, desc)

        self.assertEqual(mybook.getTitle(), title)
        self.assertEqual(mybook.getAuthor(), author)
        self.assertEqual(mybook.getDescription(), desc)
        self.assertEqual(mybook.getTotalCopies(), 1)
        self.assertEqual(mybook.getBorrows(), 0)
        self.assertEqual(mybook.getAvailableCopies(), 1)
    def test_setters(self):
        title = "10 Negrii Mititei"
        author = "Agatha Christie"
        desc = "Zece negri mititei au mancat la cina oua.\nUnul insa s-a-necat si-au rămas doar noua."

        mybook = Book(title, author, desc)
        mybook.setTitle("test")
        mybook.setAuthor("test")
        mybook.setDescription("test\ntest")
        mybook.setTotalCopies(100)
        mybook.setBorrows(10)
        mybook.setAvailableCopies(10)

        self.assertEqual(mybook.getTitle(), "test")
        self.assertEqual(mybook.getAuthor(), "test")
        self.assertEqual(mybook.getDescription(), "test\ntest")
        self.assertEqual(mybook.getTotalCopies(), 100)
        self.assertEqual(mybook.getBorrows(), 10)
        self.assertEqual(mybook.getAvailableCopies(), 10)


