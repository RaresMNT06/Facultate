from Error.repository_error import Repo_error


class RepositoryEv:
    """
    Clasa RepositoryEv gestioneaza o lista de evenimente si ofera operatii
    CRUD (Create, Read, Update, Delete)
    """

    def __init__(self):
        self.__eveniment = []

    def addEveniment(self, eveniment):
        """
        Adauga un eveniment nou in lista daca nu exista deja unul cu acelasi ID

        :param eveniment: obiect de tip Eveniment (trebuie sa aiba metoda get_id_ev())
        :raise Repo_error: daca exista deja un eveniment cu acest ID
        """

        for local_eveniment in self.__eveniment:
            if local_eveniment.get_id_ev() ==eveniment.get_id_ev():
                raise Repo_error("Boss deja evenimentul asta este")
        self.__eveniment.append(eveniment)

    def deleteEveniment(self, eveniment):
        """
        Sterge un eveniment din repository pe baza ID ului

        :param eveniment: obiect de tip Eveniment (trebuie sa aiba metoda get_id_ev())
        """
        for local_eveniment in self.__eveniment:
            if local_eveniment.get_id_ev() == eveniment.get_id_ev():
                self.__eveniment.remove(local_eveniment)

    def read_list(self):
        """
        Returneaza o copie a listei de evenimente existente in repository

        :return: lista noua care contine toate evenimentele
        """
        return list(self.__eveniment)

    def updateEveniment(self, eveniment):
        """
        Actualizeaza informatiile unui eveniment existent in repository pe baza ID ului

        :param eveniment: obiect de tip Eveniment care contine ID ul si noile valori
        """

        for local_eveniment in self.__eveniment:
            if local_eveniment.get_id_ev() == eveniment.get_id_ev():
                   return local_eveniment
        raise Repo_error("Acest eveniment nu exista!")
