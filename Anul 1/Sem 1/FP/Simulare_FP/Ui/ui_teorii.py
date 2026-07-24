

class UiTeorii:

    def __init__(self,service):
        self.__service = service

    def str_in_titlu(self,string):

        """
        Cerinta 1
        :param string: String dat de la tastatura
        :return: Returneaza o lista sortata descrescator cu elemente care contin un string dat de la tastatura
        """

        lista = self.__service.sort_teorii(string)

        if  len(lista) == 0:
            print("Nu exista astfel de teorii")
            return
        else:
            return lista

    def cerinta_2(self,number):

        """
        Cerinta 2
        :param number: Numarul cu care se compara raportul
        :return: Afiseaza tipul teoriei si niv_cred+nr_dov in caz contrar nu se va afisa nimic
        """

        lista= self.__service.raport(number)

        if  len(lista) == 0:
            print("Nu exista astfel de teorii")
            return


        for t in lista:
            print(f"{t.get_tip()}:{t.get_niv_cred()},{t.get_nr_dov}")



    def run(self):

        print("Menu")
        print("Cerinta 1: Introduceti 1")
        print("Cerinta 2: Introduceti 2")
        print("Exit: Introduceti 0")

        option = int(input("Introduceti optiunea: "))

        if option == 1:
            part = input("Introduceti string ul: ")
            self.str_in_titlu(part)

        elif option ==2:
            number = int(input("Intorduceti numarul: "))
            self.cerinta_2(number)

        elif option == 0:
            print("Bye")
            return



