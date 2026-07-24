from domain.validator_automobile import ValidateAuto
from controller.service_automoblie import ServiceAutomobile
from repo.repo_automobile import RepoAutomobile
from ui.ui import UI


def main():

    repo = RepoAutomobile("automobile.txt")
    validator = ValidateAuto()
    service = ServiceAutomobile(validator, repo)
    ui = UI(service)
    ui.start()

main()
