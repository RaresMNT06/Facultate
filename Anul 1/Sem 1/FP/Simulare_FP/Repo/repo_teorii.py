from Domain.teorii import Teorii

class Repoteorii:
    """
    Construim o lista cu toate teoriile din fisier
    """

    def __init__(self, filename):

        self.__filename = filename

    def get_all(self):

        teorii = []
        with open(self.__filename, "r") as f:
            for line in f:
                line = line.strip()
                if line != "":
                    parts = line.split(",")
                    id_t = int(parts[0])
                    titlu = parts[1]
                    tip = parts[2]
                    niv_cred= int(parts[3])
                    nr_dov= int(parts[4])
                    teorie = Teorii(id_t, titlu, tip,niv_cred, nr_dov)
                    teorii.append(teorie)

        return teorii








