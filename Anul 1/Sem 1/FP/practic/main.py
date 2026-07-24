from repo.repo_sedinte import Repo_sedinte
from domain.validator import Validator
from controller.service_sedinte import ServiceSedinte
from ui.ui_sedinte import Ui
from teste.teste_service import test_service
from teste.teste import test_adaugare

def test_sedinte():
    test_service()
    test_adaugare()
test_sedinte()
def main():

    repo = Repo_sedinte("sedinte.txt")
    validator = Validator()
    service = ServiceSedinte(repo, validator)
    ui = Ui(service)
    ui.start()

main()