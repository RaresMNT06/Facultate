class Teorii:

    def __init__(self, id, titlu,tip,niv_cred,nr_dov):

        self.__id= id
        self.__titlu = titlu
        self.__tip = tip
        self.__niv_cred=niv_cred
        self.__nr_dov = nr_dov

    def get_id(self):
        return self.__id

    def get_titlu(self):
        return self.__titlu

    def get_tip(self):
        return self.__tip

    def get_niv_cred(self):
        return self.__niv_cred

    def get_nr_dov(self):
        return self.__nr_dov
