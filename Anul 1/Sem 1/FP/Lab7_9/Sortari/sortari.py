""" Lab 12 """
class Sorts:

    @staticmethod
    def gnome_sort(lista, key=lambda x: x, reverse=False, cmp=lambda x, y: x >= y):
        """
        Gnome Sort - nediscutata la curs
        Complexitate: O(n^2)
        """
        i = 0
        while i < len(lista):
            if i == 0 or cmp(key(lista[i]), key(lista[i - 1])):
                i += 1
            else:

                lista[i], lista[i - 1] = lista[i - 1], lista[i]
                i -= 1

        if reverse:
            lista.reverse()

        return lista

    @staticmethod
    def quick_sort(lista, key=lambda x: x, reverse=False, cmp=lambda x, y: x<=y):
        """
        Quick Sort - recursiv
        Complexitate medie: O(n log n)
        Worst case: O(n^2)
        """
        if len(lista) <= 1:
            return lista

        pivot = lista[0]
        stanga = []
        dreapta = []

        for elem in lista[1:]:
            if cmp(key(elem),key(pivot)):
                stanga.append(elem)
            else:
                dreapta.append(elem)

        rezultat = (Sorts.quick_sort(stanga, key, reverse, cmp)+ [pivot]+ Sorts.quick_sort(dreapta, key, reverse,cmp))

        if reverse:
            rezultat.reverse()

        return rezultat