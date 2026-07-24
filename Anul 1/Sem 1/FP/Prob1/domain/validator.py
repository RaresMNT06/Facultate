from domain.validator_exception import ValidatorException
from datetime import datetime

class Validator:

    def validator_sedinta(self, sedinta):

        error = []
        try:
            datetime.strptime(sedinta.get_data(), "%d:%m")
        except ValueError:
            error.append("Data invalida!")

        try:
            datetime.strptime(sedinta.get_ora(), "%H:%M")
        except ValueError:
            error.append("Ora invalida!")

        stari_validare = ["exraordinara" , "normala"]
        if sedinta.get_stare() not in stari_validare:
            error.append("Stare invalida!")

        if sedinta.get_subiect() == "":
            error.append("Subiect vid!")

        if len(error) > 0:
            raise ValidatorException(error)