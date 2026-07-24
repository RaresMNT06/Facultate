from domain.validator_exeption import ValidatorExeption
from datetime import datetime


class ValidateAuto:

    def validator_automobile(self, automobile):

        erori= []
        try:
            datetime.strptime(automobile.get_data(), "%d:%m:%Y")
        except ValueError:
            (erori.append("Date not valid"))

        if automobile.get_id_automobile() <1:
            erori.append("Id not valid")

        if automobile.get_pret() <1:
            erori.append("Pret not valid")

        if automobile.get_marca() == "":
            erori.append("No marca")

        if len(erori)>0:
            raise ValidatorExeption(erori)





