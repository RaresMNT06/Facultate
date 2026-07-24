from domain.domain_automobile import DomainAutomobile
from repo.repo_exeption import RepoExeption

class RepoAutomobile:

    def __init__(self, filename):
        self.__automobile= []
        self.__filename = filename
        self.__load_from_file()

    def __load_from_file(self):
        self.__automobile= []
        try:
            with open(self.__filename, 'r') as file:
                for line in file:
                    linie = line.strip()
                    if linie:
                        val = linie.split(",")
                        automobil = DomainAutomobile(int(val[0]), val[1], int(val[2]), val[3], val[4])
                        self.__automobile.append(automobil)

        except FileNotFoundError:
            open(self.__filename, 'w').close()

    def __save_to_file(self):
        """
        Salveaza in fisier
        """
        with open(self.__filename, 'w') as file:
            for automobil in self.__automobile:
                linie = f"{automobil.get_id_automobile()},{automobil.get_marca()},{automobil.get_pret()},{automobil.get_model()},{automobil.get_data()}\n"
                file.write(linie)

    def adaugare_automobile(self, automobil):
        """
        Adaugare automobile
        :param automobil:Obiectul care se adauga in fisier
        :return:In caz de exista un automobil la fel cu id ul celui introdus va da eroare
        """

        for a in self.__automobile:
            if a.get_id_automobile()  == automobil.get_id_automobile():
                raise RepoExeption("Id ul deja exista")

        self.__automobile.append(automobil)
        self.__save_to_file()

    def stergere_automobile(self, cifra):
        """
        Stergere automobile daca cifra se afla in pretul acestora
        :param cifra: cifra introdusa la tastatura
        :return: contorul(numarul de automobile sterse)
        """
        contor = 0
        for a in self.__automobile:
            pret = a.get_pret()
            cifgasit = 0
            while pret>=1:
                if cifra == pret%10 and cifgasit==0:
                    self.__automobile.remove(a)
                    contor += 1
                    cifgasit+=1
                else:
                    pret//=10

        self.__save_to_file()
        return contor

    def get_all(self):
        return self.__automobile




