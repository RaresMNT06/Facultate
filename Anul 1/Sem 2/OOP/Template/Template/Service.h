#pragma once
#include "Repository.h"
#include <vector>
#include <string>

class Service {
private:
    Repository& repo;

public:
    /* Constructor
       @param repo: referinta la repository ; @return: - */
    explicit Service(Repository& repo) noexcept;

    /* Returneaza toate entitatile
       @param: - ; @return: referinta la vector */
    const std::vector<Entitate>& getAll() const noexcept;

    // TODO: adauga metode de filtrare/sortare
};
