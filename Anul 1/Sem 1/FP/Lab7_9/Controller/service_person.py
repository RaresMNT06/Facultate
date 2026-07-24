import string
import random
from Domain.domain_person import Person
from Domain.validator.validator_persoana import Person_Val
from Sortari.sortari import Sorts


class ServicePer:
    """
    Clasa Service gestioneaza logica aplicației pentru obiectele de tip Person
    Ea interacționeaza cu repository-ul pentru a efectua operații CRUD
    """
    def __init__(self, repository):
        self.__repository = repository

    def add_persoana(self, person_id, name, adresa):
        """
        Creeaza o persoana noua, o valideaza si o adauga în repository

        :param person_id: int — identificatorul unic al persoanei
        :param name: str — numele persoanei
        :param adresa: str — adresa persoanei
        :raise Exception: dacă persoana nu trece validarea sau există deja în repository
        """
        persoana = Person(person_id, name, adresa)
        Person_Val(persoana).validate()
        self.__repository.addPerson(persoana)

    def get_list_persoane(self):
        """
        Returneaza lista completa de persoane din repository

        :return: list — lista obiectelor de tip Person
        """
        copie =self.__repository.read_list()[:]
        copie = Sorts.gnome_sort(copie, key=lambda x:x.get_id())
        return copie

    def update_persoana(self, person_id):
        """
        Actualizeaza o persoana existenta din repository pe baza ID-ului

        :param person_id: int sau str — identificatorul persoanei care trebuie actualizata
        """
        persoana = Person(person_id, None, None)
        return self.__repository.updatePerson(persoana)

    def delete_persoana(self, person_id):
        """
        Sterge o persoana din repository pe baza ID-ului

        :param person_id: int-identificatorul persoanei care trebuie stearsa
        """
        persoana = Person(person_id, None, None)
        self.__repository.deletePerson(persoana)
    """
    def cauta_persoana(self, id_persoana):
        try:
            return self.update_persoana(id_persoana)
        except Repo_error:
            return Service_error("Persoana nu exista")
    """
    """________________________________________________________________________________________________-"""

    def cauta_persoana(self, lista, id_persoana):
        """
        Functie recursiva de cautare
        Complexitate: O(n)
        """
        if not lista:
            return None

        if lista[0].get_id() == id_persoana:
            return lista[0]

        return self.cauta_persoana(lista[1:], id_persoana)

    def salveaza_in_fisier(self):
        """
        Dacă repository-ul este FileRepositoryPer, scrie lista în fișier.
        Dacă este RepositoryPer (memorie), funcția nu face nimic.
        """
        self.__repository.write_to_file()

    """RANDOM LAB 8"""
    def random_id(self):
        return random.randint(100000000, 999999999)

    def random_name(self):
        lungime = random.randint(4, 15)
        name=""
        for i in range(lungime):
            name+= random.choice(string.ascii_lowercase)
        return name

    def random_adress(self):
        lungime = random.randint(4, 25)
        adresa = ""
        for i in range(lungime):
            adresa+=random.choice(string.ascii_lowercase)
        return adresa

    def random_person(self, nr):

        for i in range (nr):
            id_per = self.random_id()
            nume = self.random_name()
            adress = self.random_adress()
            self.add_persoana(id_per, nume,  adress)



