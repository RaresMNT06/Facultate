from subprog import *
from menu import *

"""
Problema 1

Creati un program care lucreaza cu numere complexe (a+bi). Programul gestioneaza o lista de
numere complexe si perimite efectuarea repetata a urmatoarelor actiuni:

"""



def run():
    menu()
    lista = []
    lista_veche = []
    option = int(input("Alegeti optiunea de la MENIUL PRINCIPAL:"))
    while option != 0:
        if option == 1:
            lista = citire_lista_numere_complexe()
            print(lista)
            lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
        elif option == 2:
            menu_adaugare_nr_lista()
            option2 = int(input("Alegeti optiunea de la ADAUGARE NUMERE IN LISTA:"))
            while option2 != 0:
                if option2 == 1:
                    x = complex(input("Introduceti numarul:"))
                    lista = adaugare_numar_capatul_lista(lista, x)
                    print(lista)
                    lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                elif option2 == 2:
                    a = int(input("Introduceti pozitia:"))
                    x = complex(input("Introduceti numarul:"))
                    lista = adaugare_numar_pe_o_pozitie_in_lista(lista, x, a)
                    print(lista)
                    lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                option2 = int(input("Alegeti optiunea de la ADAUGARE NUMERE IN LISTA:"))
        elif option == 3:
            menu_modificare_elemente_lista()
            option3 = int(input("Alegeti optiunea de la MENIU CAUTARE NUMERE IN LISTA:"))
            while option3 != 0:
                if option3 == 1:
                    x = int(input("Introduceti pozitia:"))
                    lista = stergere_elem_poz(lista, x)
                    print(lista)
                    lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                elif option3 == 2:
                    x = int(input("Introduceti pozitia capatului din dreapta:"))
                    y = int(input("Introduceti pozitia capatului din stanga:"))
                    lista = stergere_elem_interval_poz(lista, x, y)
                    print(lista)
                    lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                elif option3 == 3:
                    x = complex(input("Introduceti numarul pe care sa il inlocuim: "))
                    y = complex(input("Introduceti numarul pe care sa il adaugam: "))
                    lista = inlocurie_ap_unui_nr_cu_alt_nr(lista, x, y)
                    print(lista)
                    lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                option3 = int(input("Alegeti optiunea de la MENIU CAUTARE NUMERE IN LISTA:"))
        elif option == 4:
            menu_cautare_numere()
            option4 = int(input("Alegeti optiunea de la MENIU CAUTARE NUMERE:"))
            while option4 != 0:
                if option4 == 1:
                    x = int(input("Introduceti pozitia capatului din dreapta:"))
                    y = int(input("Introduceti pozitia capatului din stanga:"))
                    print(tiparire_partea_imaginara_interval(lista, x, y))
                    print(lista)
                    lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                elif option4 == 2:
                    print(tiparire_numere_care_au_modulul_maimic10(lista))
                    print(lista)
                    lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                elif option4 == 3:
                    print(tiparire_numere_care_au_modulul_egal10(lista))
                    print(lista)
                    lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                option4 = int(input("Alegeti optiunea de la MENIU CAUTARE NUMERE:"))
        elif option == 5:
            menu_operatii_cu_nr_lista()
            option5 = int(input("Alegeti optiunea de la MENIU OPERATII CU NUMERELE DIN LISTA:"))
            while option5 != 0:
                if option5 == 1:
                    x = int(input("Introduceti pozitia capatului din dreapta:"))
                    y = int(input("Introduceti pozitia capatului din stanga:"))
                    print(suma_nr_subsecv(lista, x, y))
                    print(lista)
                    lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                elif option5 == 2:
                    x = int(input("Introduceti pozitia capatului din dreapta:"))
                    y = int(input("Introduceti pozitia capatului din stanga:"))
                    print(prod_nr_subsecv(lista, x, y))
                    print(lista)
                    lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                elif option5 == 3:
                    print(tiparire_desc_part_imag(lista))
                    print(lista)
                    lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                option5 = int(input("Alegeti optiunea de la MENIU OPERATII CU NUMERELE DIN LISTA:"))
        elif option == 6:
            menu_filtrare()
            option6 = int(input("Alegeti optiunea de la MENIU FILTRARE:"))
            while option6 != 0:
                if option6 == 1:
                    print(filtrare_parte_real_prim(lista))
                    print(lista)
                    lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                elif option6 == 2:
                    x = int(input("Alegeti un numar care vreti sa il comparati cu modulul numerelor:"))
                    option6_ = str(input("Alegeti dintre <, = sau >:"))
                    if option6_ == "<":
                        print(modul_mai_mic_x(lista, x))
                        lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                    elif option6_ == "=":
                        print(modul_egal_cu_x(lista, x))
                        lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                    elif option6_ == ">":
                        print(modul_mai_mare_x(lista, x))
                        lista_veche = adaugare_lista_in_istoric(lista, lista_veche)
                option6 = int(input("Alegeti optiunea de la MENIU FILTRARE:"))
        elif option == 7:
            lista = undo_list(lista_veche)
            print("Lista veche este:", lista)
        option = int(input("Alegeti optiunea de la MENIUL PRINCIPAL:"))

run()



def main():
    lista = []
    comand = input("Introduceti comanda: ").strip().lower()
    list_param = comand.split()
    while comand != "exit":
        list_param = comand.split()
        comand_execute = list_param[0]
        if comand_execute == "create_list":
            for i in range(1, len(list_param),2):
                real = int(list_param[i])
                imag = int(list_param[i + 1])
                number = complex(real, imag)
                lista = adaugare_numar_capatul_lista(lista, number)
            print(lista)
        elif comand_execute == "add_number_to_the_end_of_the_list":
            real = int(list_param[1])
            imag = int(list_param[2])
            number = complex(real, imag)
            lista = adaugare_numar_capatul_lista(lista, number)
            print(lista)
        elif comand_execute == "add_number_on_a_given_index":
            real = int(list_param[1])
            imag = int(list_param[2])
            number = complex(real, imag)
            index = int(list_param[3])
            lista= adaugare_numar_pe_o_pozitie_in_lista(lista, number, index)
            print(lista)
        elif comand_execute == "show_list":
            print(lista)
        comand = input("Introduceti comanda: ").strip().lower()













