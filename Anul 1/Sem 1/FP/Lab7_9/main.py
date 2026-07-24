from Controller.service_inscriere import ServiceInscriere
from Controller.service_person import ServicePer
from Controller.service_eveniment import ServiceEv
from Repository.file_repo_person import FileRepositoryPer
from Repository.file_repo_eveniment import FileRepositoryEv
from Repository.file_repo_inscriere import FileRepositoryInscriere
from Ui.ui import UI




def main():


    repo_eveniment = FileRepositoryEv("evenimente.txt")
    repo_inscriere = FileRepositoryInscriere("inscrieri.txt")
    repo_person = FileRepositoryPer("persoane.txt")

    service_person = ServicePer(repo_person)
    service_eveniment = ServiceEv(repo_eveniment)
    service_inscriere = ServiceInscriere(repo_inscriere,repo_eveniment,repo_person)

    ui = UI(service_person, service_eveniment, service_inscriere)
    ui.run()

main()

