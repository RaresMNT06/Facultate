class Participare:

    def __init__(self, id_person, id_eveniment):
        self.__id_person = id_person
        self.__id_eveniment = id_eveniment

    def get_id_person(self):
        return self.__id_person

    def get_id_eveniment(self):
        return self.__id_eveniment

    def __str__(self):
        return f"Persoana {self.__id_person} participa la evenimentul {self.__id_eveniment}"

