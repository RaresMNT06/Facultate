class Person:
    def __init__(self, person_id , nume, adresa):
        self.__person_id = person_id
        self.__nume = nume
        self.__adresa = adresa
    def get_id(self):
        return self.__person_id
    def get_nume(self):
        return self.__nume
    def set_nume(self, nume):
        self.__nume = nume
    def get_adresa(self):
        return self.__adresa
    def set_adresa(self, adresa):
        self.__adresa = adresa

    def __str__(self):
        return f"Person ID: {self.__person_id}  Nume: {self.__nume} Adresa: {self.__adresa}"







