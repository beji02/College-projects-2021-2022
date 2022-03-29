from Project.___Repository.ClientRepo import ClientRepository
from Project.____Domain.Entities.Client import Client
from Project._____Utils.Exceptions import FileError


class ClientFileRepository(ClientRepository):
    def __init__(self, FileName):
        ClientRepository.__init__(self)
        self.__file_name = FileName
        self.load_from_file()

    def load_from_file(self):
        """
        copiaza informatia din fisier in memorie
        :return:
        """
        ClientRepository.getList(self).clear()
        try:
            f = open(self.__file_name, "r")
        except OSError:
            return
        try:
            for line in f:
                res = line.split()
                client = Client(res[1],
                                res[2],
                                res[3],
                                id=int(res[0]),
                                nr_imprutururi_totale=int(res[4]),
                                nr_imprumuturi_actuale=int(res[5])
                                )

                ClientRepository.getList(self).append(client)
        finally:
            f.close()
    def store_to_file(self):
        f = open(self.__file_name, "w")
        try:
            for el in self.getList():
                text = '{:<30}'.format(el.getId()) \
                       + '{:<35}'.format(el.getName()) \
                       + '{:<30}'.format(el.getFirstname()) \
                       + '{:<30}'.format(el.getPhone()) \
                       + '{:<30}'.format(el.getTotalBorrows()) \
                       + '{:<30}'.format(el.getPresentBorrows()) + "\n"

                f.write(text)
        except IOError as txt:
            raise FileError(txt)
        finally:
            f.close()
    # def load_from_file(self):
    #     """
    #     copiaza informatia din fisier in memorie
    #     :return:
    #     """
    #     ClientRepository.getList(self).clear()
    #     try:
    #         f = open(self.__file_name, "r")
    #     except OSError:
    #         return
    #     try:
    #         lines = f.readlines()
    #         n = len(lines)//6
    #         for i in range(n):
    #             client = Client(lines[i*6+1].strip(),
    #                             lines[i*6+2].strip(),
    #                             lines[i*6+3].strip(),
    #                             id=int(lines[i*6+0]),
    #                             nr_imprutururi_totale=int(lines[i*6+4]),
    #                             nr_imprumuturi_actuale=int(lines[i*6+5])
    #                             )
    #
    #             ClientRepository.getList(self).append(client)
    #     finally:
    #         f.close()
    # def store_to_file(self):
    #     f = open(self.__file_name, "w")
    #     try:
    #         for el in self.getList():
    #             text = '{:<30}'.format(el.getId()) +"\n"\
    #                    + '{:<35}'.format(el.getName()) +"\n"\
    #                    + '{:<30}'.format(el.getFirstname()) +"\n"\
    #                    + '{:<30}'.format(el.getPhone()) +"\n"\
    #                    + '{:<30}'.format(el.getTotalBorrows()) +"\n"\
    #                    + '{:<30}'.format(el.getPresentBorrows()) + "\n"
    #
    #             f.write(text)
    #     except IOError as txt:
    #         raise FileError(txt)
    #     finally:
    #         f.close()

    def addClient(self, client):
        """
        adauga un nou obiect client in fisier si in memorie
        :param client: Client: clientul nou care se adauga
        :return:
        """
        ClientRepository.addClient(self, client)

        self.store_to_file()
    def deleteClient(self, id):
        """
        sterge un client cu acel id din fisier si din memorie
        :param id: int: id-ul clientului
        :return: None
        """
        ClientRepository.deleteClient(self, id)

        self.store_to_file()
    def updateClient(self, modifiedClient):
        """
        modifica un obiect client in fisier si in memorie
        :param modifiedClient: Client: obiectul modificat
        :return: None
        """
        ClientRepository.updateClient(self, modifiedClient)

        self.store_to_file()
