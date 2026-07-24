from domain.domain_sedinte import Sedinte
from datetime import date, timedelta



class ServiceSedinte:

    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator

    def adaugare(self, data, ora, subiect,stare):


        sedinta = Sedinte(data,ora,subiect,stare)
        self.__validator.validator_sedinta(sedinta)
        self.__repo.adaugare_sedinta(sedinta)

    def sedinte_maine(self):

        toate_sedintele = self.__repo.get_all_sedinta()

        data_t = date.today() + timedelta(days=1)
        data_maine = data_t.strftime("%d:%m")

        sedinte_maine = []
        for s in toate_sedintele:
            if s.get_data() == data_maine:
                sedinte_maine.append(s)

        sedinte_maine.sort(key=lambda x: x.get_ora())
        return sedinte_maine

    def tabel_data(self,data_setata):

        toate_sedintele = self.__repo.get_all_sedinta()

        data_3zile = data_setata + timedelta(days=2)
        data_s = data_setata.strftime("%d:%m")
        data_3 = data_3zile.strftime("%d:%m")
        sedinte_3zile = []
        for s in toate_sedintele:
            if data_s <= s.get_data() <= data_3:
                sedinte_3zile.append(s)

        return sedinte_3zile
