
class Tractor:

    def __init__(self,number,brand,color,consumption,volume,price):

        self.__number =number
        self.__brand = brand
        self.__color = color
        self.__consumption = consumption
        self.__volume = volume
        self.__price = price

    def get_number(self):
        return self.__number

    def get_brand(self):
        return self.__brand

    def get_color(self):
        return self.__color

    def get_consumption(self):
        return self.__consumption

    def get_volume(self):
        return self.__volume

    def get_price(self):
        return self.__price

    def __str__(self):
        return f"{self.__number},{self.__brand},{self.__color},{self.__consumption},{self.__volume},{self.__price}"

