#pragma once
#include <exception>
#include <string>

/* Clasa de baza pentru toate exceptiile aplicatiei
   Mosteneste din std::exception pentru compatibilitate cu STL
   Permite prinderea tuturor exceptiilor proprii cu un singur catch */
class MasinaException : public std::exception {
protected:
    std::string mesaj;  // mesajul de eroare stocat ca std::string

public:
    /* Constructor - primeste mesajul de eroare
       @param mesaj: descrierea erorii
       @return: - */
    explicit MasinaException(const std::string& mesaj) : mesaj{ mesaj } {}

    /* Returneaza mesajul de eroare ca C-string
       Suprascrie metoda virtuala din std::exception
       @param: -
       @return: pointer constant la mesajul de eroare */
    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

/* Exceptie aruncata la incercarea de a adauga o masina cu nrInmatriculare
   care exista deja in repository */
class MasinaDuplicataException : public MasinaException {
public:
    /* Constructor - construieste mesajul cu nrInmatriculare-ul duplicat
       @param nrInmatriculare: numarul care exista deja
       @return: - */
    explicit MasinaDuplicataException(const std::string& nrInmatriculare)
        : MasinaException{ "Exista deja o masina cu nr. inmatriculare: " + nrInmatriculare } {
    }
};

/* Exceptie aruncata cand se incearca accesarea unei masini care nu exista
   Folosita la stergere, modificare si cautare */
class MasinaInexistentaException : public MasinaException {
public:
    /* Constructor - construieste mesajul cu nrInmatriculare-ul cautat
       @param nrInmatriculare: numarul care nu a fost gasit
       @return: - */
    explicit MasinaInexistentaException(const std::string& nrInmatriculare)
        : MasinaException{ "Nu exista nicio masina cu nr. inmatriculare: " + nrInmatriculare } {
    }
};

/* Exceptie aruncata cand datele introduse de utilizator nu sunt valide
   Folosita pentru validari: camp gol, format incorect, etc. */
class ValidareException : public MasinaException {
public:
    /* Constructor - primeste mesajul specific de validare
       @param mesaj: descrierea exacta a erorii de validare
       @return: - */
    explicit ValidareException(const std::string& mesaj)
        : MasinaException{ "Eroare de validare: " + mesaj } {
    }
};