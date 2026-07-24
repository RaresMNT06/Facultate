class Eveniment:

    def __init__(self, id_eveniment, data, timp, descriere):
        self.__id_eveniment = id_eveniment
        self.__data = data
        self.__timp = timp
        self.__descriere = descriere

    def get_id_ev(self):
        return self.__id_eveniment
    def get_data(self):
        return self.__data
    def get_timp(self):
        return self.__timp
    def get_descriere(self):
        return self.__descriere
    def set_data(self, data):
        self.__data = data
    def set_timp(self, timp):
        self.__timp = timp
    def set_descriere(self, descriere):
        self.__descriere = descriere

    def __str__(self):
        return f"Eveniment ID: {self.__id_eveniment} Data: {self.__data} Timp: {self.__timp} Descriere: {self.__descriere}"