from repo.repo_exception import RepoException


class Ui:
    def __init__(self, service):
        self.__service = service



    def update_melodies(self):


        titlu = input("Scrie un titlu: ")
        artistu = input("Scrie un artistu: ")

        try:
            music = self.__service.update_melod(titlu, artistu)
        except RepoException as e:
            print(e)
            return

        gen_nou = input("Scrie un nou gen(Rock,Pop,Jazz): ")
        music.set_gen(gen_nou)
        data_noua = input("Scrie o noua data(dd.mm.yyyy):")
        music.set_data(data_noua)

        self.__service.save_melodie(music)


    def start(self):

        option = input("Scrie option: ")
        while True:
            if option == "1":
                self.update_melodies()
            if option == "0":
                break
            option = input("Scrie option: ")