from Repo.repo_teorii import Repoteorii
from Service.service_teorii import ServiceTeorii
from Ui.ui_teorii import UiTeorii

def main():

    repo = Repoteorii("teorii.txt")
    service = ServiceTeorii(repo)
    ui = UiTeorii(service)
    ui.run()

main()