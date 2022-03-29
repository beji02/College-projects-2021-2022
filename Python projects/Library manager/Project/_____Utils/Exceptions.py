class duplicatedBookError(Exception):
    pass
class emptyStringError(Exception):
    pass
class bookNotInMemError(Exception):
    pass
class noBooksInMemError(Exception):
    pass
class noBookAvailable(Exception):
    pass
class bookValidateError(Exception):
    pass
class shouldNotBeRaisedError(Exception):
    pass
class clientValidationError(Exception):
    pass
class clientDuplicatedError(Exception):
    pass
class clientNotInMemError(Exception):
    pass
class noClientsInMemError(Exception):
    pass
class noClientHasBorrowError(Exception):
    pass
class eventValidationError(Exception):
    pass
class eventDuplicatedError(Exception):
    pass
class returnedMoreThenBorrowed(Exception):
    pass
class FileError(Exception):
    pass