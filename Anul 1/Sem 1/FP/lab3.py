def citire_liste():
    """
    Transforma sirul din str in int

    """

    liste = input("Introduceti lista: ")
    sir = [int(x) for x in liste.split(" ")]
    return sir

def problema_4(liste):
    """
    Problema 4

    Cauta intr-un sir de elemente lungimea maxima a unei secvente cu numere prime

    :param liste: Lista de elemente unde cautam secventa
    :return: Lungimea maxima a secventiei
    """
    l=1; maxi=0
    for i in range (len(liste)-1):
        if eprim(liste[i])==True and eprim(liste[i+1])==True:
            l+=1
        elif maxi<l:
            maxi=l
            l=1
    if maxi<l:
        maxi=l
    return maxi


def problema_7(liste):

    """
    Problema 7

    Se cauta secventa de lungime maxima cu proprietatea ca oricare
    doua elemente consecutive difera printr-un numar prim.

    :param liste: Lista de elemente unde cautam secventa
    :return: Lungimea maxima a secventiei

    """
    l=1; maxi=0
    for i in range (len(liste)-1):
        if consec_dif_prim(liste[i], liste[i+1])==True:
            l+=1
        elif maxi < l:
            maxi = l
            l = 1
    if maxi < l:
        maxi = l
    return maxi

def problema_11(liste):
    """
    Problema 11

    Se cauta lungimea maxima a unei sevente cu proprietatea ca
    suma elementelor este maxima

    :param liste: Lista de elemente unde cautam secventa
    :return: Lungimea maxima a secventiei
    """
    maxi=0 ; sum=0 ; sum_max=0

    for i in range(len(liste)):
        suma_curenta=0
        for j in range(i, len(liste)):
            suma_curenta += liste[j]
            if suma_curenta > sum_max:
                sum_max = suma_curenta
                maxi = j - i + 1
    return maxi

def eprim(nr):
    """
    Aceasta funtctie retruneaza True daca un numar este prim si False in caz contrar

    :param nr: Introducem un numar
    :return: Retruneaza True/False

    """
    if nr<2:
        return False
    div = 2
    while div<nr and nr%div>0:
        div+=1
    return div>=nr

def consec_dif_prim(a, b):
    """
    Subprogram ul verifica daca doua numere difera printr un numar prim
    :param a, b: Doua numere intregi
    :return: Returneaza True/False
    """
    return eprim(abs(a-b))

def menu():
    print("1. Introduceti lista")
    print("4. Problema 4 - secventa de lungime maxima de numere prime")
    print("7. Problema 7 - secventa de lungime maxima; 2 numere difera printr-un numar prim")
    print("11. Problema 11 - secventa de lungime maxima cu proprietatea ca suma elementelor este maxima")
    print("0. Exit")

    """
    Acesta este meniul de intrare:
    1. Din acest meniu utilizatorul va putea sa introduca o lista.
    2. Acesta va putea alege problema pe care vrea sa o rezolve.
    3. Plus obtiunea de iesire.
    """

def run():
    menu()
    lista1=[]
    option = int(input("Alegeti optiunea:"))
    while option !=0:
        if option ==1:
            lista1 = citire_liste()
        elif option==4:
            rez = problema_4(lista1)
            print("Lungimea maxima este: ",rez)
        elif option ==7:
            rez = problema_7(lista1)
            print("Lungimea maxima este: ",rez)
        elif option ==11:
            rez = problema_11(lista1)
            print("Lungimea maxima este: ",rez)
        option = int(input("Alegeti optiunea:"))

run()
