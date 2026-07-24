def creeaza_baller(id_baller, nume, valoare):
    '''

    :param id_baller: intreg, >=0
    :param nume: string, nevid
    :param valoare: float, >=0
    :return: un baller
    '''
    pass

def get_id_baller(baller):
    '''
    functie care returneaza idul intreg al ballerului
    :param baller:
    :return:
    '''

def test_creeaza_baller():
    id_baller =23
    nume = "Jordan"
    valoare = 9000.1
    baller = creeaza_baller(id_baller, nume, valoare)
    assert(id_baller == get_id_baller(baller))
