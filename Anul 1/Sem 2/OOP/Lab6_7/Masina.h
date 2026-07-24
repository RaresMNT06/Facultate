#pragma once
#include <string>

/* Clasa Masina reprezinta entitatea principala a aplicatiei
   Contine datele unei masini: nr inmatriculare, producator, model, tip */
class Masina {
private:
    std::string nrInmatriculare;
    std::string producator;
    std::string model;
    std::string tip;

public:
    /* Constructor - initializeaza toate campurile masinii
       @param nrInmatriculare: cheia unica a masinii
       @param producator: producatorul masinii
       @param model: modelul masinii
       @param tip: tipul masinii (sedan, SUV, etc) */
    Masina(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip);

    /* Copy constructor - afiseaza un mesaj cand se copiaza o masina */
    Masina(const Masina& other);

    /* Move constructor */
    Masina(Masina&& other) noexcept;

    /* Operator de atribuire - sters intentionat
       @param other: masina de atribuit ; @return: - */
    Masina& operator=(const Masina& other) = default;

    /* Destructor implicit
       @param: - ; @return: - */
    ~Masina() = default;

    /* Returneaza numarul de inmatriculare al masinii
       @param: - ; @return: referinta constanta la nrInmatriculare */
    const std::string& getNrInmatriculare() const noexcept;

    /* Returneaza producatorul masinii
       @param: - ; @return: referinta constanta la producator */
    const std::string& getProducator() const noexcept;

    /* Returneaza modelul masinii
       @param: - ; @return: referinta constanta la model */
    const std::string& getModel() const noexcept;

    /* Returneaza tipul masinii
       @param: - ; @return: referinta constanta la tip */
    const std::string& getTip() const noexcept;

    /* Modifica producatorul masinii
       @param newProducator: noul producator ; @return: - */
    void setProducator(const std::string& newProducator);

    /* Modifica modelul masinii
       @param newModel: noul model ; @return: - */
    void setModel(const std::string& newModel);

    /* Modifica tipul masinii
       @param newTip: noul tip ; @return: - */
    void setTip(const std::string& newTip);

    /* Returneaza masina ca text
       @param: - ; @return: string cu datele masinii */
    std::string toString() const;

    /* Doua masini sunt egale daca au acelasi nrInmatriculare
       @param other: masina cu care comparam ; @return: true daca sunt egale */
    bool operator==(const Masina& other) const noexcept;
};