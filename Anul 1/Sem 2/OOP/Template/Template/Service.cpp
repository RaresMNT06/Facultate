#include "Service.h"
#include <algorithm>

Service::Service(Repository& repo) noexcept : repo(repo) {}

const std::vector<Entitate>& Service::getAll() const noexcept {
    return repo.getAll();
}

// TODO: implementeaza metodele de filtrare/sortare
