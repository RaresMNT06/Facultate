from domain.domain_sedinte import Sedinte
from datetime import date
from repo.repo_exeption import RepoException

class Repo_sedinte:

    def __init__(self, filename):
        self.__sedinte = []
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        self.__sedinte = []

        try:
            with open(self.__filename, 'r') as f:
                for line in f:
                    linie = line.strip()
                    if linie:
                        val = linie.split(',')
                        sedinta = Sedinte(val[0], val[1],val[2],val[3])
                        self.__sedinte.append(sedinta)

        except FileNotFoundError:
            open(self.__filename, 'w').close()

    def __save_to_file(self):
        with open(self.__filename, 'w') as f:
            for sedinta in self.__sedinte:
                linie = f"{sedinta.get_data()}, {sedinta.get_ora()},{sedinta.get_subiect()},{sedinta.get_stare()}\n"
                f.write(linie)

    def adaugare_sedinta(self, sedinta):

        date_today = date.today().strftime("%d:%m")

        if sedinta.get_data() < date_today:
            raise RepoException("Data incorecta")

        for s in self.__sedinte:
            if s.get_subiect() == sedinta.get_ora() and s.get_stare() == sedinta.get_stare():
                raise RepoException("Sedinta incorecta")

        self.__sedinte.append(sedinta)
        self.__save_to_file()

    def get_all_sedinta(self):
        return self.__sedinte