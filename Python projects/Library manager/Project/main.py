from _UI.Console import Console
from __Controller.ClientService import ClientService
from __Controller.BookService import BookService
from __Controller.EventService import EventService
from __Controller.Generator import Generator
from ___Repository.BookFileRepo import BookFileRepository
from ___Repository.BookRepo import BookRepository, generate_books_repo
from ___Repository.ClientFileRepo import ClientFileRepository
from ___Repository.ClientRepo import ClientRepository, generate_clients_repo
from ___Repository.EventFileRepo import EventFileRepository
from ___Repository.EventRepo import EventRepository
from ____Domain.Validators.Validator import Validator
import unittest
import os



testsuite = unittest.TestLoader().discover('')
unittest.TextTestRunner().run(testsuite)
input("press enter to continue...")
os.system('cls')

# clientFileRepository = ClientFileRepository("Data/clients_line.txt")
# bookFileRepository = BookFileRepository("Data/books_line.txt")
# eventFileRepository = EventFileRepository("Data/events_line.txt", clientFileRepository, bookFileRepository)

clientFileRepository = ClientFileRepository("Data/clients.txt")
bookFileRepository = BookFileRepository("Data/books.txt")
eventFileRepository = EventFileRepository("Data/events.txt", clientFileRepository, bookFileRepository)

# generator = Generator()
# bookRepository, clientRepository, eventRepository = generator.generateData()
# bookRepository = BookRepository()
# clientRepository = ClientRepository()
# eventRepository = EventRepository()

validator = Validator()
bookService = BookService(bookFileRepository, validator)
clientService = ClientService(clientFileRepository, validator)
eventService = EventService(eventFileRepository, bookFileRepository, clientFileRepository, validator)

console = Console(bookService, clientService, eventService)
console.show_ui()






