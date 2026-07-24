#pragma once
#include <string>

class Entitate {
private:
    // TODO: adauga campurile aici
    std::string id;

public:
    /*
    Constructor
    @param id - identificatorul entitatii
    */
    Entitate(const std::string& id);

    // TODO: adauga getteri pentru fiecare camp
    const std::string& getId() const noexcept;
};
