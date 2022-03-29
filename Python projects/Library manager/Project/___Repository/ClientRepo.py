from Project._____Utils.Exceptions import clientDuplicatedError, clientNotInMemError
from Project.____Domain.Entities.Client import Client
from Project._____Utils.Utils import copy_list


class ClientRepository():
    def __init__(self):
        """
        initializeaza un nou repository de clienti
        contine doar o lista de clienti
        """
        self.__list_of_clients = []

    def getList(self):
        """
        returneaza lista de clienti
        :return: list of clients
        """
        return self.__list_of_clients
    def getAll(self):
        """
        returneaza o copie a listei de clienti din repository
        :return: list of clients: copie a listei de clienti din memorie
        """
        return copy_list(self.__list_of_clients)

    def __append(self, newClient):
        """
        adauga un nou client in repository
        :param newClient: Client: noul client
        :return: none
        """
        self.getList().append(newClient)

    def findClientRec(self, id, client_list = None):
        """
                returneaza clientul cu idul id daca exista, daca nu returneaza None
                :param id: id ul clientului cautat
                :return: client: obiectul cautat din lista
                """
        if client_list is None:
            client_list = self.getList()
        if len(client_list) == 0:
            return None
        client = client_list[0]
        if client.getId() == id:
            return client
        else:
            return self.findClientRec(id, client_list[1:])


    def findClient(self, id):
        """
        returneaza clientul cu idul id daca exista, daca nu returneaza None
        :param id: id ul clientului cautat
        :return: client: obiectul cautat din lista
        """
        client_list = self.getList()
        for client in client_list:
            if client.getId() == id:
                return client
        return None
    def getClient(self, id):
        """
        returneaza clientul cautat, dar ridica si exceptie daca nu este in memorie
        :param id: int: id-ul clientului cautat
        :return: client
        :raises: clientNotInMemError daca nu exista clientul cu acel id
        """
        client = self.findClient(id)
        if client is None:
            raise clientNotInMemError
        return client
    def addClient(self, newClient):
        """
        ANALIZA COMPLEXITATI
        --------------------
        fie n - nr de clienti din memorie

        complexitatea in cazul favorabil:
        T(n) = 1 + 3 = 4
        T(n) apartine clasei de complexitate Theta(1)
        (cand functia self.findClient() gaseste pe prima pozitie clientul cautat)

        complexitatea in cazul defavorabil:
        T(n) = (1 + 1 + ... + 1) de n ori + 3 = n + 3
        T(n) apartine clasei de complexitate Theta(n)
        (cand functia self.findClient() nu gaseste clientul in lista)

        complexitatea in cazul mediu:
        T(n) = (1 + 2 + 3 + 4 + ... + n) / n    + 3 = n * (n+1) / (2*n) + 3 = (n+1)/2 + 3
        T(n) apartine clasei de complexitate Theta(n)
        (presupunand ca probabilitatile ca clientul sa se gaseasca pe o anumita pozitie in sir sunt egale)

        overall complexity:
        O(n)

        --------------------
        adauga un client nou daca nu exista altul cu acel id
        :param: newClient: client: noul client care trb adaugat
        :return: none
        :raises: clientDuplicatedError daca clientul exista deja in memorie
        """
        oldClient = self.findClient(newClient.getId())
        if oldClient is not None:
            raise clientDuplicatedError

        self.__append(newClient)
    def deleteClient(self, id):
        """
        sterge clientul cu id din memorie
        :param id: int: idul clientului
        :return: none
        :raises: clientNotInMemError daca nu exista clientul cu acel id
        """
        client = self.findClient(id)
        if client is None:
            raise clientNotInMemError

        self.getList().remove(client)
    def updateClient(self, modifiedClient):
        """
        inlocuieste elementul cu acelasi id cu clientul nou modifiedClient
        :param modifiedClient: Client: noul client
        :return: none
        :raises: clientNotInMemError daca clientul nu exista in memorie
        """
        try:
            client_list = self.getList()
            index = client_list.index(modifiedClient)
            client_list[index] = modifiedClient
        except ValueError:
            raise clientNotInMemError
    # def getListWhoBorrowPresent(self):
    #     """
    #     returneaza o lista cu toti clientii care au imprumutate carti in acest moment
    #     :return: list of clients: lista ceruta
    #     """
    #     client_list = self.__get_list()
    #     return_list = []
    #     for client in client_list:
    #         if client.getPresentBorrows() > 0:
    #             return_list.append(client)
    #     return return_list


def generate_clients_repo():
    """
    generates a repository with 4 clients
    :return: ClientRepository
    """
    repo = ClientRepository()
    a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
    b = Client("Brita", "Catalin", "0744155516", nr_imprutururi_totale=5, nr_imprumuturi_actuale=2)
    c = Client("Serban", "Darian", "0745155516", nr_imprutururi_totale=20, nr_imprumuturi_actuale=0)
    d = Client("Moldovan", "Denis", "0746155516", nr_imprutururi_totale=30, nr_imprumuturi_actuale=1)
    repo.addClient(a)
    repo.addClient(b)
    repo.addClient(c)
    repo.addClient(d)

    return repo
#
# def test_addClient():
#     """
#     testeaza functia addclient
#     :return: none
#     """
#     repo = ClientRepository()
#     a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
#
#     repo.addClient(a)
#     try:
#         repo.addClient(a)
#         assert False
#     except clientDuplicatedError:
#         assert True
# def test_findClient():
#     repo = ClientRepository()
#     a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
#     b = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
#
#     repo.addClient(a)
#     assert a == repo.findClient(a.getId())
#     assert repo.findClient(b.getId()) is None
#
#     repo.addClient(b)
#     assert a == repo.findClient(a.getId())
# def test_deleteClient():
#     repo = ClientRepository()
#     a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
#     b = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
#
#     repo.addClient(a)
#     repo.addClient(b)
#
#
#     repo.deleteClient(a.getId())
#     try:
#         repo.deleteClient(a.getId())
#         assert False
#     except clientNotInMemError:
#         assert True
#     repo.deleteClient(b.getId())
# def test_updateClient():
#     repo = ClientRepository()
#     a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
#     b = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
#
#     repo.addClient(a)
#     repo.addClient(b)
#
#     a.setPhone("1111122222")
#     repo.updateClient(a)
#     assert a == repo.findClient(a.getId())
#     assert a.getPhone() == repo.findClient(a.getId()).getPhone()
#
#     repo.deleteClient(a.getId())
#     try:
#         repo.updateClient(a)
#         assert False
#     except clientNotInMemError:
#         assert True
# def test_getClient():
#     repo = ClientRepository()
#     a = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
#     b = Client("Bejan", "Andrei", "0743155516", nr_imprutururi_totale=10, nr_imprumuturi_actuale=3)
#
#     repo.addClient(a)
#     repo.addClient(b)
#     assert a == repo.getClient(a.getId())
#     repo.deleteClient(a.getId())
#     try:
#         aux = repo.getClient(a.getId())
#         assert False
#     except clientNotInMemError:
#         assert True
# def test_getListWhoBorrowPresent():
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
#     assert len(mylist) == 3
#
# test_addClient()
# test_findClient()
# test_deleteClient()
# test_updateClient()
# test_getClient()
# #test_getListWhoBorrowPresent()
