from Error.repository_error import Repo_error

class RepositoryPer:

    """
    Clasa Repository gestionează o listă de persoane și oferă operații
    CRUD (Create, Read, Update, Delete)
    """

    def __init__(self):
        self.__person = []

    def addPerson(self, person):
        """
        Adauga o persoana noua în lista, dacă nu exista deja una cu același ID

        :param person: obiect de tip Person (trebuie sa aiba metoda get_id())
        :raise Exception: daca persoana exista deja în lista
        """

        for local_person in self.__person:
            if local_person.get_id() == person.get_id():
                raise Repo_error("Boss deja persoana asta este")
        self.__person.append(person)


    def read_list(self):
        """
        Returneaza o copie a listei de persoane existente in repository

        :param self: instanța curentă a clasei.
        :return: lista nouă care conține toate persoanele
        """
        return list(self.__person)

    def updatePerson(self, person):
        """
        Actualizeaza informațiile unei persoane existente în repository pe baza ID-uluicon

        :param person: obiect de tip Person, care conține ID-ul persoanei de actualizat și noile valori (nume sau adresa)
        """
        for local_person in self.__person:
            if local_person.get_id() == person.get_id():
                return local_person
        raise Repo_error("Persoana nu exista!")

    def deletePerson(self, person):
        """
        Sterge o persoana din repository pe baza ID-ului

        :param person: obiect de tip Person (trebuie să aibă metoda get_id())
        """
        for local_person in self.__person:
            if local_person.get_id() == person.get_id():
                self.__person.remove(local_person)