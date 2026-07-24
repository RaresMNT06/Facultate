from domain.domain_melodii import DomainMelodii
class ServiceMelodii:

    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator

    def update_melod(self, titlu, artist):
        melodie = DomainMelodii( titlu, artist, "", "")
        return self.__repo.update_melodie(melodie)

    def save_melodie(self, melodie):

        self.__validator.validator_melodie(melodie)
        self.__repo.save_to_file_public()