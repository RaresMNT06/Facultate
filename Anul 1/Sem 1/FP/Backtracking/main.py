def backtracking_recursiv(monede, suma_ramasa, start_index, solutie_curenta):
    global nr_solutii

    if suma_ramasa == 0:
        print("Soluție:", solutie_curenta)
        nr_solutii += 1
        return

    for i in range(start_index, len(monede)):
        if monede[i] <= suma_ramasa:
            backtracking_recursiv(monede, suma_ramasa - monede[i], i , solutie_curenta + [monede[i]])



nr_solutii = 0


def backtracking_iterativ(monede, suma_totala):
    global nr_solutii
    stiva = [(suma_totala, 0, [])]
    monede.sort()

    while stiva:
        rest, idx, cale = stiva.pop()

        if rest == 0:
            print("Soluție:", cale)
            nr_solutii += 1
            continue


        for i in range(idx, len(monede)):
            moneda_curenta = monede[i]


            if moneda_curenta <= rest:
                stiva.append((rest - moneda_curenta, i, cale + [moneda_curenta]))

    return nr_solutii





def main():


    monede = list(map(int, input("Introdu monedele: ").split()))
    s = int(input("Introdu suma dorită: "))
    monede.sort()


    global nr_solutii
    nr_solutii = 0
    option = int(input("Introduceti 1 pt rec si 2 pt ite: "))
    if option == 1:
        backtracking_recursiv(monede, s, 0, [])
    if option == 2:
        backtracking_iterativ(monede, s)


    if nr_solutii == 0:
        print(f"Suma {s} nu poate fi plătită cu monedele date.")
    else:
        print(f"Total moduri găsite: {nr_solutii}")

main()
"""


M = {m1,m2, ... ,mn}   (Multimea de valori)
X = {0, ... , s/mi}    (Multimea nr monede)      
MxX -- > S

S={i C N| m1x1+ ....+mixi = s} (Multimea de solutii)


"""