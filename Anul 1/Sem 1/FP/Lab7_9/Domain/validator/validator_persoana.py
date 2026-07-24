from Error.validator_error import Val_error

class Person_Val:

    def __init__(self, person):
        self.__person = person

    def validate(self):
        for i in "1234567890":
            if i in self.__person.get_nume():
                raise Val_error("Numele nu este valid!")
        if len(self.__person.get_nume()) == 0:
            raise Val_error("Numele nu este valid!")
        if len(self.__person.get_adresa()) ==0 :
            raise Val_error("Adresa nu este valida")
        if len(str(self.__person.get_id()))<=1:
            raise Val_error("ID invalid")

