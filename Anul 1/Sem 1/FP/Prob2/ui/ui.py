

class UI:

    def __init__(self,service):
        self.__service = service

    def menu(self):

        print("Meniu Principal")
        print("1. Adaugare automobil")
        print("2. Stergere automobil")
        print("0. Exit")

    def adaugare(self):

        try:
            id_a = int(input("Introduceti id:"))
            marca=input("Introduceti marca: ")
            pret= int(input("introduceti pret: "))
            model=input("Introduceti model: ")
            data=input("Introduceti data(dd:mm:yy): ")
            self.__service.adaugare_automobile(id_a,marca,pret,model,data)
            print("Autoobil adaugat")
        except Exception as e:
            print(e)



    def stergere(self):
        cifra=int(input("Introduceti cifra:"))
        cif = self.__service.stergere_automobile(cifra)
        print(f"S-au sters {cif} masini")

    def start(self):


        self.menu()
        option = int(input("Alegeti optiunea:"))
        while True:
            if option == 1:
                self.adaugare()
            if option == 2:
                self.stergere()
            if option == 0:
                print("byebye")
                break
            option = int(input("Alegeti optiunea:"))


