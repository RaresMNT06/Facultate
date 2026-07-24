#pragma once
#include <stdexcept>
#include <utility>

/* Clasa template MyList implementeaza un vector dinamic
   @param T: tipul elementelor din lista */
template <typename T>
class MyList {
private:
    T* date;
    size_t lungime;
    size_t capacitate;

    /* Dubleaza capacitatea cand lista e plina
       @param: - ; @return: - */
    void resize() {
        capacitate *= 2;
        T* memoriaNova = static_cast<T*>(::operator new(capacitate * sizeof(T)));
        for (size_t i = 0; i < lungime; i++) {
            new (&memoriaNova[i]) T(std::move(date[i]));
            date[i].~T();
        }
        ::operator delete(date);
        date = memoriaNova;
    }

public:

    /*--------------ITERATOR-------------------*/
    /* Clasa Iterator pentru parcurgerea listei
       Permite folosirea MyList in bucle for-range
       @param T: tipul elementelor din lista */
    class Iterator {
    private:
        T* elementCurent;

    public:
        /* Constructor - initializeaza iteratorul cu un pointer la element
           @param ptr: pointerul la elementul curent ; @return: - */
        Iterator(T* ptr) noexcept : elementCurent{ ptr } {}

        /* Dereferentiaza iteratorul - returneaza elementul curent
           @param: - ; @return: referinta la elementul curent */
        T& operator*() noexcept {
            return *elementCurent;
        }

        /* Dereferentiaza iteratorul - versiunea const
           @param: - ; @return: referinta constanta la elementul curent */
        const T& operator*() const noexcept {
            return *elementCurent;
        }

        /* Avanseaza iteratorul la urmatorul element (prefix)
           @param: - ; @return: referinta la iteratorul avansat */
        Iterator& operator++() noexcept {
            ++elementCurent;
            return *this;
        }

        /* Verifica daca doi iteratori sunt diferiti
           @param altIterator: iteratorul cu care comparam ; @return: true daca sunt diferiti */
        bool operator!=(const Iterator& altIterator) const noexcept {
            return elementCurent != altIterator.elementCurent;
        }

        /* Verifica daca doi iteratori sunt egali
           @param altIterator: iteratorul cu care comparam ; @return: true daca sunt egali */
        bool operator==(const Iterator& altIterator) const noexcept {
            return elementCurent == altIterator.elementCurent;
        }
    };

    /* Constructor - initializeaza lista cu capacitate initiala 2
       @param: - ; @return: - */
    MyList()
        : date{ static_cast<T*>(::operator new(2 * sizeof(T))) },
        lungime{ 0 },
        capacitate{ 2 } {
    }

    /* Copy constructor - copiaza toate elementele din alta lista
       @param listaOriginala: lista de copiat ; @return: - */
    MyList(const MyList& listaOriginala)
        : date{ static_cast<T*>(::operator new(listaOriginala.capacitate * sizeof(T))) },
        lungime{ listaOriginala.lungime },
        capacitate{ listaOriginala.capacitate } {
        for (size_t i = 0; i < lungime; i++)
            new (&date[i]) T(listaOriginala.date[i]);
    }

    /* Move constructor - muta datele din alta lista fara copiere
       @param listaDeMutat: lista de mutat ; @return: - */
    MyList(MyList&& listaDeMutat) noexcept
        : date{ listaDeMutat.date },
        lungime{ listaDeMutat.lungime },
        capacitate{ listaDeMutat.capacitate } {
        listaDeMutat.date = nullptr;
        listaDeMutat.lungime = 0;
        listaDeMutat.capacitate = 0;
    }

    /* Operator de atribuire prin copiere
       @param listaOriginala: lista de copiat ; @return: referinta la lista curenta */
    MyList& operator=(const MyList& listaOriginala) {
        if (this != &listaOriginala) {
            for (size_t i = 0; i < lungime; i++)
                date[i].~T();
            ::operator delete(date);
            capacitate = listaOriginala.capacitate;
            lungime = listaOriginala.lungime;
            date = static_cast<T*>(::operator new(capacitate * sizeof(T)));
            for (size_t i = 0; i < lungime; i++)
                new (&date[i]) T(listaOriginala.date[i]);
        }
        return *this;
    }

    /* Operator de atribuire prin mutare
       @param listaDeMutat: lista de mutat ; @return: referinta la lista curenta */
    MyList& operator=(MyList&& listaDeMutat) noexcept {
        if (this != &listaDeMutat) {
            for (size_t i = 0; i < lungime; i++)
                date[i].~T();
            ::operator delete(date);
            date = listaDeMutat.date;
            lungime = listaDeMutat.lungime;
            capacitate = listaDeMutat.capacitate;
            listaDeMutat.date = nullptr;
            listaDeMutat.lungime = 0;
            listaDeMutat.capacitate = 0;
        }
        return *this;
    }

    /* Destructor - apeleaza destructorul pentru fiecare element si elibereaza memoria
       @param: - ; @return: - */
    ~MyList() {
        for (size_t i = 0; i < lungime; i++)
            date[i].~T();
        ::operator delete(date);
    }

    /* Adauga un element la sfarsitul listei
       @param elementNou: elementul de adaugat ; @return: - */
    void add(const T& elementNou) {
        if (lungime == capacitate)
            resize();
        new (&date[lungime++]) T(elementNou);
    }

    /* Sterge elementul de la pozitia index
       @param pozitie: pozitia de sters ; @return: - */
    void remove(size_t pozitie) {
        if (pozitie >= lungime)
            throw std::out_of_range("Index invalid!");
        date[pozitie].~T();
        for (size_t i = pozitie; i < lungime - 1; i++) {
            new (&date[i]) T(std::move(date[i + 1]));
            date[i + 1].~T();
        }
        lungime--;
    }

    /* Returneaza elementul de la pozitia index
       @param pozitie: pozitia dorita ; @return: referinta la element */
    T& at(size_t pozitie) {
        if (pozitie >= lungime)
            throw std::out_of_range("Index invalid!");
        return date[pozitie];
    }

    /* Returneaza elementul de la pozitia index - versiunea const
       @param pozitie: pozitia dorita ; @return: referinta constanta la element */
    const T& at(size_t pozitie) const {
        if (pozitie >= lungime)
            throw std::out_of_range("Index invalid!");
        return date[pozitie];
    }

    /* Returneaza elementul de la pozitia index - alias pentru at()
   @param pozitie: pozitia dorita ; @return: referinta la element */
    T& get(size_t pozitie) {
        if (pozitie >= lungime)
            throw std::out_of_range("Index invalid!");
        return date[pozitie];
    }

    /* Returneaza elementul de la pozitia index - versiunea const
       @param pozitie: pozitia dorita ; @return: referinta constanta la element */
    const T& get(size_t pozitie) const {
        if (pozitie >= lungime)
            throw std::out_of_range("Index invalid!");
        return date[pozitie];
    }

    /* Returneaza numarul de elemente din lista
       @param: - ; @return: numarul de elemente */
    size_t size() const noexcept {
        return lungime;
    }

    /* Verifica daca lista e goala
       @param: - ; @return: true daca e goala */
    bool empty() const noexcept {
        return lungime == 0;
    }

    /* Returneaza iteratorul la primul element
       @param: - ; @return: iterator la primul element */
    Iterator begin() noexcept {
        return Iterator(date);
    }

    /* Returneaza iteratorul dupa ultimul element
       @param: - ; @return: iterator dupa ultimul element */
    Iterator end() noexcept {
        return Iterator(date + lungime);
    }

    /* Returneaza iteratorul const la primul element
       @param: - ; @return: iterator const la primul element */
    const Iterator begin() const noexcept {
        return Iterator(date);
    }

    /* Returneaza iteratorul const dupa ultimul element
       @param: - ; @return: iterator const dupa ultimul element */
    const Iterator end() const noexcept {
        return Iterator(date + lungime);
    }
};