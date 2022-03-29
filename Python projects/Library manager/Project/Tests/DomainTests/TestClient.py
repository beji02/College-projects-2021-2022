import unittest
from Project.____Domain.Entities.Client import Client

class TestClient(unittest.TestCase):

    def test_getters(self):
        a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)

        self.assertEqual(a.getName(), "Bejan")
        self.assertEqual(a.getFirstname(), "Andrei")
        self.assertEqual(a.getPhone(), "0743155516")
        self.assertEqual(a.getTotalBorrows(), 10)
        self.assertEqual(a.getPresentBorrows(), 3)
    def test_setters(self):
        a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)

        a.setName("Brita")
        a.setFirstname("Catalin")
        a.setPhone("0777444333")
        a.setTotalBorrows(3)
        a.setPresentBorrows(2)

        self.assertEqual(a.getName(), "Brita")
        self.assertEqual(a.getFirstname(), "Catalin")
        self.assertEqual(a.getPhone(), "0777444333")
        self.assertEqual(a.getTotalBorrows(), 3)
        self.assertEqual(a.getPresentBorrows(), 2)