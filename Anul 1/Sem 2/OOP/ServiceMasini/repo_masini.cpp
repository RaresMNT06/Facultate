#include "repo_masini.h"
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
        std::string nr, marca, tip, varstaStr;
        std::getline(ss, nr, ',');
        std::getline(ss, marca, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, varstaStr, ',');
        int varsta = std::stoi(varstaStr);
        masini.push_back(Vehicul(nr, marca, tip, varsta));
    }
}

const std::vector<Vehicul>& Repository::getAll() const noexcept {
    return masini;
}

size_t Repository::size() const noexcept {
    return masini.size();
}
