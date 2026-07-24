#include "Entitate.h"

Entitate::Entitate(const std::string& id) : id(id) {}

const std::string& Entitate::getId() const noexcept {
    return id;
}
