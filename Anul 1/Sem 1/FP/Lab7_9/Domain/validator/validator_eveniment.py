from Error.validator_error import Val_error

class Eveniment_Val:

    def __init__(self, eveniment):
        self.__eveniment = eveniment

    def validate_ev(self):
        if len(str(self.__eveniment.get_id_ev()))<=1:
            raise Val_error("Id invalid")
        if len(self.__eveniment.get_data())==0:
            raise Val_error("Data invalida")
        if len(self.__eveniment.get_timp())==0:
            raise Val_error("Timp invalid")
        if len(self.__eveniment.get_descriere())== 0:
            raise Val_error("Descriere invalida")