from repo.repo_melodie import RepoMelodie
from domain.validator_melodie import ValidatorMelodie
from controller.service_melodii import ServiceMelodii
from ui.Ui import  Ui

def main():

    repo = RepoMelodie("melodie.txt")
    validate = ValidatorMelodie()
    service = ServiceMelodii(repo, validate)
    ui = Ui(service)
    ui.start()


main()