class TractorUI:


    def __init__(self, service):
        self.__service = service

    # 1) Afișăm LISTA de obiecte Tractor
    def __ui_search_by_consumption(self):
        try:
            max_cons = float(input("Introdu consumul maxim: "))
        except:
            print("Valoare invalidă.")
            return

        tractors = self.__service.search_by_consumption(max_cons)

        if len(tractors) == 0:
            print("Nu s-au găsit tractoare cu consumul dorit.")
        else:
            print("Tractoare găsite:")
            for t in tractors:
                print(t)




    # 2) Afișăm un obiect TractorRental
    def __ui_rent_tractor(self):
        try:
            km = float(input("Introdu numărul de kilometri ai terenului: "))
            zile = int(input("Număr de zile de închiriere: "))
        except:
            print("Valori invalide!")
            return

        rental = self.__service.rent_tractor(km, zile)

        if rental is None:
            print("Nu există tractor potrivit pentru închiriere.")
        else:
            print("Tractor închiriat cu succes:")
            print(rental)





    def run(self):

        while True:
            print("=== MENIU TRACTOARE ===")
            print("1. Caută tractoare după consum")
            print("2. Închiriază un tractor")
            print("0. Ieșire")

            opt = input("Alege opțiunea: ")

            if opt == "1":
                  self.__ui_search_by_consumption()
            elif opt == "2":
                    self.__ui_rent_tractor()
            elif opt == "0":
                break
            else:
                print("Opțiune invalidă! Reîncearcă.")