#include "masini.h"
#include <iostream>

/* Initializeaza toate campurile masinii folosind lista de initializare
   @param nrInmatriculare: cheia unica ; @param producator: producatorul
   @param model: modelul ; @param tip: tipul masinii
   @param inchiriata: statusul de inchiriere (default false)
   @return: - */
Masina::Masina(const std::string& nrInmatriculare, const std::string& producator,
    const std::string& model, const std::string& tip, bool inchiriata)
    : nrInmatriculare{ nrInmatriculare }, producator{ producator },
    model{ model }, tip{ tip }, inchiriata{ inchiriata } {
}

/* Copy constructor - afiseaza mesaj pentru a urmari cen opierile inutile din aplicatie
   @param other: masina din care se copiaza ; @return: - */
Masina::Masina(const Masina& other)
    : nrInmatriculare{ other.nrInmatriculare }, producator{ other.producator },
    model{ other.model }, tip{ other.tip }, inchiriata{ other.inchiriata } {
    std::cout << "Copie Masina " << "\n";
}

/* Move constructor - muta resursele fara copiere
   noexcept este obligatoriu pentru ca std::vector sa foloseasca move la realocare
   @param other: masina din care se muta resursele ; @return: - */
Masina::Masina(Masina&& other) noexcept
    : nrInmatriculare{ std::move(other.nrInmatriculare) },
    producator{ std::move(other.producator) },
    model{ std::move(other.model) },
    tip{ std::move(other.tip) },
    inchiriata{ other.inchiriata } {
}


/* Returneaza numarul de inmatriculare al masinii
   @param: - ; @return: referinta constanta la nrInmatriculare */
const std::string& Masina::getNrInmatriculare() const noexcept {
    return nrInmatriculare;
}

/* Returneaza producatorul masinii
   @param: - ; @return: referinta constanta la producator */
const std::string& Masina::getProducator() const noexcept {
    return producator;
}

/* Returneaza modelul masinii
   @param: - ; @return: referinta constanta la model */
const std::string& Masina::getModel() const noexcept {
    return model;
}

/* Returneaza tipul masinii
   @param: - ; @return: referinta constanta la tip */
const std::string& Masina::getTip() const noexcept {
    return tip;
}

/* Returneaza statusul de inchiriere
   @param: - ; @return: true daca masina e inchiriata, false altfel */
bool Masina::getInchiriata() const noexcept {
    return inchiriata;
}

/* Modifica producatorul masinii
   @param newProducator: noul producator ; @return: - */
void Masina::setProducator(const std::string& newProducator) {
    producator = newProducator;
}

/* Modifica modelul masinii
   @param newModel: noul model ; @return: - */
void Masina::setModel(const std::string& newModel) {
    model = newModel;
}

/* Modifica tipul masinii
   @param newTip: noul tip ; @return: - */
void Masina::setTip(const std::string& newTip) {
    tip = newTip;
}

/* Modifica statusul de inchiriere
   @param newInchiriata: noul status ; @return: - */
void Masina::setInchiriata(bool newInchiriata) noexcept {
    inchiriata = newInchiriata;
}

/* Construieste un string lizibil cu datele masinii
   Exemplu: "[CJ 01 ABC] | Producator: Dacia | Model: Logan | Tip: berlina | Status: disponibila"
   @param: - ; @return: string cu datele masinii */
std::string Masina::toString() const {
    return "[" + nrInmatriculare + "] | Producator: " + producator + " | Model: " + model
        + " | Tip: " + tip + " | Status: " + (inchiriata ? "inchiriata" : "disponibila");
}

/* Verifica daca doua masini sunt egale dupa nrInmatriculare
   @param other: masina cu care comparam ; @return: true daca nrInmatriculare este identic */
bool Masina::operator==(const Masina& other) const noexcept {
    return nrInmatriculare == other.nrInmatriculare;
}

/* Operatorul invers pentru !=
   @param other: masina cu care comparam ; @return: true daca nrInmatriculare difera */
bool Masina::operator!=(const Masina& other) const noexcept {
    return !(*this == other);
}