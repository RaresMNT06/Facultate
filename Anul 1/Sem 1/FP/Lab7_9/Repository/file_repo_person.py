from Error.repository_error import Repo_error
from Domain.domain_person import Person


class FileRepositoryPer:

    def __init__(self, filename):
        """
        Repository de persoane care lucrează cu fișier text.
        La pornire încarcă toate persoanele în memorie.
        """
        self.__filename = filename
        self.__person = []
        self.__load_from_file()


    def __load_from_file(self):
        """
        Încarcă toate persoanele din fișier în lista __person.
        Dacă fișierul nu există, îl creează gol.
        """
        self.__person = []
        try:
            with open(self.__filename, "r") as f:
                for line in f:
                    line = line.strip()
                    if line == "":
                        continue
                    parts = line.split(";")
                    person = Person(int(parts[0]), parts[1], parts[2])
                    self.__person.append(person)

        except FileNotFoundError:
            open(self.__filename, "w").close()

    def write_to_file(self):
        """
        Rescrie TOT fișierul pe baza listei curente __person.
        """
        with open(self.__filename, "w") as f:
            for p in self.__person:
                line = f"{p.get_id()};{p.get_nume()};{p.get_adresa()}"
                f.write(line + "\n")

    def addPerson(self, person):
        """
        Adaugă o persoană și salvează lista în fișier.
        """
        for local_person in self.__person:
            if local_person.get_id() == person.get_id():
                raise Repo_error("Boss deja persoana asta este")

        self.__person.append(person)
        self.write_to_file()

    def read_list(self):
        """
        Returnează o copie a listei de persoane.
        """
        return list(self.__person)

    def updatePerson(self, person):
        for local_person in self.__person:
            if local_person.get_id() == person.get_id():
                return local_person
        raise Repo_error("Persoana nu exista!")



    def deletePerson(self, person):
        """
        Șterge persoana și scrie lista actualizată în fișier.
        """
        for local_person in self.__person:
            if local_person.get_id() == person.get_id():
                self.__person.remove(local_person)
                self.write_to_file()
                return

        raise Repo_error("Persoana nu exista!")