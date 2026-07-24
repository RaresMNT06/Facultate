from class_fnct import *

def citire_lista_numere_complexe():
    """
    Citire lista de numere complexe

    :return: Lista de numere complexe
    """

    liste = input("Introduceti lista: ")
    sir = [complex(x) for x in liste.split()]
    return sir


def adaugare_numar_capatul_lista(liste, x):
    """
    Adaugare numar complex la capatul listei

    :param liste: Lista de numere complexe
    :param x: Numar complex
    :return: Lista de numere complexe cu numarul introdus la capatul listei
    """

    liste.append(x)
    return liste


def adaugare_numar_pe_o_pozitie_in_lista(liste, x, a):
    """
    Adaugare numar complex pe o pozitie anume in lista

    :param liste: Lista de numere complexe
    :param x: Numar complex
    :param a: Pozitie anume
    :return: Lista de numere complexe cu numarul introdus pe o pozitie anume
    """

    liste.insert(a, x)
    return liste


def stergere_elem_poz(liste, x):
    """
    Stergem un element de pe o anumita pozitie

    :param liste: Lista de numere complexe
    :param x: Pozitia elementului pe care vrem sa il stergem
    :return: Lista de numere complexe fara elementul de pe pozitia aleasa
    """

    liste.pop(x)
    return liste


def stergere_elem_interval_poz(liste, x, y):
    """
    Sterge elementele de pe un interval de pozitii

    :param liste: Lista de numere complexe
    :param x: Pozitia din stanga
    :param y: Pozitia din dreapta
    :return: Lista de numere complexe fara numerele din intervalul dat
    """

    del liste[x:y + 1]
    return liste


def inlocurie_ap_unui_nr_cu_alt_nr(liste, x, y):
    """
    Inlocuieste toate aparitiile unui numar complex cu un alt numar complex

    :param liste: Lista de numere complexe
    :param x: Numarul pe care trebuie sa il inlocuim
    :param y: Numarul care trebuie adaugat in locul lui x
    :return: Lista de numere complexe cu numarul inlocuit
    """
    for i in range(len(liste)):
        if liste[i] == x:
            liste[i] = y
    return liste


def tiparire_partea_imaginara_interval(liste, x, y):
    """
    Tipareste partea imaginara pentru numerele din lista. Se da un interval anume

    :param liste: Lista de numere complexe
    :param x: Capatul stang
    :param y: Capatul drept
    :return: Lista cu partea imaginara
    """

    imag = [get_imag(i) for i in liste[x:y + 1]]
    return imag


def tiparire_numere_care_au_modulul_maimic10(liste):
    """
    Tipareste toate numerele complexe care au modulul mai mic decat 10

    :param liste: Lista de numere complexe
    :return: Numerele cu modul mai mic decat 10
    """
    sir = []
    for i in range(len(liste)):
        if get_mod(liste[i]) < 10:
            sir.append(liste[i])
    return sir


def tiparire_numere_care_au_modulul_egal10(liste):
    """
    Tipareste toate numerele complexe care au modul egal cu 10

    :param liste: Lista de numere complexe
    :return: Numerele cu modul egal cu 10
    """
    sir = []
    for i in range(len(liste)):
        if get_mod(liste[i]) == 10:
            sir.append(liste[i])
    return sir


def suma_nr_subsecv(liste, x, y):
    """
    Suma numerelor complexe dintr-o subsecventa data

    :param liste: Lista de numere complexe
    :param x: Capatul stang
    :param y: Capatul drept
    :return: Suma numerelor din subsecventa data
    """
    suma = 0
    suma = sum(liste[x:y + 1])
    return suma


def prod_nr_subsecv(liste, x, y):
    """
    Produsul numerelor complexe dintr-o subsecventa data

    :param liste: Lista de numere complexe
    :param x: Capatul stang
    :param y: Capatul drept
    :return: Produsul numerelor din subsecventa data
    """
    prod = 1 + 0j
    for a in liste[x:y + 1]:
        prod *= a
    return prod


def tiparire_desc_part_imag(liste):
    """
    Returneaza o lista cu numerele complexe ordonate descrescator

    :param liste: Lista de numere complexe
    :return: Returneaza lista de numere complexe ordonata descrescator dupa partea imaginara
    """
    desc = []
    desc = sorted(liste, key=lambda x: get_imag(x), reverse=True)
    return desc


def eprim(nr):
    """
    Aceasta funtctie retruneaza True daca un numar este prim si False in caz contrar

    :param nr: Introducem un numar
    :return: Retruneaza True/False

    """
    if nr < 2:
        return False
    div = 2
    while div < nr and nr % div > 0:
        div += 1
    return div >= nr


def filtrare_parte_real_prim(liste):
    """
    Elimina numerele care au partea reala un numar prim

    :param liste:Lista de numere complexe
    :return:Lista de numere complexe care nu au partea reala numar prim
    """
    nr_prime = []
    for i in range(len(liste)):
        nr = liste[i]
        if eprim(get_real(nr)) == False:
            nr_prime.append(liste[i])
    return nr_prime


def modul_mai_mic_x(liste, x):
    """
    Elimină numerele din listă care au modulul mai mic decât x.

    :param liste: Lista de numere complexe
    :param x: Numarul care il comparam
    :return: Lista de numere complexe fara cele care au modulul mai mic ca x
    """

    return [nr for nr in liste if get_mod(nr) >= x]


def modul_egal_cu_x(liste, x):
    """
    Elimină numerele din listă care au modulul egal cu x.

    :param liste: Lista de numere complexe
    :param x: Numarul care il comparam
    :return: Lista de numere complexe fara cele care au modulul mai mic ca x
    """

    return [nr for nr in liste if get_mod(nr) != x]


def modul_mai_mare_x(liste, x):
    """
    Elimină numerele din listă care au modulul mai mare decât x.

    :param liste: Lista de numere complexe
    :param x: Numarul care il comparam
    :return: Lista de numere complexe fara cele care au modulul mai mic ca x
    """

    return [nr for nr in liste if get_mod(nr) <= x]

def undo_list(lista_veche):
    """
    Functia undo care verifica
    :param lista_veche: Lista cu modificarile anterioare
    :return: Lista veche
    """
    if len(lista_veche) > 0:
        lista_veche.pop()
        return lista_veche[-1]
    else:
        print("Nu există nicio stare anterioară!")
        return []


def adaugare_lista_in_istoric(lista, list_history):
    """
    Adaugam intr o lista tot ceea ce lucram astfel creeand un istoril
    :param lista: Lista de numere complexe
    :param list_history: Istoricul
    :return: Istoricul
    """
    list_history.append(lista[:])
    return list_history