class TractorRental:

    def __init__(self,tractor,total_price):

        self.__tractor = tractor
        self.__total_price = total_price

    def get_tractor(self):
        return self.__tractor

    def get_tractor_price(self):
        return self.__total_price

    def __str__(self):
        return (f"Inchiriere Tractor #{self.__tractor.get_number()} | "
            f"Brand: {self.__tractor.get_brand()} | "
            f"Consum: {self.__tractor.get_consumption()} | "
            f"Pret total: {self.__total_price} lei"
        )