class DomainAutomobile:

    def __init__(self, id_automobile, marca, pret, model, data):
        self.__id_automobile = id_automobile
        self.__marca = marca
        self.__pret = pret
        self.__model = model
        self.__data = data

    def get_id_automobile(self):
        return self.__id_automobile
    def get_marca(self):
        return self.__marca
    def get_pret(self):
        return self.__pret
    def get_model(self):
        return self.__model
    def get_data(self):
        return self.__data
    def set_id_automobile(self, id_automobile):
        self.__id_automobile = id_automobile
    def set_marca(self, marca):
        self.__marca = marca
    def set_pret(self, pret):
        self.__pret = pret
    def set_model(self, model):
        self.__model = model
    def set_data(self, data):
        self.__data = data
