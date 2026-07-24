from domain.validator_exception import ValidatorException
from datetime import datetime

class ValidatorMelodie:

    def validator_melodie(self, melodie):

        error = []

        try:
            datetime.strptime(melodie.get_data(), "%d.%m.%Y")
        except ValueError:
            error.append("Data invalida!")

        gen_melodie = ["Rock", "Pop", "Jazz"]
        if melodie.get_gen() not in gen_melodie:
            error.append("Gen invalid!")

        if melodie.get_title() == "":
            error.append("Titulu invalid!")

        if melodie.get_artist() == "":
            error.append("Artist invalid!")

        if len(error) > 0:
            raise ValidatorException(error)