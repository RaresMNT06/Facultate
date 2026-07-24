from domain.domain_melodii import DomainMelodii
from repo.repo_exception import RepoException

class RepoMelodie:
    def __init__(self, filename):
        self.__melodie = []
        self.__filename = filename
        self.__load_from_file()


    def __load_from_file(self):

        self.__melodie = []

        try:
            with open(self.__filename, "r") as file:
                for line in file:
                    line = line.strip()
                    if line:
                        val = line.split(",")
                        music = DomainMelodii(val[0], val[1], val[2], val[3])
                        self.__melodie.append(music)

        except FileNotFoundError:
            open(self.__filename, "w").close()

    def __save_to_file(self):
        with open(self.__filename, "w") as filename:
            for melodie in self.__melodie:
                    linie = f"{melodie.get_title()},{melodie.get_artist()},{melodie.get_gen()},{melodie.get_data()}\n"
                    filename.write(linie)

    def update_melodie(self, music):
        for m in self.__melodie:
            if m.get_title().strip() == music.get_title().strip() and m.get_artist().strip() == music.get_artist().strip():
                return m
        raise RepoException("Melodia nu exista")

    def save_to_file_public(self):
        self.__save_to_file()
