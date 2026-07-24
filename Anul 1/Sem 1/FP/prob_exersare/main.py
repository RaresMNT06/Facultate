from Repo.repo_tractor import Repo_tractor
from Service.tractor_service import TractorService
from Ui.Ui_tractoare import TractorUI

def main():
    repo = Repo_tractor("tractoare.txt")
    service = TractorService(repo)
    ui = TractorUI(service)
    ui.run()


main()