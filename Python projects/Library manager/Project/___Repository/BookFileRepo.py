from Project.___Repository.BookRepo import BookRepository
from Project.____Domain.Entities.Book import Book
from Project._____Utils.Exceptions import FileError


class BookFileRepository(BookRepository):
    def __init__(self, FileName):
        BookRepository.__init__(self)
        self.__file_name = FileName
        self.load_from_file()

    def load_from_file(self):
        """
        copiaza informatia din fisier in memoria programului
        :return: None
        """
        BookRepository.getList(self).clear()
        try:
            f = open(self.__file_name, "r")
        except OSError:
            return
        try:
            for line in f:
                res = line.split("?")
                book = Book(res[1].strip(),
                             res[2].strip(),
                             k_av=int(res[3]),
                             k_copies=int(res[4]),
                             k_borrows=int(res[5]),
                             id=int(res[0]),
                             description=res[6].strip()
                            )

                BookRepository.getList(self).append(book)
        finally:
            f.close()
    def store_to_file(self):
        f = open(self.__file_name, "w")
        try:
            for el in self.getList():
                text = '{:<30}'.format(el.getId()) + "?" \
                       + '{:<35}'.format(el.getTitle()) + "?" \
                       + '{:<30}'.format(el.getAuthor()) + "?" \
                       + '{:<30}'.format(el.getAvailableCopies()) + "?" \
                       + '{:<30}'.format(el.getTotalCopies()) + "?" \
                       + '{:<30}'.format(el.getBorrows()) + "?" \
                       + '{:<30}'.format(el.getDescription()) + "\n"

                f.write(text)
        except IOError as txt:
            raise FileError(txt)
        finally:
            f.close()
    # def load_from_file(self):
    #     """
    #     copiaza informatia din fisier in memoria programului
    #     :return: None
    #     """
    #     BookRepository.getList(self).clear()
    #     try:
    #         f = open(self.__file_name, "r")
    #     except OSError:
    #         return
    #     try:
    #         lines = f.readlines()
    #         n = len(lines)//7
    #         for i in range(n):
    #             book = Book(lines[i*7+1].strip(),
    #                         lines[i*7+2].strip(),
    #                         k_av=int(lines[i*7+3]),
    #                         k_copies=int(lines[i*7+4]),
    #                         k_borrows=int(lines[i*7+5]),
    #                         id=int(lines[i*7+0]),
    #                         description=lines[i*7+6].strip()
    #                         )
    #
    #             BookRepository.getList(self).append(book)
    #     finally:
    #         f.close()
    # def store_to_file(self):
    #     f = open(self.__file_name, "w")
    #     try:
    #         for el in self.getList():
    #             text = '{:<30}'.format(el.getId()) + "\n" \
    #                    + '{:<35}'.format(el.getTitle()) + "\n" \
    #                    + '{:<30}'.format(el.getAuthor()) + "\n" \
    #                    + '{:<30}'.format(el.getAvailableCopies()) + "\n" \
    #                    + '{:<30}'.format(el.getTotalCopies()) + "\n" \
    #                    + '{:<30}'.format(el.getBorrows()) + "\n" \
    #                    + '{:<30}'.format(el.getDescription()) + "\n"
    #
    #             f.write(text)
    #     except IOError as txt:
    #         raise FileError(txt)
    #     finally:
    #         f.close()


    def append(self, book):
        """
        adauga un obiect carte in fisier si in memorie
        :param book: Book: cartea care se adauga
        :return: None
        """
        BookRepository.append(self, book)

        self.store_to_file()
    def remove(self, book):
        """
        sterge un obiect carte din fisier si din memorie
        :param book: Book: cartea care se va sterge
        :return: None
        """
        BookRepository.remove(self, book)

        self.store_to_file()

