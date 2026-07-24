class DomainMelodii:

    def __init__(self, titlu, artist, gen, data):
        self.__title = titlu
        self.__artist = artist
        self.__gen = gen
        self.__data = data

    def get_title(self):
        return self.__title
    def get_artist(self):
        return self.__artist
    def get_gen(self):
        return self.__gen
    def get_data(self):
        return self.__data

    def set_title(self, titlu):
        self.__title = titlu
    def set_artist(self, artist):
        self.__artist = artist
    def set_gen(self, gen):
        self.__gen = gen
    def set_data(self, data):
        self.__data = data

