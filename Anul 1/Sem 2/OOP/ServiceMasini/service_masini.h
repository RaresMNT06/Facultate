#pragma once
#include "repo_masini.h"
#include <vector>
#include <string>

class Service {
private:
    Repository& repo;

public:
    /* Constructor
       @param repo: referinta la repository
       @return: - */
    explicit Service(Repository& repo) noexcept;

    /* Returneaza toate vehiculele
       @param: -
       @return: referinta la vector */
    const std::vector<Vehicul>& getAll() const noexcept;

    /* Filtreaza vehiculele dupa tip
       @param tip: tipul cautat
       @return: vector cu vehiculele filtrate */
    std::vector<Vehicul> filtreazaDupaTip(const std::string& tip) const;

    /* Sorteaza vehiculele dupa varsta
       @param: -
       @return: vector sortat crescator dupa varsta */
    std::vector<Vehicul> sorteazaDupaVarsta() const;
};
