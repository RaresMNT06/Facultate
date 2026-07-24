#pragma once
#include "vehicul.h"
#include <vector>
#include <string>

class Repository {
private:
    std::vector<Vehicul> masini;
    std::string fileName;

    /* Citeste vehiculele din fisier la pornire
       @param: - ; @return: - */
    void loadFromFile();

public:
    /* Constructor - citeste din fisier
       @param fileName: calea fisierului ; @return: - */
    explicit Repository(const std::string& fileName);

    /* Returneaza toate vehiculele
       @param: - ; @return: referinta constanta la vector */
    const std::vector<Vehicul>& getAll() const noexcept;

    /* Returneaza numarul de vehicule
       @param: - ; @return: numarul de vehicule */
    size_t size() const noexcept;
};
