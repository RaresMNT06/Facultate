#include "Masina.h"
#include <iostream>
/* Initializeaza toate campurile masinii folosind lista de initializare
   @param nrInmatriculare: cheia unica ; @param producator: producatorul
   @param model: modelul ; @param tip: tipul masinii */
Masina::Masina(const std::string& nrInmatriculare, const std::string& producator,
    const std::string& model, const std::string& tip)
    : nrInmatriculare{ nrInmatriculare }, producator{ producator },
    model{ model }, tip{ tip } {
}

Masina::Masina(const Masina& other)
    : nrInmatriculare{ other.nrInmatriculare }, producator{ other.producator },
    model{ other.model }, tip{ other.tip } {
    std::cout << "Copie Masina " << "\n";
}

Masina::Masina(Masina&& other) noexcept
    : nrInmatriculare{ std::move(other.nrInmatriculare) },
    producator{ std::move(other.producator) },
    model{ std::move(other.model) },
    tip{ std::move(other.tip) } {
}

/* Returneaza numarul de inmatriculare al masinii
   @param: - ; @return: referinta constanta la nrInmatriculare */
const std::string& Masina::getNrInmatriculare() const noexcept { return nrInmatriculare; }

/* Returneaza producatorul masinii
   @param: - ; @return: referinta constanta la producator */
const std::string& Masina::getProducator() const noexcept { return producator; }

/* Returneaza modelul masinii
   @param: - ; @return: referinta constanta la model */
const std::string& Masina::getModel() const noexcept { return model; }

/* Returneaza tipul masinii
   @param: - ; @return: referinta constanta la tip */
const std::string& Masina::getTip() const noexcept { return tip; }

/* Modifica producatorul masinii
   @param producator: noul producator ; @return: - */
void Masina::setProducator(const std::string& newProducator) { producator = newProducator; }

/* Modifica modelul masinii
   @param model: noul model ; @return: - */
void Masina::setModel(const std::string& newModel) { model = newModel; }

/* Modifica tipul masinii
   @param tip: noul tip ; @return: - */
void Masina::setTip(const std::string& newTip) { tip = newTip; }

/* Construieste un string lizibil cu datele masinii
   Exemplu: "[CJ 01 ABC] | Producator: Dacia | Model: Logan | Categorie: berlina"
   @param: - ; @return: string cu datele masinii */
std::string Masina::toString() const {
    return "[" + nrInmatriculare + "] | Producator: " + producator + " | Model: " + model + " | Tip: " + tip;
}

/* Verifica daca doua masini sunt egale dupa nrInmatriculare
   @param other: masina cu care comparam ; @return: true daca nrInmatriculare este identic */
bool Masina::operator==(const Masina& other) const noexcept {
    return nrInmatriculare == other.nrInmatriculare;
}