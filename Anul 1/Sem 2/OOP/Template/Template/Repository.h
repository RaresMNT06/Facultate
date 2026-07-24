#pragma once
#include "Entitate.h"
#include <vector>
#include <string>

class Repository {
private:
    std::vector<Entitate> items;
    std::string fileName;

    /* Citeste datele din fisier
       @param: - ; @return: - */
    void loadFromFile();

public:
    /* Constructor - citeste din fisier
       @param fileName: calea fisierului ; @return: - */
    explicit Repository(const std::string& fileName);

    /* Returneaza toate entitatile
       @param: - ; @return: referinta constanta la vector */
    const std::vector<Entitate>& getAll() const noexcept;

    /* Returneaza numarul de entitati
       @param: - ; @return: numarul de entitati */
    size_t size() const noexcept;
};
