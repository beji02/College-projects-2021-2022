from math import ceil

from Project.___Repository.EventRepo import EventRepository
from Project.____Domain.Entities.Event import Event
from Project.____Domain.Validators.Validator import Validator
from Project._____Utils.Exceptions import eventDuplicatedError, noBookAvailable, returnedMoreThenBorrowed, noBooksInMemError, \
    noClientsInMemError, noClientHasBorrowError
from Project.__Controller.Generator import Generator
from Project._____Utils.Utils import myBubbleSort, myShellSort


class EventService:
    def __init__(self, eventRepository, bookRepository, clientRepository, validator):
        """
        initializeaza un nou service pentru evenimente
        :param eventRepository: repositoriul cu evenimente
        :param bookRepository: repositoriul cu carti
        :param clientRepository: repositoriul cu clienti
        :param validator: validatorul de entitati
        """
        self.__eventRepo = eventRepository
        self.__bookRepo = bookRepository
        self.__clientRepo = clientRepository
        self.__validator = validator

    def inchiriere_carte(self, id_client, nume_carte, nume_autor):
        """
        simuleaza inchirierea unei carti,
        introduce evenimentul in repositoriul de evenimente,
        incrementeaza nr_imprumuturi_totale ale clientului,
        incrementeaza nr_imprumuturi_actuale ale clientului,
        incrementeaza k_borrows pentru carte,
        decrementeaza k_av_copies pentru carte,

        :param id_client: idul clientului care imprumuta
        :param nume_carte: numele cartii imprumutate
        :param nume_autor: numele autorului cartii
        :raises eventDuplicatedError daca exista fix acelasi eveniment in memorie
        :raises noBookAvailable daca nu exista niciun exemplar pe care l-ar putea imprumuta
        """
        book = self.__bookRepo.getBook(nume_carte, nume_autor)
        client = self.__clientRepo.getClient(id_client)

        new_event = Event("borrow", client, book)
        self.__validator.validateEvent(new_event)

        already_stored = self.__eventRepo.find(new_event)
        if already_stored:
            raise eventDuplicatedError

        if book.isAvailable():
            self.__eventRepo.store(new_event)
            self.__bookRepo.remove(book)
            book.borrow()
            self.__bookRepo.append(book)
            self.__clientRepo.deleteClient(client.getId())
            client.borrow()
            self.__clientRepo.addClient(client)
        else:
            raise noBookAvailable

    def verify_book_borrowed(self, client, book):
        """
        verifica daca o carte care se returneaza provine din aceasta biblioteca
        :param client: obiectul client
        :param book: obiectul cartii
        :raises returnedMoreThenBorrowed: daca cartea nu provine din aceasta biblioteca
        """
        all_events = self.__eventRepo.getAll()
        k_borrowed = 0
        k_returned = 0
        for ev in all_events:
            if ev.getClient() == client and ev.getBook() == book:
                if ev.getType() == "borrow":
                    k_borrowed = k_borrowed + 1
                elif ev.getType() == "return":
                    k_returned = k_returned + 1

        if k_returned >= k_borrowed:
            raise returnedMoreThenBorrowed
    def returnare_carte(self, id_client, nume_carte, nume_autor):
        """
        simuleaza returnarea unei carti,
        introduce evenimentul in repositoriul de evenimente,
        decrementeaza nr_imprumuturi_actuale ale clientului,
        incrementeaza k_av_copies pentru carte,
        :param id_client: id client care returneaza
        :param nume_carte: numele cartii
        :param nume_autor: numele autorului
        :raise eventDuplicatedError: daca evenimentul exista deja
        """
        book = self.__bookRepo.getBook(nume_carte, nume_autor)
        client = self.__clientRepo.getClient(id_client)

        self.verify_book_borrowed(client, book)

        new_event = Event("return", client, book)
        self.__validator.validateEvent(new_event)

        already_stored = self.__eventRepo.find(new_event)
        if already_stored:
            raise eventDuplicatedError

        self.__eventRepo.store(new_event)
        self.__bookRepo.remove(book)
        book.retur()
        self.__bookRepo.append(book)
        self.__clientRepo.deleteClient(client.getId())
        client.retur()
        self.__clientRepo.addClient(client)

    def raport_cele_mai_inchiriate_carti(self):
        """
        creeaza un raport cu carti inchiriate ordonate dupa nr de inchirieri
        :return: raportul structurat pe coloane
        :raises: noBooksInMemError daca nu exista nicio carte in memorie
        """
        all_books = self.__bookRepo.getAll()
        if len(all_books) == 0:
            raise noBooksInMemError

        #all_books.sort(key=lambda x: x.getBorrows(), reverse=True)
        def mycmp(a, b):
            if a.getAuthor() == b.getAuthor():
                return a.getTitle() < b.getTitle()
            return a.getAuthor() < b.getAuthor()
        myBubbleSort(all_books, cmp=mycmp)


        table = '{:<30}'.format("ID") \
                + '{:<35}'.format("TITLU") \
                + '{:<30}'.format("AUTOR") \
                + '{:<30}'.format("DE CATE ORI A FOST IMPRUMUTATA")

        for book in all_books:
            text = '{:<30}'.format(book.getId()) \
                   + '{:<35}'.format(book.getTitle()) \
                   + '{:<30}'.format(book.getAuthor()) \
                   + '{:<30}'.format(book.getBorrows())
            table = table + "\n" + text

        return table
    def raport_clienti_ordonati_dupa_nr_inchirieri(self):
        """
        creeaza un raport cu clientii care au imprumutat carti ordonati dupa nr de imprumuturi
        :return: raportul structurat pe coloane
        :raises: noClientsInMemError: daca nu exista clienti in memorie
        :raises: noClientHasBorrowError: daca niciun client nu a imprumutat carti
        """
        all_clients = self.__clientRepo.getAll()
        if len(all_clients) == 0:
            raise noClientsInMemError

        clients_who_borrowed = []
        for client in all_clients:
            if client.getTotalBorrows() > 0:
                clients_who_borrowed.append(client)

        if len(clients_who_borrowed) == 0:
            raise noClientHasBorrowError

        myBubbleSort(clients_who_borrowed, key=lambda x: x.getTotalBorrows(), reversed = True)

        table = '{:<30}'.format("ID") \
                + '{:<35}'.format("NUME") \
                + '{:<30}'.format("PRENUME") \
                + '{:<30}'.format("NR CARTI IMPRUMUTATE IN TOTAL")

        for client in clients_who_borrowed:
            text = '{:<30}'.format(client.getId()) \
                   + '{:<35}'.format(client.getName()) \
                   + '{:<30}'.format(client.getFirstname()) \
                   + '{:<30}'.format(client.getTotalBorrows())
            table = table + "\n" + text

        return table
    def raport_clienti_ordonati_dupa_nume(self):
        """
        creeaza un raport cu clientii care au imprumutat carti ordonati dupa nume
        :return: raportul structurat pe coloane
        :raises: noClientsInMemError: daca nu exista clienti in memorie
        :raises: noClientHasBorrowError: daca niciun client nu a imprumutat carti
        """
        all_clients = self.__clientRepo.getAll()
        if len(all_clients) == 0:
            raise noClientsInMemError

        clients_who_borrowed = []
        for client in all_clients:
            if client.getTotalBorrows() > 0:
                clients_who_borrowed.append(client)

        if len(clients_who_borrowed) == 0:
            raise noClientHasBorrowError

        myBubbleSort(clients_who_borrowed, key=lambda x: x.getName(), reversed=True)

        table = '{:<30}'.format("ID") \
                + '{:<35}'.format("NUME") \
                + '{:<30}'.format("PRENUME") \
                + '{:<30}'.format("NR CARTI IMPRUMUTATE IN TOTAL")

        for client in clients_who_borrowed:
            text = '{:<30}'.format(client.getId()) \
                   + '{:<35}'.format(client.getName()) \
                   + '{:<30}'.format(client.getFirstname()) \
                   + '{:<30}'.format(client.getTotalBorrows())
            table = table + "\n" + text

        return table

    def raport_clienti_top_20(self):
        """
        creeaza un top20 al celor mai activi clienti
        :return: raportul structurat pe coloane
        :raises: noClientsInMemError: daca nu exista clienti in memorie
        """
        all_clients = self.__clientRepo.getAll()

        kclients = len(all_clients)
        if kclients == 0:
            raise noClientsInMemError

        myShellSort(all_clients, key=lambda x: x.getTotalBorrows(), reversed = True)

        ktop = ceil(kclients/5)
        all_clients = all_clients[0:ktop]

        table = '{:<30}'.format("ID") \
                + '{:<35}'.format("NUME") \
                + '{:<30}'.format("PRENUME") \
                + '{:<30}'.format("NR CARTI IMPRUMUTATE IN TOTAL")

        for client in all_clients:
            text = '{:<30}'.format(client.getId()) \
                   + '{:<35}'.format(client.getName()) \
                   + '{:<30}'.format(client.getFirstname()) \
                   + '{:<30}'.format(client.getTotalBorrows())
            table = table + "\n" + text

        return table

    def raport_cei_mai_inchiriati_3_scriitori(self):
        """
        creeaza un raport cu primii 3 authori cu cele mai multe carti inchiriate
        :return: raportul structurat pe coloane
        :raises: noBooksInMemError: daca nu exista carti in memorie
        """
        all_books = self.__bookRepo.getAll()
        if len(all_books) == 0:
            raise noBooksInMemError

        dict_of_authors = {}
        for book in all_books:
            if book.getAuthor() not in dict_of_authors:
                dict_of_authors[book.getAuthor()] = 0
            dict_of_authors[book.getAuthor()] = dict_of_authors[book.getAuthor()] + book.getBorrows()

        sort_order = myShellSort(dict_of_authors.items(), key=lambda x: x[1], reversed=True)

        table = '{:<30}'.format("AUTOR") \
                + '{:<30}'.format("IMPRUMUTURI")

        for el in sort_order:
            text = '{:<30}'.format(el[0]) \
                   + '{:<30}'.format(el[1])
            table = table + "\n" + text
        return table



# def test_inchiriere_carte():
#     validator = Validator()
#     generator = Generator()
#     bookRepository, clientRepository, eventRepository = generator.generateData()
#     eventService = EventService(eventRepository, bookRepository, clientRepository, validator)
#
#     id = clientRepository.getAll()[0].getId()
#     lenght = len(eventRepository.getAll())
#     eventService.inchiriere_carte(id, "test", "test")
#
#     assert lenght + 1 == len(eventRepository.getAll())
# def test_verify_book_borrowed():
#     validator = Validator()
#     generator = Generator()
#     bookRepository, clientRepository, eventRepository = generator.generateData()
#     eventService = EventService(eventRepository, bookRepository, clientRepository, validator)
#
#     id = clientRepository.getAll()[0].getId()
#     eventService.inchiriere_carte(id, "test", "test")
#     assert eventService.verify_book_borrowed(clientRepository.getClient(id), bookRepository.getBook("test", "test")) == None
# def test_returnare_carte():
#     validator = Validator()
#     generator = Generator()
#     bookRepository, clientRepository, eventRepository = generator.generateData()
#     eventService = EventService(eventRepository, bookRepository, clientRepository, validator)
#
#     id = clientRepository.getAll()[0].getId()
#     before = clientRepository.findClient(id).getPresentBorrows()
#     eventService.inchiriere_carte(id, "test", "test")
#     eventService.returnare_carte(id, "test", "test")
#     assert before == clientRepository.findClient(id).getPresentBorrows()
#
#
# test_inchiriere_carte()
# test_verify_book_borrowed()
# test_returnare_carte()