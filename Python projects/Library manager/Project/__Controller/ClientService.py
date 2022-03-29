from Project.____Domain.Entities.Client import Client
from Project.____Domain.Validators.Validator import Validator
from Project._____Utils.Utils import random_word, random_word_with_numbers


class ClientService():
    def __init__(self, clientRepo, validator):
        """
        initializeaza un nou obiect de tipul clientservice
        care are acces la repositorioul cu clienti si la un validator
        :param clientRepo: repositoriul cu clienti
        :param validator: pentru a valida obiecte
        """
        self.__clientRepo = clientRepo
        self.__validator = validator

    def adauga_client(self, nume, prenume, nr_telefon):
        """
        preia informatiile de la consola, creaza obiectul client, il valideaza si il transmite repositoryului
        pt a-l adauga in memorie
        :param nume: str
        :param prenume: str
        :param nr_telefon: str
        :return: id-ul noului client
        """
        newClient = Client(nume, prenume, nr_telefon)
        self.__validator.validateClient(newClient)

        self.__clientRepo.addClient(newClient)
        return newClient.getId()
    def sterge_client(self, id):
        """
        transmite repositoryului id-ul el care trb sters
        :param id: int
        :return: none
        """
        self.__clientRepo.deleteClient(id)
    def modifica_client(self, id, field, newValue):
        """
        modifica clientul cu acel id in functii de parametrii, il valideaza si
        il transmite repoului pt a-l updata in memorie
        :param id: int
        :param field: "n" - nume, "p" - prenume, "t" - telefon
        :param newValue: noua valoare pt acel camp
        :return: none
        """
        client = self.__clientRepo.getClient(id)

        if field == "n":
            client.setName(newValue)
        elif field == "p":
            client.setFirstname(newValue)
        elif field == "t":
            client.setPhone(newValue)
        self.__validator.validateClient(client)

        self.__clientRepo.updateClient(client)
    def cautare_client(self, id):
        """
        cauta clientul in memorie si returneaza nr de imprumuturi din acest moment
        :param id: int
        :return: int
        """
        client = self.__clientRepo.getClient(id)

        return client.getPresentBorrows()
    # def raport_clienti_inchirieri_prezent(self):
    #     """
    #     preia lista de clienti de la repository, o sorteaza dupa nume, o transforma in text si o returneaza
    #     :return: multi-line text: tabela cu acei clienti
    #     :raises: noClientHasBorrowError daca lista cu clienti care au imprumutate carti e goala
    #     """
    #     client_list = self.__clientRepo.getListWhoBorrowPresent()
    #
    #     if not client_list:
    #         raise noClientHasBorrowError
    #
    #     table = '{:<30}'.format("ID") \
    #             + '{:<35}'.format("NUME") \
    #             + '{:<30}'.format("PRENUME") \
    #             + '{:<30}'.format("NR TELEFON") \
    #             + '{:<30}'.format("NR CARTI IMPRUMUTATE IN ACEST MOMENT")
    #
    #     client_list.sort(key=lambda x: x.getName())
    #
    #     for client in client_list:
    #         table = table + "\n" + str(client)
    #
    #
    #
    #     return table

    def generate_random(self, nr):
        """
        genereaza 'nr' clienti random
        :param nr: numarul de clienti generati
        :return: none
        """
        for i in range(nr):
            nume = random_word(10)
            prenume = random_word(10)
            telefon = random_word_with_numbers(10)
            self.adauga_client(nume, prenume, telefon)



# def test_adauga_client():
#     validator = Validator()
#     clientRepositoy = ClientRepository()
#     clientService = ClientService(clientRepositoy, validator)
#     clientService.adauga_client("Bejan", "Andrei", "0743155516")
#
#     assert len(clientRepositoy.getAll()) == 1
#
#     try:
#         clientService.adauga_client("Bejan", "Andrei", "074155516")
#         assert False
#     except clientValidationError:
#         assert True
# def test_sterge_client():
#     validator = Validator()
#     clientRepositoy = ClientRepository()
#     clientService = ClientService(clientRepositoy, validator)
#
#     id = clientService.adauga_client("Bejan", "Andrei", "0743155516")
#     clientService.sterge_client(id)
#
#     assert len(clientRepositoy.getAll()) == 0
#
#     try:
#         clientService.sterge_client(id)
#         assert False
#     except clientNotInMemError:
#         assert True
# def test_modifica_client():
#     validator = Validator()
#     clientRepositoy = ClientRepository()
#     clientService = ClientService(clientRepositoy, validator)
#
#     id = clientService.adauga_client("Bejan", "Andrei", "0743155516")
#     clientService.modifica_client(id, "n", "Beji")
#
#     assert clientRepositoy.getAll()[0].getName() == "Beji"
#
#     try:
#         clientService.modifica_client(1, "n", "Beji")
#         assert False
#     except clientNotInMemError:
#         assert True
# def test_cautare_client():
#     validator = Validator()
#     clientRepositoy = ClientRepository()
#     clientService = ClientService(clientRepositoy, validator)
#
#     id = clientService.adauga_client("Bejan", "Andrei", "0743155516")
#     borrows = clientService.cautare_client(id)
#
#     assert borrows == 0
#
#     try:
#         borrows = clientService.cautare_client(1)
#         assert False
#     except clientNotInMemError:
#         assert True
# def test_raport_clienti_inchirieri_prezent():
#     validator = Validator()
#     clientRepositoy = ClientRepository()
#     clientService = ClientService(clientRepositoy, validator)
#
#     clientService.adauga_client("Bejan", "Andrei", "0743155516")
#
#     try:
#         raport = clientService.raport_clienti_inchirieri_prezent()
#         assert False
#     except noClientHasBorrowError:
#         assert True
# def test_generate_random():
#     validator = Validator()
#     clientRepositoy = ClientRepository()
#     clientService = ClientService(clientRepositoy, validator)
#
#     clientService.generate_random(5)
#     assert len(clientRepositoy.getAll()) == 5
#
#
# test_adauga_client()
# test_sterge_client()
# test_modifica_client()
# test_cautare_client()
# test_raport_clienti_inchirieri_prezent()
# test_generate_random()
