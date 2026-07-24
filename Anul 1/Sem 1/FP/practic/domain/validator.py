from domain.validator_exeption import ValidatorException
from datetime import datetime

class Validator:

    def validator_sedinta(self, sedinta):

        """
        Validator pentru sedinta
        :param sedinta: Sedinta care se verifica daca data este introdusa corect,ora etc
        :return: Se returneaza o lista care contine toate erorile
        """

        error = []
        try:
            datetime.strptime(sedinta.get_data(), "%d.%m")
        except ValueError:
            error.append("Data invalida!")

        try:
            datetime.strptime(sedinta.get_ora(), "%H:%M")
        except ValueError:
            error.append("Ora invalida!")

        stari_validare = ["extraordinara" , "normala"]
        if sedinta.get_stare() not in stari_validare:
            error.append("Stare invalida!")

        if sedinta.get_subiect() == "":
            error.append("Subiect vid!")

        if len(error) > 0:
            raise ValidatorException(error)