#include "service_masini.h"
#include <algorithm>

Service::Service(Repository& repo) noexcept : repo(repo) {}

const std::vector<Vehicul>& Service::getAll() const noexcept {
    return repo.getAll();
}

std::vector<Vehicul> Service::filtreazaDupaTip(const std::string& tip) const {
    std::vector<Vehicul> result;
    for (const auto& v : getAll())
        if (v.getTip() == tip)
            result.push_back(v);
    return result;
}

std::vector<Vehicul> Service::sorteazaDupaVarsta() const {
    std::vector<Vehicul> result = repo.getAll();
    std::sort(result.begin(), result.end(),
        [](const Vehicul& a, const Vehicul& b) {
            return a.getVarsta() < b.getVarsta();
        });
    return result;
}
