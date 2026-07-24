from datetime import datetime
class Ui:

    def __init__(self, service_sedinte):
        self.__service_sedinte = service_sedinte

    def menu(self):
        """
        Meniu principal
        :return:
        """
        print("Meniu Principal")
        print("Adaugare Sedinte.1")
        print("Tabel data.2")
        print("Export.3")
        print("Exit.0")

    def sedinte_maine(self):
        """
        Sedinte maine(ex 1)
        :return: Se afiseaza la inceputul programului toate sedintele de main
        in caz contrar afiseaza un mesaj ca nu exista
        """

        print("\nSedinte maine")
        sedinte = self.__service_sedinte.sedinte_maine()
        if not sedinte:
            print("Nu exista sedinte maine")

        else:
            for s in sedinte:
                print(f"{s.get_data()} | {s.get_ora()} | {s.get_subiect()} - {s.get_stare()}")

    def adaugare_sedinte(self):
        """
        Adaugare sedinte(ex 2)
        :return: In caz de datele nu sunt introduse corect se va afisa o eroare
        """

        try:
            data = input("data(dd.mm): ")
            ora = input("ora(hh:mm): ")
            subiect = input("subiect: ")
            starea= input("stare(normala/extraordinara): ")
            self.__service_sedinte.adaugare(data, ora, subiect, starea)
            print("Sedinta adaugata!")
        except Exception as e:
            print(e)

    def sedinte_data(self):
        """
        Sedinte data(ex 3)
        Se introduce data str si trbuie convertita de tip time pentru a compara cu data de maine
        :return: Afiseaza toate sedintele de la data respectiva inclusiv cele de dupa 3 zile
        """
        data_str = input("data(dd.mm): ")
        data_nustr=datetime.strptime(data_str, "%d.%m")
        sedinte = self.__service_sedinte.tabel_data(data_nustr)
        if not sedinte:
            print("Nu exista sedinte maine")
        else:
            print(" DATA |  ORA  | SUBIECT - STARE")
            for s in sedinte:
                print(f"{s.get_data()} | {s.get_ora()} | {s.get_subiect()} - {s.get_stare()}")

    def fis_ex(self):
        """
        Sedinte Export(ex 4)
        :return:
        """
        nume_fisier = input("Introduceti denumire fisier(ex: fisier.txt): ")
        sir_caract = input("Introduceti un sir de caractere: ")
        self.__service_sedinte.fis_ex_service(nume_fisier, sir_caract)


    def start(self):


        self.menu()
        self.sedinte_maine()
        option = int(input("Alegeti optiunea: "))
        while True:
            if option == 1:
                self.adaugare_sedinte()
            if option == 2:
                self.sedinte_data()
            if option == 0:
                print("byebye")
                break

            option = int(input("Alegeti optiunea: "))




