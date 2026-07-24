#include "Repository.h"
#include <fstream>
#include <sstream>

Repository::Repository(const std::string& fileName) : fileName(fileName) {
    loadFromFile();
}

void Repository::loadFromFile() {
    std::ifstream f(fileName);
    std::string line;
    while (std::getline(f, line)) {
        std::stringstream ss(line);
        std::string id;
        // TODO: adauga celelalte campuri
        std::getline(ss, id, ',');
        items.push_back(Entitate(id));
    }
}

const std::vector<Entitate>& Repository::getAll() const noexcept {
    return items;
}

size_t Repository::size() const noexcept {
    return items.size();
}
