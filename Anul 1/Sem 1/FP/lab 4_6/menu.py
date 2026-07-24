def menu():
    """
    Meniu principal
    """

    print("------ MENIU PRINCIPAL------")
    print("Alegeti obtiunea:")
    print("1. Introduceti lista de numere complexe")
    print("2. Adauga numar in lista")
    print("3. Modifica elemente din lista")
    print("4. Cautare numere")
    print("5. Operatii cu numerele din lista")
    print("6. Filtrare")
    print("7. Undo")
    print("0. Exit")


def menu_adaugare_nr_lista():
    print("------ MENIU ADAUGARE NUMERE IN LISTA ------")
    print("1. Adaugare numar complex la sfarsitul listei")
    print("2. Inserare numar complex pe o pozitie data")
    print("0. Revenire la MENIUL PRINCIPAL")


def menu_modificare_elemente_lista():
    print("------ MENIU MODIFICARE NUMERE DIN LISTA------")
    print("1. Sterge element de pe o pozitie data")
    print("2. Sterge elemente de pe un interval de pozitii")
    print("3. Inlocuieste toate aparitiile unui numar complex cu un alt numar complex")
    print("0. Revenire la MENIUL PRINCIPAL")


def menu_cautare_numere():
    print("------ MENIU CAUTARE NUMERE ------")
    print("1. Tipareste partea imaginara pentru numerele din lista.Se da intervalul de pozitii")
    print("2. Tipareste toate numerele complexe care au modulul mai mic decat 10")
    print("3. Tipareste toate numerele complexe care au modul egal cu 10")
    print("0. Revenire la MENIUL PRINCIPAL")


def menu_operatii_cu_nr_lista():
    print("------ MENIU OPERATII CU NUMERELE DIN LISTA ------")
    print("1. Suma numerelor dintr-o subsecventa data")
    print("2. Produsul numerele dintr-o subseventa data")
    print("3. Tipareste lista sprtata descrescator dupa partea imaginara")
    print("0. Revenire la MENIUL PRINCIPAL")


def menu_filtrare():
    print("------ MENIU FILTRARE ------")
    print("1. Filtrare parte reala prim - elimina din lista numerele complexe la care paretea reala este prim")
    print("2. Filtrare modulul - elimina din lista numerele complexe la care modulul este <,= sau > decat un numar dat")
    print("0. Revenire la MENIUL PRINCIPAL")