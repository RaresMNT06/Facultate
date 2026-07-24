from subprog import *

def test_adaugare_numar_capatul_lista():
    assert adaugare_numar_capatul_lista([2 + 3j, 2 + 5j], 8 + 9j) == [2 + 3j, 2 + 5j, 8 + 9j]
    assert adaugare_numar_capatul_lista([7 - 4j, 20 + 5j, 7 - 2j], 7 + 9j) == [7 - 4j, 20 + 5j, 7 - 2j, 7 + 9j]
    assert adaugare_numar_capatul_lista([79 + 5j, 4 - 8j, 50 - 32j, 8 - 3j], 27 - 2j) == [79 + 5j, 4 - 8j, 50 - 32j,
                                                                                          8 - 3j, 27 - 2j]

test_adaugare_numar_capatul_lista()


def test_adaugare_numar_pe_o_pozitie_in_lista():

    assert adaugare_numar_pe_o_pozitie_in_lista([2 + 3j, 2 + 5j], 8 + 9j, 0) == [8 + 9j, 2 + 3j, 2 + 5j]
    assert adaugare_numar_pe_o_pozitie_in_lista([7 - 4j, 20 + 5j, 7 - 2j], 7 + 9j, 3) == [7 - 4j, 20 + 5j, 7 - 2j,7 + 9j]
    assert adaugare_numar_pe_o_pozitie_in_lista([79 + 5j, 4 - 8j, 50 - 32j, 8 - 3j], 27 - 2j, 2) == [79 + 5j, 4 - 8j, 27 - 2j, 50 - 32j,8 - 3j]



test_adaugare_numar_pe_o_pozitie_in_lista()


def test_stergere_elem_poz():
    assert stergere_elem_poz([2 + 3j, 2 + 5j], 0) == [2 + 5j]
    assert stergere_elem_poz([7 - 4j, 20 + 5j, 7 - 2j], 2) == [7 - 4j, 20 + 5j]
    assert stergere_elem_poz([79 + 5j, 4 - 8j, 50 - 32j, 8 - 3j], 2) == [79 + 5j, 4 - 8j, 8 - 3j]


test_stergere_elem_poz()


def test_stergere_elem_interval_poz():
    assert stergere_elem_interval_poz([2 + 3j, 2 + 5j], 0, 1) == []
    assert stergere_elem_interval_poz([7 - 4j, 20 + 5j, 7 - 2j], 1, 2) == [7 - 4j]
    assert stergere_elem_interval_poz([79 + 5j, 4 - 8j, 50 - 32j, 8 - 3j], 0, 1) == [50 - 32j, 8 - 3j]
    assert stergere_elem_interval_poz([79 + 5j, 4 - 8j, 50 - 32j, 8 - 3j], 1, 2) == [79 + 5j, 8 - 3j]


test_stergere_elem_interval_poz()


def test_inlocurie_ap_unui_nr_cu_alt_nr():
    assert inlocurie_ap_unui_nr_cu_alt_nr([7 + 9j, 7 + 9j, 7 + 9j], 7 + 9j, 2 + 3j) == [2 + 3j, 2 + 3j, 2 + 3j]
    assert inlocurie_ap_unui_nr_cu_alt_nr([79 + 5j, 4 - 8j, 50 - 32j, 8 - 3j], 4 - 8j, 2 + 9j) == [79 + 5j, 2 + 9j,
                                                                                                   50 - 32j, 8 - 3j]
    assert inlocurie_ap_unui_nr_cu_alt_nr([79 + 5j, 50 - 32j, 50 - 32j, 8 - 3j], 50 - 32j, 10 - 3j) == [79 + 5j,
                                                                                                        10 - 3j,
                                                                                                        10 - 3j, 8 - 3j]


test_inlocurie_ap_unui_nr_cu_alt_nr()


def test_tiparire_partea_imaginara_interval():
    assert tiparire_partea_imaginara_interval([79 + 5j, 50 - 32j, 50 + 2j, 8 - 3j], 0, 3) == [5.0, -32.0, 2.0, -3.0]
    assert tiparire_partea_imaginara_interval([20 + 2j, 3 + 2j, 23 - 6j], 0, 1) == [2.0, 2.0]
    assert tiparire_partea_imaginara_interval([2 - 3j, 4 - 6j, 2 - 5j, 2 + 3j, 3 + 2j], 1, 3) == [-6.0, -5.0, 3.0]
    assert tiparire_partea_imaginara_interval([2 - 3j, 4 - 6j, 2 - 5j, 2 + 3j, 3 + 2j], 2, 5) == [-5.0, 3.0, 2.0]


test_tiparire_partea_imaginara_interval()


def test_tiparire_numere_care_au_modulul_maimic10():
    assert tiparire_numere_care_au_modulul_maimic10([6 + 8j, 2 - 3j, 20 + 3j, 4 - 3j]) == [2 - 3j, 4 - 3j]
    assert tiparire_numere_care_au_modulul_maimic10([8 + 6j, 8 + 10j, 20 + 2j]) == []
    assert tiparire_numere_care_au_modulul_maimic10([2 + 3j, 2 + 5j, 4 + 2j]) == [2 + 3j, 2 + 5j, 4 + 2j]


test_tiparire_numere_care_au_modulul_maimic10()


def test_tiparire_numere_care_au_modulul_egal10():
    assert tiparire_numere_care_au_modulul_egal10([2 + 3j, 2 + 5j, 4 + 2j]) == []
    assert tiparire_numere_care_au_modulul_egal10([6 + 8j, 2 - 3j, 20 + 3j, 4 - 3j]) == [6 + 8j]
    assert tiparire_numere_care_au_modulul_egal10([8 + 6j, 6 + 8j, 20 + 2j]) == [8 + 6j, 6 + 8j]


test_tiparire_numere_care_au_modulul_egal10()


def test_suma_nr_subsecv():
    assert suma_nr_subsecv([2 + 3j, 2 + 5j, 4 + 2j], 0, 2) == 8 + 10j
    assert suma_nr_subsecv([6 + 8j, 2 - 3j, 20 + 3j, 4 - 3j], 0, 2) == 28 + 8j
    assert suma_nr_subsecv([8 + 6j, 6 + 8j, 20 + 2j], 1, 2) == 26 + 10j


test_suma_nr_subsecv()


def test_prod_nr_subsecv():

    assert prod_nr_subsecv([1 + 2j, 3 + 4j, 2 - 1j], 0, 2) == 25j
    assert prod_nr_subsecv([5 + 0j, -3 + 0j, 2 + 0j, 2 + 3j], 0, 2) == -30 + 0j
    assert prod_nr_subsecv([1 - 2j, 3 + 5j, 8 + 6j, 6 + 8j, 20 + 2j], 2, 4) == -200 + 2000j


test_prod_nr_subsecv()


def test_tiparire_desc_part_imag():
    assert tiparire_desc_part_imag([1 + 2j, 3 + 4j, 2 - 1j]) == [3 + 4j, 1 + 2j, 2 - 1j]
    assert tiparire_desc_part_imag([5 + 2j, -3 + 7j, 2 + 0j, 2 + 3j]) == [-3 + 7j, 2 + 3j, 5 + 2j, 2 + 0j]
    assert tiparire_desc_part_imag([1 - 2j, 3 + 5j, 8 + 6j, 6 + 8j, 20 + 2j]) == [6 + 8j, 8 + 6j, 3 + 5j, 20 + 2j,
                                                                                  1 - 2j]


test_tiparire_desc_part_imag()


def test_filtrare_parte_real_prim():
    assert filtrare_parte_real_prim([2 + 3j, 17 + 5j, 4 + 2j]) == [4 + 2j]
    assert filtrare_parte_real_prim([6 + 8j, 7 - 3j, 20 + 3j, 4 - 3j]) == [6 + 8j, 20 + 3j, 4 - 3j]
    assert filtrare_parte_real_prim([8 + 6j, 6 + 8j, 20 + 2j]) == [8 + 6j, 6 + 8j, 20 + 2j]


test_filtrare_parte_real_prim()


def test_modul_mai_mic_x():
    assert modul_mai_mic_x([1 + 1j, 2 - 3j, 4 - 3j], 10) == []
    assert modul_mai_mic_x([6 + 8j, 1 - 3j, 20 + 3j, 2 - 3j], 5) == [6 + 8j, 20 + 3j]
    assert modul_mai_mic_x([8 + 6j, 6 + 8j, 20 + 2j], 3) == [8 + 6j, 6 + 8j, 20 + 2j]


test_modul_mai_mic_x()


def test_modul_egal_cu_x():

    assert modul_egal_cu_x([6 + 8j, 1 - 3j, 20 + 3j, 4 - 3j], 10) == [1 - 3j, 20 + 3j, 4 - 3j]
    assert modul_egal_cu_x([3 + 4j, 4 + 3j], 5) == []
    assert modul_egal_cu_x([2 - 2j, 4 - 5j, 3 - 4j], 7) == [2 - 2j, 4 - 5j, 3 - 4j]


test_modul_egal_cu_x()


def test_modul_mai_mare_x():

    assert modul_mai_mare_x([1 + 1j, 2 - 3j, 4 - 3j], 10) == [1 + 1j, 2 - 3j, 4 - 3j]
    assert modul_mai_mare_x([6 + 8j, 1 - 3j, 20 + 3j, 2 - 3j], 5) == [1 - 3j, 2 - 3j]
    assert modul_mai_mare_x([8 + 6j, 6 + 8j, 20 + 2j], 3) == []


test_modul_mai_mare_x()

def test_adaugare_lista_in_istoric():

    assert adaugare_lista_in_istoric([2, 4, 4], [[],[4,5]])== [[],[4,5],[2,4,4]]
    assert adaugare_lista_in_istoric([],[[6,7],[5,6,7]]) ==[[6,7],[5,6,7],[]]

test_adaugare_lista_in_istoric()

def test_undo_list():

    assert undo_list([[3,4],[5,6]]) == [3,4]
    assert undo_list([[3,4],[5,6,6,7], [4,8,7]]) == [5,6,6,7]

test_undo_list()