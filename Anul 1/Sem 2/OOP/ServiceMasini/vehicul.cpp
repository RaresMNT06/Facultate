#include "vehicul.h"

Vehicul::Vehicul(const std::string& nrInmatriculare, const std::string& marca, const std::string& tip, int varsta)
    : nrInmatriculare(nrInmatriculare), marca(marca), tip(tip), varsta(varsta) {
}

const std::string& Vehicul::getNrInmatriculare() const noexcept {
    return nrInmatriculare;
}

const std::string& Vehicul::getMarca() const noexcept {
    return marca;
}

const std::string& Vehicul::getTip() const noexcept {
    return tip;
}

int Vehicul::getVarsta() const noexcept {
    return varsta;
}
