from domain.domain_automobile import DomainAutomobile


class ServiceAutomobile:

    def __init__(self, validate, repo):
        self.__validate = validate
        self.__repo = repo

    def adaugare_automobile(self,id_a, marca, pret,model,data):
        automobil = DomainAutomobile(id_a, marca, pret, model, data)
        self.__validate.validator_automobile(automobil)
        self.__repo.adaugare_automobile(automobil)

    def stergere_automobile(self, cifra):
        cif = self.__repo.stergere_automobile(cifra)
        return cif