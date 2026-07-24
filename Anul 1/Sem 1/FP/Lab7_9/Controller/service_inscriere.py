from Domain.domain_inscriere import Participare
from Domain.domain_person import Person
from Domain.domain_eveniment import Eveniment
from Error.repository_error import Repo_error
from Error.service_error import Service_error

class ServiceInscriere:
    """
    Service pentru gestionarea înscrierilor persoanelor la evenimente.
    Menține două dicționare:
      - __pers_ev: pentru fiecare persoană -> lista de id-uri de evenimente
      - __ev_pers: pentru fiecare eveniment -> lista de id-uri de persoane
    """

    def __init__(self, repository_inscriere, repository_eveniment, repository_persoana):
        self.__repository_inscriere = repository_inscriere
        self.__repository_persoana =repository_persoana
        self.__repository_eveniment = repository_eveniment
        self.__pers_ev = {}
        self.__ev_pers ={}

    def add_inscriere(self, id_eveniment, id_persoana):
        """
        Înscrie o persoană la un eveniment.

        :param id_eveniment: ID-ul evenimentului
        :param id_persoana: ID-ul persoanei
        :raises Service_error: dacă persoana sau evenimentul nu există
        """
        try:
            self.__repository_eveniment.updateEveniment(Eveniment(id_eveniment, None, None,None))
        except Repo_error:
            raise Service_error("Evenimentul nu exista")
        try:
            self.__repository_persoana.updatePerson(Person(id_persoana, None, None))
        except Repo_error:
            raise Service_error("Persoana nu exista")

        inscriere = Participare(id_persoana, id_eveniment)
        self.__repository_inscriere.addinscriere(inscriere)

        if id_persoana not in self.__pers_ev:
            self.__pers_ev[id_persoana] = []
        self.__pers_ev[id_persoana].append(id_eveniment)

        if  id_eveniment not in self.__ev_pers:
            self.__ev_pers[id_eveniment] = []
        self.__ev_pers[id_eveniment].append(id_persoana)

    def read_list_inscriere(self):
        """
        Returnează lista tuturor înscrierilor.

        :return: listă de obiecte Participare
        """
        return self.__repository_inscriere.get_list()

    def raport_evenimente_persoana_ordonate(self, id_pers):

        """
        Returnează lista de evenimente la care participă o persoană,
        ordonate după descriere, apoi după dată.

        :param id_pers: ID-ul persoanei
        :return: listă de obiecte Eveniment ordonate
        :raises Service_error: dacă persoana nu există
        """
        try:
            self.__repository_persoana.updatePerson(Person(id_pers, None, None))
        except Repo_error:
            raise Service_error("Persoana nu exista!")


        lista_id_evenimente = self.__pers_ev[id_pers]

        lista_evenimente = []
        for id_ev in lista_id_evenimente:
            ev = self.__repository_eveniment.updateEveniment(Eveniment(id_ev, None, None, None))
            lista_evenimente.append(ev)
        lista_evenimente.sort(key=lambda x: (x.get_descriere(), x.get_data()))
        return lista_evenimente

    def raport_persoane_max_evenimente(self):
        """
        Returnează persoanele care participă la cele mai multe evenimente.

        :return: listă(Persoana, număr_evenimente)
        """
        maxim = 0
        for id_pers in self.__pers_ev:
            nr_ev = len(self.__pers_ev[id_pers])
            if nr_ev > maxim:
                maxim = nr_ev

        rez = []
        for id_pers in self.__pers_ev:
            nr_ev = len(self.__pers_ev[id_pers])
            if nr_ev == maxim:
                persoana = self.__repository_persoana.updatePerson(Person(id_pers, None, None))
                rez.append((persoana, nr_ev))
        return rez

    def raport_top_evenimente(self):

        """
        Returnează top 20% dintre evenimentele cu cei mai mulți participanți.

        :return: listă (Eveniment, număr_participanți)
        """
        lista_evenimente = []
        for id_ev, lista_pers in self.__ev_pers.items():
            nr_part = len(lista_pers)
            ev = self.__repository_eveniment.updateEveniment(Eveniment(id_ev, None, None, None))
            lista_evenimente.append((ev, nr_part))
        lista_evenimente.sort(key=lambda x:x[1], reverse=True)
        nr_total = len(lista_evenimente)
        nr_top = int(nr_total * 0.2)
        if nr_top < 1:
            nr_top = 1

        return lista_evenimente[:nr_top]


    """ LAB  9 """
    def raport_top_pers(self, top):
        """
        Returnează topul persoanelor după numărul de evenimente la care sunt înscrise.

        :param top: numărul de persoane din top
        :return: listă de tupluri (Persoană, număr_evenimente)
        """
        lista_persoane=[]
        for id_pers, lista_ev in self.__pers_ev.items():
            nr_ins = len(lista_ev)
            pers = self.__repository_persoana.updatePerson(Person(id_pers,None,None))
            lista_persoane.append((pers, nr_ins))
        lista_persoane.sort(key=lambda x:x[1], reverse=True)

        return lista_persoane[:top]

    def raport_top_ev(self,top):
        """
        Returnează topul evenimentelor după numărul de participanți.

        :param top: numărul de evenimente din top
        :return: listă de tupluri (Eveniment, număr_participanți)
        """
        lista_ev=[]
        for id_ev, lista_pers in self.__ev_pers.items():
            nr_pers = len(lista_pers)
            ev = self.__repository_eveniment.updateEveniment(Eveniment(id_ev, None , None,None))
            lista_ev.append((ev, nr_pers))
        lista_ev.sort(key=lambda x:x[1], reverse=True)
        return lista_ev[:top]

    def este_inscris(self, id_pers, id_ev):
        """
        Verifică dacă o persoană este înscrisă la un anumit eveniment.

        :param id_pers: ID-ul persoanei pentru care se verifică înscrierea.
        :param id_ev: ID-ul evenimentului pentru care se verifică înscrierea.
        :return: bool
            True dacă persoana este înscrisă la eveniment,
            False în caz contrar.
        """
        lista_ins = self.read_list_inscriere()
        for ins in lista_ins:
            if ins.get_id_person() == id_pers and ins.get_id_eveniment() == id_ev:
                return True
        return False

    def raport_top_persoane_evenimente(self, x):
        """
        Returnează lista persoanelor din topul persoanelor care sunt înscrise
        la evenimentele din topul evenimentelor.

        :param x: numărul de persoane și evenimente din top
        :return: listă de tupluri (id_persoană, id_eveniment)
        """

        top = []
        lista_top_pers = self.raport_top_pers(x)
        lista_top_ev = self.raport_top_ev(x)
        lista_ins = self.read_list_inscriere()
        for ev, nr_pers in lista_top_ev:
            id_ev = ev.get_id_ev()
            for pers, nr_ev in lista_top_pers:
                id_pers = pers.get_id() #<--------------------------------------------------------------------------------------------------------------------------------
                if self.este_inscris(id_pers,id_ev):
                    top.append((id_pers,id_ev))

        return top

    "LAB 9 RAMAS"