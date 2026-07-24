from datetime import datetime
class Ui:

    def __init__(self, service_sedinte):
        self.__service_sedinte = service_sedinte

    def menu(self):
        print("Meniu Principal")
        print("Adaugare Sedinte.1")
        print("Tabel data.2")
        print("Exit.0")

    def sedinte_maine(self):

        print("\nSedinte maine")
        sedinte = self.__service_sedinte.sedinte_maine()
        if not sedinte:
            print("Nu exista sedinte maine")

        else:
            for s in sedinte:
                print(f"{s.get_data()} {s.get_ora()} - {s.get_subiect()}")

    def adaugare_sedinte(self):

        try:
            data = input("data(dd:mm): ")
            ora = input("ora(hh:mm): ")
            subiect = input("subiect: ")
            starea= input("stare(normala/extraordinara): ")
            self.__service_sedinte.adaugare(data, ora, subiect, starea)
            print("Sedinta adaugata!")
        except Exception as e:
            print(e)

    def sedinte_data(self):
        data_str = input("data(dd:mm): ")
        data_nstr=datetime.strptime(data_str, "%d:%m")
        sedinte = self.__service_sedinte.tabel_data(data_nstr)

        for s in sedinte:
            print(f"{s.get_data()} {s.get_ora()} - {s.get_subiect()} - {s.get_stare()}")


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




