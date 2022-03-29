import unittest
from Project.____Domain.Entities.Client import Client
from Project.___Repository.ClientRepo import ClientRepository
from Project._____Utils.Exceptions import clientDuplicatedError, clientNotInMemError


class TestClientRepo(unittest.TestCase):
    def test_addClient(self):
        """
        testeaza functia addclient
        :return: none
        """
        repo = ClientRepository()
        a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)

        repo.addClient(a)
        try:
            repo.addClient(a)
            self.assertTrue(False)
        except clientDuplicatedError:
            self.assertTrue(True)
    def test_findClient(self):
        repo = ClientRepository()
        a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
        b = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)

        repo.addClient(a)
        self.assertEqual(a, repo.findClient(a.getId()))
        self.assertIs(repo.findClient(b.getId()), None)

        repo.addClient(b)
        self.assertEqual(a, repo.findClient(a.getId()))
    def test_deleteClient(self):
        repo = ClientRepository()
        a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
        b = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)

        repo.addClient(a)
        repo.addClient(b)

        repo.deleteClient(a.getId())
        try:
            repo.deleteClient(a.getId())
            self.assertTrue(False)
        except clientNotInMemError:
            self.assertTrue(True)
        repo.deleteClient(b.getId())
    def test_updateClient(self):
        repo = ClientRepository()
        a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
        b = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)

        repo.addClient(a)
        repo.addClient(b)

        a.setPhone("1111122222")
        repo.updateClient(a)
        self.assertEqual(a, repo.findClient(a.getId()))
        self.assertEqual(a.getPhone(), repo.findClient(a.getId()).getPhone())

        repo.deleteClient(a.getId())
        try:
            repo.updateClient(a)
            self.assertTrue(False)
        except clientNotInMemError:
            self.assertTrue(True)
    def test_getClient(self):
        repo = ClientRepository()
        a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
        b = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)

        repo.addClient(a)
        repo.addClient(b)
        self.assertEqual(a, repo.getClient(a.getId()))
        repo.deleteClient(a.getId())
        try:
            aux = repo.getClient(a.getId())
            self.assertTrue(False)
        except clientNotInMemError:
            self.assertTrue(True)

    def test_findClientRec(self):
        repo = ClientRepository()
        a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
        b = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)

        repo.addClient(a)
        self.assertEqual(a, repo.findClientRec(a.getId()))
        self.assertIs(repo.findClientRec(b.getId()), None)

        repo.addClient(b)
        self.assertEqual(a, repo.findClientRec(a.getId()))
    # def test_getListWhoBorrowPresent(self):
    #     repo = ClientRepository()
    #     a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
    #     b = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=2)
    #     c = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=0)
    #     d = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=1)
    #     repo.addClient(a)
    #     repo.addClient(b)
    #     repo.addClient(c)
    #     repo.addClient(d)
    #     mylist = repo.getListWhoBorrowPresent()
    #     self.assertEqual(len(mylist), 3)
