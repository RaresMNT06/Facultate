from Error.repository_error import Repo_error
from Domain.domain_inscriere import Participare


class FileRepositoryInscriere:

    def __init__(self, filename):
        """
        Repository pentru inscrieri pe baza unui fisier text.
        """
        self.__filename = filename
        self.__participari = []
        self.__load_from_file()

    def __load_from_file(self):
        """
        Încarcă toate înscrierile din fișier în memorie.
        """
        self.__participari = []

        try:
            with open(self.__filename, "r") as f:
                for line in f:
                    line = line.strip()
                    if line == "":
                        continue

                    parts = line.split(";")

                    participare = Participare(
                        int(parts[0]),  # id_person
                        int(parts[1])   # id_eveniment
                    )

                    self.__participari.append(participare)

        except FileNotFoundError:
            open(self.__filename, "w").close()

    def write_to_file(self):
        """
        Scrie toate participările în fișier.
        """
        with open(self.__filename, "w") as f:
            for p in self.__participari:
                line = f"{p.get_id_person()};{p.get_id_eveniment()}"
                f.write(line + "\n")

    def addinscriere(self, participare):
        """
        Adaugă o participare nouă și o salvează în fișier.
        """
        for inscriere in self.__participari:
            if (inscriere.get_id_person() == participare.get_id_person() and
                inscriere.get_id_eveniment() == participare.get_id_eveniment()):
                raise Repo_error("Boss persoana este deja inscrisa in acest eveniment")

        self.__participari.append(participare)
        self.write_to_file()

    def get_list(self):
        """
        Returnează o copie a listei de participări.
        """
        return list(self.__participari)