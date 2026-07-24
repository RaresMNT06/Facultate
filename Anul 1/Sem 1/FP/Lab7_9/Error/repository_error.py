class Repo_error(Exception):

    def __init__(self, messege):
        self.__messege=messege

    def get_messege(self):
        return self.__messege