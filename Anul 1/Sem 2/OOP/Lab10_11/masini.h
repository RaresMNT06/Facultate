#pragma once
#include <string>

/* Clasa Masina reprezinta entitatea principala a aplicatiei
   Contine datele unei masini: nr inmatriculare, producator, model, tip
   nrInmatriculare este cheia unica - nu are setter pentru a preveni duplicate */
class Masina {
private:
    std::string nrInmatriculare;
    std::string producator;
    std::string model;
    std::string tip;
    bool inchiriata;  // true daca masina este inchiriata, false daca este disponibila

public:
    /* Constructor - initializeaza toate campurile masinii
       @param nrInmatriculare: cheia unica a masinii
       @param producator: producatorul masinii
       @param model: modelul masinii
       @param tip: tipul masinii (sedan, SUV, etc)
       @param inchiriata: statusul de inchiriere (default false)
       @return: - */
    Masina(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip, bool inchiriata = false);

    /* Copy constructor - afiseaza un mesaj cand se copiaza o masina
       Folosit pentru a urmari copierile inutile din aplicatie
       @param other: masina din care se copiaza
       @return: - */
    Masina(const Masina& other);

    /* Move constructor - muta resursele fara copiere
       Marcat noexcept pentru ca std::vector sa foloseasca move la realocare
       @param other: masina din care se muta resursele
       @return: - */
    Masina(Masina&& other) noexcept;

    /* Copy assignment - generat de compilator
        @param other: masina din care se copiaza
        @return: referinta la obiectul curent */
    Masina& operator=(const Masina& other) = default;

    /* Move assignment - muta resursele fara copiere
       Marcat noexcept pentru eficienta in containere STL
       @param other: masina din care se muta resursele
       @return: referinta la obiectul curent */
    Masina& operator=(Masina&& other) noexcept = default;

    /* Destructor implicit
       @param: -
       @return: - */
    ~Masina() = default;

    /* Returneaza numarul de inmatriculare al masinii
       @param: -
       @return: referinta constanta la nrInmatriculare */
    const std::string& getNrInmatriculare() const noexcept;

    /* Returneaza producatorul masinii
       @param: -
       @return: referinta constanta la producator */
    const std::string& getProducator() const noexcept;

    /* Returneaza modelul masinii
       @param: -
       @return: referinta constanta la model */
    const std::string& getModel() const noexcept;

    /* Returneaza tipul masinii
       @param: -
       @return: referinta constanta la tip */
    const std::string& getTip() const noexcept;

    /* Returneaza statusul de inchiriere
       @param: -
       @return: true daca masina e inchiriata, false altfel */
    bool getInchiriata() const noexcept;

    /* Modifica producatorul masinii
       @param newProducator: noul producator
       @return: - */
    void setProducator(const std::string& newProducator);

    /* Modifica modelul masinii
       @param newModel: noul model
       @return: - */
    void setModel(const std::string& newModel);

    /* Modifica tipul masinii
       @param newTip: noul tip
       @return: - */
    void setTip(const std::string& newTip);

    /* Modifica statusul de inchiriere
       @param newInchiriata: noul status
       @return: - */
    void setInchiriata(bool newInchiriata) noexcept;

    /* Returneaza masina ca text pentru afisare sau export
       @param: -
       @return: string cu datele masinii */
    std::string toString() const;

    /* Doua masini sunt egale daca au acelasi nrInmatriculare
       @param other: masina cu care comparam
       @return: true daca au acelasi nrInmatriculare, false altfel */
    bool operator==(const Masina& other) const noexcept;

    /* Operatorul invers pentru !=
       @param other: masina cu care comparam
       @return: true daca au nrInmatriculare diferite, false altfel */
    bool operator!=(const Masina& other) const noexcept;
};