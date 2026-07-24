

class ServiceTeorii:

    def __init__(self,repo):
        self.__repo = repo

    def sort_teorii(self,string):

        """
        Cerinta 1
        :param string: Un string dat de la tastatura
        :return: O lista sortata descrescator dupa nivelul de credibilitate
        """
        list_teorii_str = []
        list_teorii = self.__repo.get_all()

        for f in list_teorii:
            if string in f.get_titlu():
                list_teorii_str.append(f)



        list_teorii_str.sort(key = lambda  t: t.get_niv_cred(),  reverse = True)
        return list_teorii_str


    def raport(self,number):

        """
        Cerinta 2
        :param number: Numarul cu care se compara raportul
        :return: Returneaza o lista care contine doar teorii de care avem nevoie
        """
        lista= self.__repo.get_all()
        lista_return =[]

        for f in lista:
            if f.get_niv_cred()*f.get_nr_dov()/100 > number:
                lista_return.append(f)

        return lista_return






