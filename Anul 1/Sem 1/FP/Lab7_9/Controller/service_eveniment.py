import random
import string
from Domain.domain_eveniment import Eveniment
from Domain.validator.validator_eveniment import Eveniment_Val
from Sortari.sortari import Sorts


class ServiceEv:
    """
    Clasa ServiceEv gestioneaza logica aplicatiei pentru obiectele de tip Eveniment
    Ea interactioneaza cu repository ul pentru a efectua operatii CRUD
    """
    def __init__(self, repository_eveniment):
        self.__repository_eveniment = repository_eveniment

    def add_ev(self, id_eveniment, data, timp,descriere):
        """
        Creeaza un eveniment nou si il adauga in repository

        :param id_eveniment: int — identificatorul unic al evenimentului
        :param data: str — data evenimentului
        :param timp: str — timpul evenimentului
        :param descriere: str — descrierea evenimentului
        """
        eveniment = Eveniment(id_eveniment, data, timp, descriere)
        Eveniment_Val(eveniment).validate_ev()
        self.__repository_eveniment.addEveniment(eveniment)




    def get_list_evenimente(self):
        """
        Returneaza lista completa de evenimente din repository

        :return: list — lista obiectelor de tip Eveniment
        """
        copie= self.__repository_eveniment.read_list()[:]
        copie = Sorts.quick_sort(copie, key=lambda x:x.get_id_ev())
        return copie

    def update_eveniment(self, eveniment_id):
        """
        Actualizeaza un eveniment existent din repository pe baza ID ului

        :param eveniment_id: int sau str — identificatorul evenimentului care trebuie actualizat
        """
        eveniment = Eveniment(eveniment_id, None, None, None)
        return self.__repository_eveniment.updateEveniment(eveniment)

    def delete_eveniment(self, eveniment_id):
        """
        Sterge un eveniment din repository pe baza ID ului

        :param eveniment_id: int — identificatorul evenimentului care trebuie sters
        """
        eveniment = Eveniment(eveniment_id, None, None, None)
        self.__repository_eveniment.deleteEveniment(eveniment)
    """
    def cauta_eveniment(self, id_eveniment):

        try:
            return self.update_eveniment(id_eveniment)
        except Repo_error:
            return Service_error("Evenimentul nu exista!")
    """
    """_______________________________________________________________________________________________"""

    def cauta_eveniment(self, lista, id_eveniment):
        """
        Functie recursiva de cautare eveniment
        Complexitate: O(n)
        """
        if not lista:
            return None

        if lista[0].get_id_ev() == id_eveniment:
            return lista[0]

        return self.cauta_eveniment(lista[1:], id_eveniment)

    def salveaza_in_fisier_ev(self):
        self.__repository_eveniment.write_to_file()


    """RANDOM LAB 8"""

    def random_id_e(self):
        return random.randint(100000000, 999999999)

    def random_data(self):
        lungime = random.randint(4, 15)
        data = ""
        for i in range(lungime):
            data += random.choice(string.ascii_lowercase)
        return data

    def random_timp(self):
        lungime = random.randint(4, 15)
        time = ""
        for i in range(lungime):
            time += random.choice(string.ascii_lowercase)
        return time

    def random_des(self):
        lungime = random.randint(4, 15)
        des = ""
        for i in range(lungime):
            des += random.choice(string.ascii_lowercase)
        return des

    def random_evenimente(self, nr):
        for i in range(nr):
            id_ev = self.random_id_e()
            data = self.random_data()
            timp = self.random_timp()
            descriere = self.random_des()
            self.add_ev(id_ev, data, timp, descriere)

