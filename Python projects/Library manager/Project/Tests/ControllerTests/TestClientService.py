import unittest

from Project.__Controller.ClientService import ClientService
from Project.___Repository.ClientRepo import ClientRepository
from Project.____Domain.Validators.Validator import Validator
from Project._____Utils.Exceptions import clientValidationError, clientNotInMemError, noClientHasBorrowError


class TestClientService(unittest.TestCase):
    def test_adauga_client(self):
        validator = Validator()
        clientRepositoy = ClientRepository()
        clientService = ClientService(clientRepositoy, validator)
        clientService.adauga_client("Bejan", "Andrei", "0743155516")

        self.assertEqual(len(clientRepositoy.getAll()), 1)

        try:
            clientService.adauga_client("Bejan", "Andrei", "074155516")
            self.assertTrue(False)
        except clientValidationError:
            self.assertTrue(True) 
    def test_sterge_client(self):
        validator = Validator()
        clientRepositoy = ClientRepository()
        clientService = ClientService(clientRepositoy, validator)

        id = clientService.adauga_client("Bejan", "Andrei", "0743155516")
        clientService.sterge_client(id)

        self.assertEqual(len(clientRepositoy.getAll()), 0)

        try:
            clientService.sterge_client(id)
            self.assertTrue(False)
        except clientNotInMemError:
            self.assertTrue(True)
    def test_modifica_client(self):
        validator = Validator()
        clientRepositoy = ClientRepository()
        clientService = ClientService(clientRepositoy, validator)

        id = clientService.adauga_client("Bejan", "Andrei", "0743155516")
        clientService.modifica_client(id, "n", "Beji")

        self.assertEqual(clientRepositoy.getAll()[0].getName(), "Beji")

        try:
            clientService.modifica_client(1, "n", "Beji")
            self.assertTrue(False)
        except clientNotInMemError:
            self.assertTrue(True)
    def test_cautare_client(self):
        validator = Validator()
        clientRepositoy = ClientRepository()
        clientService = ClientService(clientRepositoy, validator)

        id = clientService.adauga_client("Bejan", "Andrei", "0743155516")
        borrows = clientService.cautare_client(id)

        self.assertEqual(borrows, 0)

        try:
            borrows = clientService.cautare_client(1)
            self.assertTrue(False)
        except clientNotInMemError:
            self.assertTrue(True)
    # def test_raport_clienti_inchirieri_prezent(self):
    #     validator = Validator()
    #     clientRepositoy = ClientRepository()
    #     clientService = ClientService(clientRepositoy, validator)
    #
    #     clientService.adauga_client("Bejan", "Andrei", "0743155516")
    #
    #     try:
    #         raport = clientService.raport_clienti_inchirieri_prezent()
    #         self.assertTrue(False)
    #     except noClientHasBorrowError:
    #         self.assertTrue(True)
    def test_generate_random(self):
        validator = Validator()
        clientRepositoy = ClientRepository()
        clientService = ClientService(clientRepositoy, validator)

        clientService.generate_random(5)
        self.assertEqual(len(clientRepositoy.getAll()), 5)