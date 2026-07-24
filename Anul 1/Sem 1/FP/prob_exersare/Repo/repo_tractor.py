from Domain.domain_tractor import Tractor

class Repo_tractor:

    def __init__(self,filename):

        self.__filename = filename

    def getAll(self):
        tractoare= []
        with open(self.__filename, "r") as f:
            for line in f:
                line = line.strip()
                if line != "":
                    parts = line.split(",")

                    number = int(parts[0])
                    brand = parts[1]
                    color =parts[2]
                    consumption =float(parts[3])
                    volume = float(parts[4])
                    price = float(parts[5])
                    tractor = Tractor(number,brand,color,consumption,volume,price)
                    tractoare.append(tractor)

        return tractoare

    def removeByNumber(self, number):

        tractoare = self.getAll()
        for t in tractoare:
            if t.get_number()== number:
                tractoare.remove(t)
                break

        with open(self.__filename, "w") as f:
            for t in tractoare:
                f.write(f"{t.get_number()},{t.get_brand()},{t.get_color()},{t.get_consumption()},{t.get_volume()},{t.get_price()}\n")

