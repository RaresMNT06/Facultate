from menu import *
from Error.repository_error import Repo_error
from Error.validator_error import Val_error
from Error.service_error import Service_error

class UI:
    """
    Clasa UI gestioneaza interactiunea cu utilizatorul
    Aceasta preia input-ul de la utilizator si apeleaza metodele corespunzatoare din Service
    """
    def __init__(self, service_persoana, service_eveniment, service_inscriere):
        self.__service_persoana = service_persoana
        self.__service_eveniment = service_eveniment
        self.__service_inscriere = service_inscriere

    def add_person(self):

        """
        Functia pentru adaugare persoane

        Citeste ID-ul, numele si adresa de la utilizator si adauga o persoana in service
        """
        try:
            id_persoana = int(input("ID Persoana: "))
        except ValueError:
            print("!!!ID invalid!!!")
            return
        nume = input("Nume: ")
        adresa = input("Adresa: ")
        try:
            self.__service_persoana.add_persoana(id_persoana, nume, adresa)
        except Repo_error as e:
            print(e)
        except Val_error as er:
            print(er)

    def del_person(self):

        """
        Functia pentru stergere persoane

        Citeste ID-ul persoanei care trebuie stearsa si apeleaza service.delete()
        """
        try:
            id_person = int(input("Introduceti ID ul persoanei pe care doriti sa o stergeti: "))
        except ValueError:
            print("!!!ID invalid!!!")
            return
        self.__service_persoana.delete_persoana(id_person)

    def readList(self):

        """
        Functia pentru afisare persoane

        :return: lista tuturor persoanelor din service
        """
        return self.__service_persoana.get_list_persoane()

    def update_person(self):

        """
        Functia pentru modificare persoane

        Citeste ID-ul persoanei care trebuie actualizata si apeleaza service.update()
        """
        try:
            id_persoana = int(input("Introduceti ID ul persoanei pe care doriti sa o modificati: "))
        except ValueError:
            print("!!!ID invalid!!!")
            return
        try:
            pers = self.__service_persoana.update_persoana(id_persoana)
        except Repo_error as e:
            print(e)
            return

        menu_update_persoana()

        opt = int(input("Alegeti optiunea: "))
        if opt == 1:
            nume_nou = input("Nume nou: ")
            pers.set_nume(nume_nou)
            self.__service_persoana.salveaza_in_fisier()
        elif opt == 2:
            adresa_noua = input("Adresa noua: ")
            pers.set_adresa(adresa_noua)
            self.__service_persoana.salveaza_in_fisier()

    def add_eveniment(self):
        """
        Functia pentru adaugare evenimente

        Citeste ID ul, data, timpul si descrierea de la utilizator si adauga un eveniment in service
        """
        try:
            id_eveniment = int(input("Introduceti id ul evenimentului: "))
        except ValueError:
            print("!!!ID invalid!!!")
            return
        data = input("Introduceti data: ")
        timp = input("Introduceti timpul: ")
        descriere = input("Introduceti descriere: ")
        try:
            self.__service_eveniment.add_ev(id_eveniment, data, timp, descriere)
        except Repo_error as e:
            print(e)
        except Val_error as er:
            print(er)

    def del_eveniment(self):
        """
        Functia pentru stergere evenimente

        Citeste ID ul evenimentului care trebuie sters si apeleaza service.delete()
        """
        try:
            id_eveniment = int(input("Introduceti ID ul evenimentului pe care doriti sa o stergeti: "))
        except ValueError:
            print("!!!ID invalid!!!")
            return
        self.__service_eveniment.delete_eveniment(id_eveniment)

    def readEveniment(self):
        """
        Functia pentru afisare evenimente

        :return: lista tuturor evenimentelor din service
        """
        return self.__service_eveniment.get_list_evenimente()

    def update_eveniment(self):
        """
        Functia pentru modificare evenimente

        Citeste ID ul evenimentului care trebuie actualizat si apeleaza service.update()
        """
        try:
            id_eveniment = int(input("Introduceti ID ul evenimentului pe care doriti sa o modificati: "))
        except ValueError:
            print("!!!ID invalid!!!")
            return
        try:
            ev = self.__service_eveniment.update_eveniment(id_eveniment)
        except Repo_error as e:
            print(e)
            return

        menu_update_eveniment()

        opt = int(input("Alegeti optiunea: "))
        if opt == 1:
            data_noua = input("Introduceti data noua: ")
            ev.set_data(data_noua)
            self.__service_eveniment.salveaza_in_fisier_ev()
        elif opt == 2:
            timp_nou = input("Introduceti timp nou: ")
            ev.set_timp(timp_nou)
            self.__service_eveniment.salveaza_in_fisier_ev()
        elif opt == 3:
            des_nou = input("Introduceti descriere noua: ")
            ev.set_descriere(des_nou)
            self.__service_eveniment.salveaza_in_fisier_ev()

    def random_pers(self):

        """
        Generează și adaugă un număr aleator de persoane în sistem.

        Cere utilizatorului un număr n și apelează service-ul pentru a crea n persoane
        cu id, nume și adresă generate automat.
        """

        op = int(input("Introduceti numarul de persoane pe care vreti sa il adaugati: "))
        self.__service_persoana.random_person(op)

    def random_ev(self):
        """
        Generează și adaugă un număr aleator de evenimente în sistem.

        Cere utilizatorului un număr n și apelează service-ul pentru a crea n evenimente
        cu id, dată, timp și descriere generate automat.
        """

        op = int(input("Introduceti numarul de evenimente pe care vreti sa il adaugati: "))
        self.__service_eveniment.random_evenimente(op)

    def inscriere(self):
        """
        Înscrie o persoană la un eveniment.
        """
        try:
            id_ev = int(input("Introduceti id ul evenimentului: "))
            id_pers = int(input("Introduceti id ul persoanei: "))
            self.__service_inscriere.add_inscriere(id_ev, id_pers)
        except Service_error as e:
            print(e)
        except ValueError:
            print("ID INTRODUS GRESIT")


    def readInscrieri(self):
        """
        Afișează toate înscrierile.
        """

        return self.__service_inscriere.read_list_inscriere()

    def cauta_person(self):
        """
        Caută o persoană după ID și o afișează.
        """
        lista = self.__service_persoana.get_list_persoane()
        try:
            id_pers = int(input("Introduceti id ul persoanei:"))
            persoana = self.__service_persoana.cauta_persoana(lista, id_pers)
            print(persoana)
        except ValueError:
            print("ID INVALID")
        except Service_error as e:
            print(e)

    def cauta_eveniment(self):
        """
        Caută un eveniment după ID și îl afișează.
        """
        lista = self.__service_eveniment.get_list_evenimente()

        try:
            id_ev = int(input("Introduceti id ul evenimentului: "))
            eveniment = self.__service_eveniment.cauta_eveniment(lista, id_ev)
            print(eveniment)
        except ValueError:
            print("ID INVALID")
        except Service_error as e:
            print(e)

    def raport_evenimente_persoana(self):
        """
        Afișează evenimentele unei persoane, ordonate după descriere și dată.
        """
        try:
            id_pers = int(input("Introduceti ID-ul persoanei: "))
        except ValueError:
            print("ID invalid!")
            return

        try:
            lista = self.__service_inscriere.raport_evenimente_persoana_ordonate(id_pers)
        except Service_error as e:
            print(e)
            return
        if not lista:
            print("Aceasta persoana nu participa la niciun eveniment!")
            return

        print("Evenimente la care participa persoana: ")
        for ev in lista:
            print(f"ID: {ev.get_id_ev()}  Data: {ev.get_data()}  Timp: {ev.get_timp()}  Descriere: {ev.get_descriere()}")

    def raport_persoane_max(self):
        """
        Afișează persoanele care participă la cele mai multe evenimente.
        """
        lista = self.__service_inscriere.raport_persoane_max_evenimente()

        print("Persoanele care au cele mai multe evenimente:")
        for persoana, nr_ev in lista:
            print(f"{persoana.get_nume()} cu ID ul: {persoana.get_id()} are {nr_ev} evenimente")

    def raport_top_evenimente(self):
        """
        Afișează primele 20% dintre evenimentele cu cei mai mulți participanți.
        """
        lista = self.__service_inscriere.raport_top_evenimente()

        print("Primele 20% evenimente cu cei mai mulți participanți:")
        for ev, nr_part in lista:
            print(f"Eveniment: {ev.get_id_ev()} Descriere: {ev.get_descriere()}  participanti: {nr_part}")

    def rap_top(self):
        x = int(input("Introduceti top:"))
        lista = self.__service_inscriere.raport_top_persoane_evenimente(x)

        print(f"Topul {x} este:")
        for id_p, id_ev in lista:
            print(f"Eveniment: {id_ev} Persoana: {id_p}")


    def run(self):
        """
        Ruleaza interfata UI principala
        """

        while True:
            option = input("Introduceti comanda: ").lower().strip()
            op = option.split(" ")
            op =op[0]
            if op == "help":
                menu_principal()
            elif op == "add_person":
                self.add_person()
            elif op == "read":
                for i  in self.readList():
                    print(i)
            elif option == "delete_person":
                self.del_person()
            elif option == "update_person":
                self.update_person()
            elif option == "add_ev":
                self.add_eveniment()
            elif option == "read_ev":
                for i  in self.readEveniment():
                    print(i)
            elif option == "delete_ev":
                self.del_eveniment()
            elif option == "update_ev":
                self.update_eveniment()
            elif option == "random_pers":
                self.random_pers()
            elif option == "random_ev":
                self.random_ev()
            elif option == "inscriere":
                self.inscriere()
            elif option == "read_ins":
                for i in self.readInscrieri():
                    print(i)
            elif option == "cauta_person":
                self.cauta_person()
            elif option == "cauta_ev":
                self.cauta_eveniment()
            elif option == "rap_lista_ord":
                self.raport_evenimente_persoana()
            elif option == "rap_max_pers":
                self.raport_persoane_max()
            elif option == "rap_top_ev":
                self.raport_top_evenimente()
            elif option == "top":
                self.rap_top()
            elif option == "exit":
                print("bye")
                break




