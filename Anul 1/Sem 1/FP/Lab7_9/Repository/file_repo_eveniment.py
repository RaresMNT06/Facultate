from Error.repository_error import Repo_error
from Domain.domain_eveniment import Eveniment


class FileRepositoryEv:

    def __init__(self, filename):
        """
        Repository pentru evenimente pe fișier.
        Încarcă evenimentele în memorie la pornire.
        """
        self.__filename = filename
        self.__evenimente = []
        self.__load_from_file()

    def __load_from_file(self):
        """
        Încarcă evenimentele din fișier.
        Creează fișierul dacă nu există.
        """
        self.__evenimente = []

        try:
            with open(self.__filename, "r") as f:
                for line in f:
                    line = line.strip()
                    if line == "":
                        continue

                    parts = line.split(";")
                    ev = Eveniment(int(parts[0]),parts[1],parts[2],parts[3])
                    self.__evenimente.append(ev)

        except FileNotFoundError:
            open(self.__filename, "w").close()

    def write_to_file(self):
        """
        Scrie întreaga listă de evenimente în fișier.
        """
        with open(self.__filename, "w") as f:
            for ev in self.__evenimente:
                line = f"{ev.get_id_ev()};{ev.get_data()};{ev.get_timp()};{ev.get_descriere()}"
                f.write(line + "\n")

    def addEveniment(self, eveniment):
        """
        Adaugă un eveniment și rescrie fișierul.
        """
        for local_ev in self.__evenimente:
            if local_ev.get_id_ev() == eveniment.get_id_ev():
                raise Repo_error("Boss deja evenimentul asta este!")

        self.__evenimente.append(eveniment)
        self.write_to_file()

    def deleteEveniment(self, eveniment):
        """
        Șterge un eveniment și actualizează fișierul.
        """
        for local_ev in self.__evenimente:
            if local_ev.get_id_ev() == eveniment.get_id_ev():
                self.__evenimente.remove(local_ev)
                self.write_to_file()
                return

        raise Repo_error("Evenimentul nu exista!")

    def read_list(self):
        """
        Returnează o copie a listei de evenimente.
        """
        return list(self.__evenimente)

    def updateEveniment(self, eveniment):
        """
        Returnează evenimentul cu ID-ul dat pentru a fi modificat în UI.
        Scrierea în fișier va fi făcută după modificare, în service/UI.
        """
        for local_ev in self.__evenimente:
            if local_ev.get_id_ev() == eveniment.get_id_ev():
                return local_ev

        raise Repo_error("Acest eveniment nu exista!")