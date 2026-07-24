#pragma once
#include <string>

class Vehicul {
private:
    std::string nrInmatriculare;
    std::string marca;
    std::string tip;
    int varsta;

public:
    /*
    Constructor
    @param nrInmatriculare - numarul de inmatriculare al vehiculului
    @param marca - marca vehiculului
    @param tip - tip vehiculului
    @param varsta - varsta vehiculului
    */
    Vehicul(const std::string& nrInmatriculare, const std::string& marca, const std::string& tip, int varsta);

    const std::string& getNrInmatriculare() const noexcept;
    const std::string& getMarca() const noexcept;
    const std::string& getTip() const noexcept;
    int getVarsta() const noexcept;
};
