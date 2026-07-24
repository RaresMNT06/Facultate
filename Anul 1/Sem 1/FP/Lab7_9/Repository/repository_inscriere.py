from Error.repository_error import Repo_error

class RepoInscriere:

    def __init__(self):
        """
        Repository pentru gestionarea înscrierilor (participărilor) persoanelor la evenimente.
        """
        self.__participari = []

    def addinscriere(self, participare):
        """
        Adaugă o înscriere nouă în listă.

        :param participare: obiect de tip Participare (conține id-ul persoanei și id-ul evenimentului)
        :raises Repo_error: dacă persoana este deja înscrisă la acel eveniment
        """
        for inscriere in self.__participari:
            if inscriere.get_id_person() == participare.get_id_person() and inscriere.get_id_eveniment() == participare.get_id_eveniment():
                raise Repo_error("Boss persoana este deja inscrisa in accest eveniment")
        self.__participari.append(participare)

    def get_list(self):
        """
        Returnează lista tuturor înscrierilor.

        :return: listă de obiecte Participare
        """
        return list(self.__participari)