#pragma once
#include <string>

/* Clasa DTO (Data Transfer Object) pentru raportul de analiza
   Foloseste un dictionar (std::map) pentru a tine evidenta numarului de aparitii
   pentru fiecare categorie de masini (de exemplu: tipul masinii)
   Cerinta: "folositi un dictionar (map, unordered_map) pt crearea unui raport.
   Sa fie un raport specific problemei/entitatii"
   La aplicatia de inchiriere masini, raportul este: tip <-> cate masini de acel tip exista */
class DTO {
public:
    std::string nume;   // numele categoriei (de ex. tipul masinii: "SUV", "berlina")
    int aparitii;       // numarul de masini din aceasta categorie

    /* Constructor implicit - initializeaza la valori goale
       @param: -
       @return: - */
    DTO() : nume{ "" }, aparitii{ 0 } {}

    /* Constructor cu parametri
       @param nume: numele categoriei
       @param aparitii: numarul initial de aparitii
       @return: - */
    DTO(const std::string& nume, int aparitii) : nume{ nume }, aparitii{ aparitii } {}

    /* Incrementeaza numarul de aparitii cu 1
       Folosita cand se gaseste o noua masina din aceeasi categorie
       @param: -
       @return: - */
    void incrementAparitii() noexcept {
        aparitii += 1;
    }
};
