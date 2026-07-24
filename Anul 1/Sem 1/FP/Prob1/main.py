from controller.service_sedinte import ServiceSedinte
from repo.repo_sedinte import Repo_sedinte
from domain.validator import Validator
from ui.ui_sedinte import Ui


def main():

    repo = Repo_sedinte("sedinte.txt")
    validator = Validator()
    service = ServiceSedinte(repo, validator)
    ui = Ui(service)
    ui.start()

main()