import os

from Project._____Utils.Exceptions import duplicatedBookError, emptyStringError, bookNotInMemError, noBooksInMemError, \
    clientValidationError, clientDuplicatedError, clientNotInMemError, noClientHasBorrowError, \
    eventValidationError, eventDuplicatedError, noBookAvailable, returnedMoreThenBorrowed, noClientsInMemError

class Console:
    def __init__(self, bookService, clientService, eventService):
        self.__bookService = bookService
        self.__clientService = clientService
        self.__eventService = eventService

    @staticmethod
    def read_string(message):
        """
        citeste un sir de caractere de la utilizator
        :param message: string: textul care sa fie afisat
        :return: str: textul citit
        :raises: emptyStringError daca sirul contine doar spatii goale
        """
        text = input(message)
        if text.strip() == "":
            raise emptyStringError
        return text
    @staticmethod
    def read_number(message):
        """
        citeste un numar de la utilizator
        :param message: string: textul care sa fie afisat
        :return: int: numarul citit
        :raises: valueError daca utiliz nu a introdus un numar
        """
        nr = int(input(message))
        return nr

    def ui_adauga_carte(self):
        try:
            title = self.read_string("titlu: ")
            author = self.read_string("autor: ")
            description = self.read_string("descriere: ")
            k_copies = self.read_number("numar de exemplare: ")

            self.__bookService.adauga_carte(title, author, description, k_copies)
            print("Cartea a fost adaugata cu succes!")
        except ValueError:
            print("Nu ati introdus numarul de exemplare in mod corect.")
        except emptyStringError:
            print("Campul nu poate fi gol!")
        except duplicatedBookError:
            print("Exista deja o carte cu acelasi nume si acelasi autor!")
    def ui_sterge_carte(self):
        try:
            title = self.read_string("titlu: ")
            author = self.read_string("autor: ")

            self.__bookService.sterge_carte(title, author)
            print("Cartea a fost stearsa din memorie.")
        except emptyStringError:
            print("Campul nu poate fi gol!")
        except bookNotInMemError:
            print("Cartea nu exista in memorie!")
    def ui_modifica_carte(self):
        def newTitle():
            newtitle = self.read_string("Titlu nou: ")
            self.__bookService.modifica_carte(title, author, newTitle=newtitle)
            print("Titlul a fost modificat cu succes!")
        def newAuthor():
            newauthor = self.read_string("Autor nou: ")
            self.__bookService.modifica_carte(title, author, newAuthor=newauthor)
            print("Autorul a fost modificat cu succes!")
        def newNrExemplare():
            newnrExemplare = self.read_number("Numar de exemplare nou: ")
            self.__bookService.modifica_carte(title, author, new_k_copies=newnrExemplare)
            print("Numarul de exemplare a fost modificat cu succes!")
        def newDescr():
            newdescript = self.read_string("Descriere noua: ")
            self.__bookService.modifica_carte(title, author, new_desc=newdescript)
            print("Descrierea a fost modificata cu succes!")
        commands = {
            "titlu": newTitle,
            "autor": newAuthor,
            "nrexemplare": newNrExemplare,
            "descriere": newDescr,
        }

        try:
            title = self.read_string("titlu: ")
            author = self.read_string("autor: ")

            while True:
                print("Ce doriti sa modificati: ", end="")
                for key in commands.keys():
                    print(key, end="/")
                choice = input("--------> ")
                if choice in commands.keys():
                    commands[choice]()
                    break
        except ValueError:
            print("Nu ati introdus numarul de exemplare in mod corect.")
        except emptyStringError:
            print("Campul nu poate fi gol!")
        except bookNotInMemError:
            print("Cartea nu exista in memorie!")
        except duplicatedBookError:
            print("Exista deja o carte cu acelasi nume si autor!")
    def ui_cauta_carte(self):
        try:
            title = self.read_string("titlu: ")
            author = self.read_string("autor: ")

            nrExemplare = self.__bookService.cauta_exemplare_carte(title, author)
            if nrExemplare == 0:
                print("Cartea este in memorie, dar toate exemplarele sunt imprumutate. Ne pare rau!")
            else:
                print("Exista " + str(nrExemplare) + " exemplare disponibile ale cartii.")
        except emptyStringError:
            print("Campul nu poate fi gol!")
        except bookNotInMemError:
            print("Cartea nu exista in memorie!")
    # def ui_raport_carti_inchiriate(self):
    #     try:
    #         raport = self.__bookService.raport_carti_inchiriate()
    #         print(raport)
    #     except noBooksInMemError:
    #         print("Deocamdata biblioteca este goala...")

    def ui_adauga_client(self):
        try:
            nume = self.read_string("nume: ")
            prenume = self.read_string("prenume: ")
            nr_telefon = self.read_string("nr telefon: ")

            id = self.__clientService.adauga_client(nume, prenume, nr_telefon)
            print("Clientul a fost adaugat cu succes! Id-ul acestuia este: " + str(id))
        except emptyStringError:
            print("Campul nu poate fi gol!")
        except clientValidationError as message:
            print(message)
        except clientDuplicatedError:
            print("Clientul este deja in memorie.")
    def ui_sterge_client(self):
        try:
            id = self.read_number("Id-ul utilizatorului: ")

            self.__clientService.sterge_client(id)
            print("Clientul a fost sters din memorie!")
        except ValueError:
            print("Id-ul nu a fost introdus corect!")
        except clientNotInMemError:
            print("Clientul nu exista in memorie.")
    def ui_modifica_client(self):
        commands = ["nume", "prenume", "nr telefon"]
        try:
            id = self.read_number("Id-ul utilizatorului: ")

            field = None
            newValue = None
            while True:
                print("Ce doriti sa modificati: ", end="")
                for key in commands:
                    print(key, end="/")
                choice = input("--------> ")
                if choice in commands:
                    if choice == "nume":
                        field = "n"
                        newValue = self.read_string("nume nou: ")
                    elif choice == "prenume":
                        field = "p"
                        newValue = self.read_string("prenume nou: ")
                    elif choice == "nr telefon":
                        field = "t"
                        newValue = self.read_string("nr nou de telefon: ")
                    break

            self.__clientService.modifica_client(id, field, newValue)
            print("Informatiile clientului au fost modificat cu succes!")
        except ValueError:
            print("Id-ul nu a fost introdus corect!")
        except clientNotInMemError:
            print("Clientul nu exista in memorie.")
        except emptyStringError:
            print("Campul nu poate fi gol!")
        except clientValidationError as message:
            print(message)
    def ui_cautare_client(self):
        try:
            id = self.read_number("Id-ul utilizatorului: ")

            nr_imprumuturi_in_prezent = self.__clientService.cautare_client(id)
            print("Clientul este inregistrat si are imprumutate " + str(nr_imprumuturi_in_prezent)\
                  +" carti in prezent.")
        except ValueError:
            print("Id-ul nu a fost introdus corect!")
        except clientNotInMemError:
            print("Clientul nu exista in memorie.")
    # def ui_raport_clienti_inchirieri_prezent(self):
    #     try:
    #         raport = self.__clientService.raport_clienti_inchirieri_prezent()
    #         print(raport)
    #     except noClientHasBorrowError:
    #         print("Nici un client nu are imprumutata vreo carte in acest moment...")

    def ui_generate_random(self):
        try:
            nr = self.read_number("Cati clienti random sa generez: ")
            self.__clientService.generate_random(nr)
            print("Clientii au fost generati cu succes.")
        except ValueError:
            print("Nu ati introdus numarul in mod corect.")
        except clientValidationError as message:
            print(message)
        except clientDuplicatedError:
            print("Clientul este deja in memorie.")

    def ui_inchiriere_carte(self):
        try:
            id = self.read_number("Id-ul utilizatorului: ")
            nume_carte = self.read_string("Numele cartii: ")
            nume_autor = self.read_string("Numele autorului: ")
            self.__eventService.inchiriere_carte(id, nume_carte, nume_autor)
            print("Clientul cu id-ul " + str(id) + " a inchiriat cartea " + nume_carte + " cu succes!")
        except ValueError:
            print("Id-ul nu a fost introdus corect!")
        except emptyStringError:
            print("Campul nu poate fi gol!")
        except clientNotInMemError:
            print("Clientul nu exista in memorie.")
        except bookNotInMemError:
            print("Cartea nu exista in memorie.")
        except noBookAvailable:
            print("Toate exemplarele cartii sunt imprumutate in acest moment. Ne pare rau!")
        except eventValidationError:
            print("Evenimentul nu se poate valida!")
        except eventDuplicatedError:
            print("Evenimentul exista deja in memorie")
    def ui_returnare_carte(self):
        try:
            id = self.read_number("Id-ul utilizatorului: ")
            nume_carte = self.read_string("Numele cartii: ")
            nume_autor = self.read_string("Numele autorului: ")
            self.__eventService.returnare_carte(id, nume_carte, nume_autor)
            print("Clientul cu id-ul " + str(id) + " a returnat cartea " + nume_carte + " cu succes!")
        except ValueError:
            print("Id-ul nu a fost introdus corect!")
        except emptyStringError:
            print("Campul nu poate fi gol!")
        except clientNotInMemError:
            print("Clientul nu exista in memorie.")
        except bookNotInMemError:
            print("Cartea nu exista in memorie.")
        except eventValidationError:
            print("Evenimentul nu se poate valida!")
        except eventDuplicatedError:
            print("Evenimentul exista deja in memorie")
        except returnedMoreThenBorrowed:
            print("Cartea nu este imprumutata de la aceasta biblioteca!")

    def ui_raport_cele_mai_inchiriate_carti(self):
        try:
            raport = self.__eventService.raport_cele_mai_inchiriate_carti()
            print(raport)
        except noBooksInMemError:
            print("Deocamdata biblioteca este goala...")
    def ui_raport_clienti_ordonati_dupa_nume(self):
        try:
            raport = self.__eventService.raport_clienti_ordonati_dupa_nume()
            print(raport)
        except noClientHasBorrowError:
            print("Nici un client nu are imprumutata vreo carte in acest moment...")
        except noClientsInMemError:
            print("Nu exista clienti in memorie.")
    def ui_raport_clienti_ordonati_dupa_nr_inchirieri(self):
        try:
            raport = self.__eventService.raport_clienti_ordonati_dupa_nr_inchirieri()
            print(raport)
        except noClientHasBorrowError:
            print("Nici un client nu are imprumutata vreo carte in acest moment...")
        except noClientsInMemError:
            print("Nu exista clienti in memorie.")
    def ui_raport_clienti_top_20(self):
        try:
            raport = self.__eventService.raport_clienti_top_20()
            print(raport)
        except noClientHasBorrowError:
            print("Nici un client nu are imprumutata vreo carte in acest moment...")
        except noClientsInMemError:
            print("Nu exista clienti in memorie.")
    def ui_raport_cei_mai_inchiriati_3_scriitori(self):
        try:
            raport = self.__eventService.raport_cei_mai_inchiriati_3_scriitori()
            print(raport)
        except noBooksInMemError:
            print("Deocamdata biblioteca este goala...")

    def show_ui(self):
        commands = {
            "addb" :    self.ui_adauga_carte,
            "deleteb" : self.ui_sterge_carte,
            "modifyb" : self.ui_modifica_carte,
            "searchb" : self.ui_cauta_carte,
            #"raportb" : self.ui_raport_carti_inchiriate,

            "addc":     self.ui_adauga_client,
            "deletec":  self.ui_sterge_client,
            "modifyc":  self.ui_modifica_client,
            "searchc":  self.ui_cautare_client,
            #"raportc":  self.ui_raport_clienti_inchirieri_prezent,

            "generate": self.ui_generate_random,

            "imprumut": self.ui_inchiriere_carte,
            "returnare": self.ui_returnare_carte,

            "rapnume": self.ui_raport_clienti_ordonati_dupa_nume,
            "rapborrows": self.ui_raport_clienti_ordonati_dupa_nr_inchirieri,
            "rapbooks": self.ui_raport_cele_mai_inchiriate_carti,
            "top20": self.ui_raport_clienti_top_20,

            "rapauthors": self.ui_raport_cei_mai_inchiriati_3_scriitori,
        }

        while True:
            print("Alege o functie dintre: end; ", end="")
            for key in commands.keys():
                print(key, end="; ")
            menu_choice = input("--------> ")
            if menu_choice == "end":
                return
            if menu_choice in commands.keys():
                commands[menu_choice]()
                input("press enter to continue...")
            os.system('cls')


