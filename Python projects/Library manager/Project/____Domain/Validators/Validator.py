from Project._____Utils.Exceptions import clientValidationError, eventValidationError


class Validator:
    def validateBook(self, newBook):
        # raises: bookValidateError
        pass
    def validateClient(self, newClient):
        """
        un client este valid daca:
            idul sau e un nr de 4 cifre
            nu are nume si prenume camp gol
            numarul sau de telefon are 10 cifre
            nr total de imprumuturi este pozitiv
            nr de imprumuturi in acest moment este pozitiv
        :param newClient: obiectul care se testeaza
        :return: none
        """
        if newClient.getId() < 1000 or newClient.getId() > 9999:
            raise clientValidationError("id invalid")
        if newClient.getName().strip() == "":
            raise clientValidationError("camp nume gol")
        if newClient.getFirstname().strip() == "":
            raise clientValidationError("camp prenume gol")
        if len(newClient.getPhone()) != 10:
            raise clientValidationError("nr de telefon invalid")
        if newClient.getTotalBorrows() < 0:
            raise clientValidationError("nr total de imprumuturi negativ")
        if newClient.getPresentBorrows() < 0:
            raise clientValidationError("nr de imprumuturi negativ")
    def validateEvent(self, newEvent):
        """
        ridica exceptia eventValidationError daca
            tipul evenimentului e diferit de borrow/return
        :param newEvent: Client: evenimentul evaluat
        :return: none
        """
        if newEvent.getType() != "borrow" and \
            newEvent.getType() != "return":
            raise eventValidationError("tip eveniment invalid")
        self.validateBook(newEvent.getBook())
        self.validateClient(newEvent.getClient())