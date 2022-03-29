import unittest
import os

from Project.___Repository.ClientFileRepo import ClientFileRepository
from Project.____Domain.Entities.Client import Client

class TestClientFileRepo(unittest.TestCase):
    def test_load_from_file(self):
        repo = ClientFileRepository("testclients.txt")
        client = Client("Bejan", "Andrei", "0743155516")
        repo.addClient(client)

        list = repo.getAll()
        self.assertEqual(list[0], client)

        repo2 = ClientFileRepository("testclients.txt")
        list = repo2.getAll()
        self.assertEqual(list[0], client)
    def test_addClient(self):
        repo = ClientFileRepository("testclients.txt")
        client = Client("Bejan", "Andrei", "0743155516")
        repo.addClient(client)

        list = repo.getAll()
        self.assertEqual(list[0], client)

        repo.load_from_file()
        list = repo.getAll()

        self.assertEqual(list[0], client)
    def test_deleteClient(self):
        repo = ClientFileRepository("testclients.txt")
        client = Client("Bejan", "Andrei", "0743155516")

        repo.addClient(client)
        repo.deleteClient(client.getId())

        list = repo.getAll()
        self.assertFalse(list)

        repo.load_from_file()
        list = repo.getAll()
        self.assertFalse(list)
    def test_updateClient(self):
        repo = ClientFileRepository("testclients.txt")
        client = Client("Bejan", "Andrei", "0743155516")
        repo.addClient(client)

        client.setPhone("0744155516")
        repo.updateClient(client)

        list = repo.getList()
        self.assertEqual(list[0].getPhone(), client.getPhone())

        repo.load_from_file()
        list = repo.getAll()
        self.assertEqual(list[0].getPhone(), client.getPhone())

    def tearDown(self):
        os.remove("testclients.txt")
