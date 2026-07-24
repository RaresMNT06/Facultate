
from domain.validator_exeption import ValidatorException
from controller.service_sedinte import ServiceSedinte
from repo.repo_sedinte import Repo_sedinte
from domain.validator import Validator
from datetime import datetime

def test_service():

    f_test = "test_sedinte.txt"
    open(f_test, 'w').close()
    repo_sedinte = Repo_sedinte(f_test)
    validate = Validator()
    service = ServiceSedinte(repo_sedinte,  validate)
    """
    Test service adaugare
    """
    try:
        service.adaugare("20.0a", "18:00", "camion", "normala")
        assert False
    except ValidatorException:
        assert True

    """Teste pentru sedintele de maine"""
    open(f_test, 'w').close()

    service.adaugare("08.02", "18:00", "camion", "normala")
    test_sedinte_maine = service.sedinte_maine()
    #assert len(test_sedinte_maine)==1
    """Teste pentru tabel in functie de data data"""
    open(f_test, 'w').close()

    service.adaugare("23.05", "18:00", "tractor", "normala")
    service.adaugare("24.05", "23:00", "masina", "extraordinara")
    data_set_test = "23.05"
    data_set_maine_nustr = datetime.strptime(data_set_test, "%d.%m")
    test_sedinte_data = service.tabel_data(data_set_maine_nustr)
    assert len(test_sedinte_data)==2

