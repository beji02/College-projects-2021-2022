from Project.___Repository.BookRepo import BookRepository
from Project.___Repository.ClientRepo import ClientRepository
from Project.___Repository.EventRepo import EventRepository
from Project.____Domain.Entities.Book import Book
from Project.____Domain.Entities.Event import Event
from Project.____Domain.Entities.Client import Client

class Generator:
    @staticmethod
    def generate_book_repository():
        """
        genereaza 5 carti pe care le salveaza intr-un repository
        :return: BookRepository: repositoriul cu cele 5 carti
        """
        repo = BookRepository()
        title = "10 Negrii Mititei"
        author = "Agatha Christie"
        desc = "Zece negri mititei au mancat la cina oua.\nUnul insa s-a-necat si-au rămas doar noua."
        mybook = Book(title, author, desc, k_copies=10, k_borrows=9)
        repo.append(mybook)

        title = "Craciunul lui Poirot"
        mybook = Book(title, author, desc, k_copies=4, k_borrows=10)
        repo.append(mybook)

        title = "Crima din Orient Express"
        mybook = Book(title, author, desc, k_copies=3, k_borrows=3)
        repo.append(mybook)

        title = "Misterul din Caraibe"
        mybook = Book(title, author, desc, k_copies=1, k_borrows=4)
        repo.append(mybook)

        title = "test"
        author = "test"
        mybook = Book(title, author, desc, k_copies=10, k_borrows=20)
        repo.append(mybook)

        return repo
    @staticmethod
    def generate_client_repository():
        """
        genereaza 4 clienti pe care ii adauga in repository
        :return: ClientRepository: repositoriul cu cei 4 clienti
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
    @staticmethod
    def generate_event_repository(book_repo, client_repo):
        """
        generates 8 events based on 4 clients and 5 books and saves them to a new event repository
        :param book_repo: BookRepository: repositoriul cu cele 5 carti
        :param client_repo: ClientRepository: repositoriul cu cei 4 clienti
        :return: EventRepository: repositoriul cu cele 8 evenimente
        """
        books = book_repo.getAll()
        clients = client_repo.getAll()
        repo = EventRepository()

        event = Event("borrow", clients[0], books[1])
        repo.store(event)
        event = Event("return", clients[0], books[1])
        repo.store(event)
        event = Event("borrow", clients[1], books[0])
        repo.store(event)
        event = Event("borrow", clients[1], books[1])
        repo.store(event)
        event = Event("borrow", clients[1], books[2])
        repo.store(event)
        event = Event("return", clients[1], books[1])
        repo.store(event)
        event = Event("borrow", clients[2], books[0])
        repo.store(event)
        event = Event("borrow", clients[3], books[0])
        repo.store(event)

        return repo


    def generateData(self):
        """
        genereaza un book repository, un client repository si un event repository
        cu legaturi intre ele
        :return: BookRepository, ClientRepository, EventRepository: cele 3 repositoriuri cu date generate
        """
        book_repo = Generator.generate_book_repository()
        client_repo = Generator.generate_client_repository()
        event_repo = Generator.generate_event_repository(book_repo, client_repo)
        return book_repo, client_repo, event_repo


# def test_generate_book_repository():
#     book_repo = Generator.generate_book_repository()
#     all = book_repo.getAll()
#     assert len(all) == 5
# def test_generate_client_repository():
#     client_repo = Generator.generate_client_repository()
#     all = client_repo.getAll()
#     assert len(all) == 4
# def test_generate_event_repository():
#     book_repo = Generator.generate_book_repository()
#     client_repo = Generator.generate_client_repository()
#
#     event_repo = Generator.generate_event_repository(book_repo, client_repo)
#     all = event_repo.getAll()
#     assert len(all) == 8
#
#
# test_generate_book_repository()
# test_generate_client_repository()
# test_generate_event_repository()