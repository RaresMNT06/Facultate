#include "service.h"
#include "exceptii.h"
#include <algorithm>
#include <iterator>
#include <random>
#include <chrono>
#include <fstream>

/* Verifica daca caracterul este litera mare (A-Z)
   Numerele de inmatriculare romanesti folosesc doar majuscule
   @param c: caracterul de verificat ; @return: true daca e litera mare */
bool Service::esteLitera(char c) const noexcept {
    return (c >= 'A' && c <= 'Z');
}

/* Verifica daca caracterul este cifra (0-9)
   @param c: caracterul de verificat ; @return: true daca e cifra */
bool Service::esteCifra(char c) const noexcept {
    return c >= '0' && c <= '9';
}

/* Valideaza formatul numarului de inmatriculare
   Accepta formatul standard (ex: CJ 01 ABC) sau Bucuresti (ex: B 01 ABC / B 001 ABC)
   @param nr: numarul de validat ; @return: true daca formatul e valid */
bool Service::esteNrInmatriculareValid(const std::string& nr) const {
    const auto len = nr.size();

    // Format standard: 2 litere + spatiu + 2 cifre + spatiu + 3 litere (ex: "CJ 01 ABC")
    if (len == 9 && nr.at(1) != ' ') {
        if (!esteLitera(nr.at(0)) || !esteLitera(nr.at(1))) return false;
        if (nr.at(2) != ' ') return false;
        if (!esteCifra(nr.at(3)) || !esteCifra(nr.at(4))) return false;
        if (nr.at(5) != ' ') return false;
        if (!esteLitera(nr.at(6)) || !esteLitera(nr.at(7)) || !esteLitera(nr.at(8))) return false;
        return true;
    }

    // Format Bucuresti: B + spatiu + 2 sau 3 cifre + spatiu + 3 litere
    if ((len == 8 || len == 9) && nr.at(0) == 'B' && nr.at(1) == ' ') {
        if (len == 9) {
            if (!esteCifra(nr.at(2)) || !esteCifra(nr.at(3)) || !esteCifra(nr.at(4))) return false;
            if (nr.at(5) != ' ') return false;
            if (!esteLitera(nr.at(6)) || !esteLitera(nr.at(7)) || !esteLitera(nr.at(8))) return false;
        }
        else {
            if (!esteCifra(nr.at(2)) || !esteCifra(nr.at(3))) return false;
            if (nr.at(4) != ' ') return false;
            if (!esteLitera(nr.at(5)) || !esteLitera(nr.at(6)) || !esteLitera(nr.at(7))) return false;
        }
        return true;
    }

    return false;
}

/* Initializeaza service-ul cu o referinta la repository
   @param repo: referinta la repository ; @return: - */
Service::Service(Repository& repo) noexcept : repo{ repo } {}

/* Valideaza si adauga o masina in repository
   Arunca ValidareException daca un camp e gol sau formatul nrInmatriculare e invalid
   Arunca MasinaDuplicataException daca masina exista deja (propagata din Repository)
   @param nrInmatriculare: cheia unica ; @param producator: producatorul
   @param model: modelul ; @param tip: tipul masinii
   @param inchiriata: statusul de inchiriere ; @return: - */
void Service::adaugaMasina(const std::string& nrInmatriculare, const std::string& producator,
    const std::string& model, const std::string& tip, bool inchiriata) {
    if (nrInmatriculare.empty() || producator.empty() || model.empty() || tip.empty())
        throw ValidareException("Toate campurile sunt obligatorii!");
    if (!esteNrInmatriculareValid(nrInmatriculare))
        throw ValidareException("Format invalid! Exemple: 'CJ 01 ABC' sau 'B 67 MNT'");
    Masina m{ nrInmatriculare, producator, model, tip, inchiriata };
    repo.adauga(m);
}

/* Valideaza si sterge masina cu nrInmatriculare dat
   Arunca ValidareException daca campul e gol
   Arunca MasinaInexistentaException daca masina nu exista (propagata din Repository)
   @param nrInmatriculare: cheia de identificare ; @return: - */
void Service::stergeMasina(const std::string& nrInmatriculare) {
    if (nrInmatriculare.empty())
        throw ValidareException("Numarul de inmatriculare nu poate fi gol!");
    repo.sterge(nrInmatriculare);
}

/* Valideaza si modifica masina identificata prin nrInmatriculare
   Arunca ValidareException daca un camp e gol sau formatul nrInmatriculare e invalid
   Arunca MasinaInexistentaException daca masina nu exista (propagata din Repository)
   @param nrInmatriculare: cheia de identificare
   @param producator: noul producator ; @param model: noul model ; @param tip: noul tip
   @return: - */
void Service::modificaMasina(const std::string& nrInmatriculare, const std::string& producator,
    const std::string& model, const std::string& tip) {
    if (nrInmatriculare.empty() || producator.empty() || model.empty() || tip.empty())
        throw ValidareException("Toate campurile sunt obligatorii!");
    if (!esteNrInmatriculareValid(nrInmatriculare))
        throw ValidareException("Format invalid! Exemple: 'CJ 01 ABC' sau 'B 67 MNT'");
    repo.modifica(nrInmatriculare, producator, model, tip);
}

/* Cauta masina dupa nrInmatriculare
   Arunca ValidareException daca campul e gol
   Arunca MasinaInexistentaException daca masina nu exista (propagata din Repository)
   @param nrInmatriculare: cheia cautata ; @return: referinta constanta la masina gasita */
const Masina& Service::cautaMasina(const std::string& nrInmatriculare) const {
    if (nrInmatriculare.empty())
        throw ValidareException("Numarul de inmatriculare nu poate fi gol!");
    return repo.cauta(nrInmatriculare);
}

/* Returneaza toata lista de masini fara copiere
   @param: - ; @return: referinta constanta la vectorul de masini */
const std::vector<Masina>& Service::getToateMasinile() const noexcept {
    return repo.getAll();
}

/* Returneaza un vector nou cu masinile care au producatorul dat
   Foloseste std::copy_if pentru filtrare si reserve pentru a evita realocari
   @param producator: producatorul cautat ; @return: vector cu masinile filtrate */
std::vector<Masina> Service::filtreazaDupaProducator(const std::string& producator) const {
    const auto& toate = repo.getAll();
    std::vector<Masina> rezultat;
    rezultat.reserve(toate.size());
    std::copy_if(toate.cbegin(), toate.cend(), std::back_inserter(rezultat),
        [&producator](const Masina& m) {
            return m.getProducator() == producator;
        });
    return rezultat;
}

/* Returneaza un vector nou cu masinile care au tipul dat
   Foloseste std::copy_if pentru filtrare si reserve pentru a evita realocari
   @param tip: tipul cautat ; @return: vector cu masinile filtrate */
std::vector<Masina> Service::filtreazaDupaTip(const std::string& tip) const {
    const auto& toate = repo.getAll();
    std::vector<Masina> rezultat;
    rezultat.reserve(toate.size());
    std::copy_if(toate.cbegin(), toate.cend(), std::back_inserter(rezultat),
        [&tip](const Masina& m) {
            return m.getTip() == tip;
        });
    return rezultat;
}

/* Returneaza un vector nou sortat dupa nrInmatriculare crescator sau descrescator
   Foloseste std::sort cu un comparator lambda
   @param crescator: true = crescator, false = descrescator ; @return: vector sortat */
std::vector<Masina> Service::sorteazaDupaNrInmatriculare(bool crescator) const {
    std::vector<Masina> rezultat = repo.getAll();
    std::sort(rezultat.begin(), rezultat.end(), [crescator](const Masina& a, const Masina& b) {
        if (crescator)
            return a.getNrInmatriculare() < b.getNrInmatriculare();
        return a.getNrInmatriculare() > b.getNrInmatriculare();
        });
    return rezultat;
}

/* Returneaza un vector nou sortat dupa tip crescator sau descrescator
   Foloseste std::sort cu un comparator lambda
   @param crescator: true = crescator, false = descrescator ; @return: vector sortat */
std::vector<Masina> Service::sorteazaDupaTip(bool crescator) const {
    std::vector<Masina> rezultat = repo.getAll();
    std::sort(rezultat.begin(), rezultat.end(), [crescator](const Masina& a, const Masina& b) {
        if (crescator)
            return a.getTip() < b.getTip();
        return a.getTip() > b.getTip();
        });
    return rezultat;
}

/* Returneaza un vector nou sortat dupa producator, apoi dupa model la egalitate
   Foloseste std::sort cu un comparator lambda compus
   @param crescator: true = crescator, false = descrescator ; @return: vector sortat */
std::vector<Masina> Service::sorteazaDupaProducatorModel(bool crescator) const {
    std::vector<Masina> rezultat = repo.getAll();
    std::sort(rezultat.begin(), rezultat.end(), [crescator](const Masina& a, const Masina& b) {
        if (a.getProducator() == b.getProducator()) {
            if (crescator)
                return a.getModel() < b.getModel();
            return a.getModel() > b.getModel();
        }
        if (crescator)
            return a.getProducator() < b.getProducator();
        return a.getProducator() > b.getProducator();
        });
    return rezultat;
}

/* Marcheaza o masina ca inchiriata
   Cauta masina prin Repository si modifica doar statusul
   Arunca ValidareException daca campul e gol sau masina e deja inchiriata
   Arunca MasinaInexistentaException daca masina nu exista (propagata din Repository)
   @param nrInmatriculare: cheia masinii de inchiriat ; @return: - */
void Service::inchiriazaMasina(const std::string& nrInmatriculare) {
    if (nrInmatriculare.empty())
        throw ValidareException("Numarul de inmatriculare nu poate fi gol!");
    // Cautam masina existenta in repo (poate arunca MasinaInexistentaException)
    const Masina& m = repo.cauta(nrInmatriculare);
    if (m.getInchiriata())
        throw ValidareException("Masina este deja inchiriata!");
    repo.setStatusInchiriere(nrInmatriculare, true);
}

/* Marcheaza o masina ca returnata (disponibila)
   Cauta masina prin Repository si modifica doar statusul
   Arunca ValidareException daca campul e gol sau masina e deja disponibila
   Arunca MasinaInexistentaException daca masina nu exista (propagata din Repository)
   @param nrInmatriculare: cheia masinii de returnat ; @return: - */
void Service::returneazaMasina(const std::string& nrInmatriculare) {
    if (nrInmatriculare.empty())
        throw ValidareException("Numarul de inmatriculare nu poate fi gol!");
    const Masina& m = repo.cauta(nrInmatriculare);
    if (!m.getInchiriata())
        throw ValidareException("Masina este deja disponibila!");
    repo.setStatusInchiriere(nrInmatriculare, false);
}

/* ===== Implementari pentru lista de spalare (cerinta 9) ===== */

/* Adauga o masina in lista de spalare dupa cautarea ei in repo
   Arunca ValidareException daca nrInmatriculare are format invalid
   Arunca MasinaInexistentaException daca masina nu exista in garaj
   Arunca ValidareException daca masina e deja in lista de spalare
   @param nrInmatriculare: cheia masinii de adaugat in lista de spalare ; @return: - */
void Service::adaugaInListaSpalate(const std::string& nrInmatriculare) {
    // Validam formatul - nu doar daca e gol (consistent cu adaugaMasina)
    if (!esteNrInmatriculareValid(nrInmatriculare))
        throw ValidareException("Format invalid! Exemple: 'CJ 01 ABC' sau 'B 67 MNT'");
    // Cautam masina in repo - propaga MasinaInexistentaException daca nu exista
    const Masina& m = repo.cauta(nrInmatriculare);
    // Verificam sa nu fie deja in lista de spalare
    if (repo.existaInListaSpalate(nrInmatriculare))
        throw ValidareException("Masina este deja in lista de spalare!");
    repo.adaugaInListaSpalate(m);
}

/* Goleste lista de spalare - elimina toate masinile
   @param: - ; @return: - */
void Service::golesteListaSpalate() noexcept {
    repo.golesteListaSpalate();
}

/* Genereaza o lista de spalare aleatoare cu n masini
   Goleste lista existenta inainte de a o popula
   Foloseste std::default_random_engine cu seed din chrono pentru selectia aleatoare
   Optimizat: amestecam doar un vector de indici, nu o copie a tuturor masinilor
   (evitam copy constructor pentru fiecare masina din garaj)
   Arunca ValidareException daca n este invalid (peste numarul de masini)
   @param nrMasini: numarul de masini de adaugat in lista de spalare ; @return: - */
void Service::genereazaListaSpalate(size_t nrMasini) {
    const auto& toate = repo.getAll();
    if (nrMasini > toate.size())
        throw ValidareException("Nu exista suficiente masini in garaj pentru generare!");

    // Golim lista existenta inainte sa o populam din nou
    repo.golesteListaSpalate();

    // Construim un vector cu indicii [0, 1, 2, ..., size-1] - nu copiem masinile
    std::vector<size_t> indici(toate.size());
    for (size_t i = 0; i < indici.size(); i++)
        indici[i] = i;

    // Amestecam aleator doar indicii (operatie ieftina, doar size_t-uri)
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(indici.begin(), indici.end(), std::default_random_engine(static_cast<unsigned>(seed)));

    // Adaugam primele nrMasini in lista de spalare folosind indicii amestecati
    // Aici se face copy constructor (necesar - vectorul stocheaza valori, nu referinte)
    for (size_t i = 0; i < nrMasini; i++) {
        repo.adaugaInListaSpalate(toate.at(indici.at(i)));
    }
}

/* Returneaza lista de spalare curenta fara copiere
   @param: - ; @return: referinta constanta la vectorul cu masinile de spalat */
const std::vector<Masina>& Service::getListaSpalate() const noexcept {
    return repo.getListaSpalate();
}

/* Returneaza numarul de masini din lista de spalare
   @param: - ; @return: numarul de masini din lista de spalare */
size_t Service::lungimeListaSpalate() const noexcept {
    return repo.lungimeListaSpalate();
}

/* Detecteaza extensia fisierului pentru a alege formatul de export
   Helper local - nu este expusa in interfata clasei
   @param numeFisier: calea fisierului
   @return: extensia in lowercase, sau string gol */
static std::string extensieFisier(const std::string& numeFisier) {
    auto poz = numeFisier.find_last_of('.');
    if (poz == std::string::npos) return "";
    std::string ext = numeFisier.substr(poz + 1);
    // Convertim la litere mici pentru a accepta CSV/csv/Csv
    for (auto& c : ext) c = static_cast<char>(std::tolower(c));
    return ext;
}

/* Exporta lista de spalare intr-un fisier CSV sau HTML
   Decide formatul dupa extensia fisierului (.csv sau .html / .htm)
   Format CSV: nrInmatriculare,producator,model,tip,inchiriata (fara header)
   Arunca ValidareException daca fisierul nu poate fi deschis
   Arunca ValidareException daca extensia nu e suportata
   @param numeFisier: calea fisierului in care se salveaza ; @return: - */
void Service::exportListaSpalate(const std::string& numeFisier) const {
    if (numeFisier.empty())
        throw ValidareException("Numele fisierului nu poate fi gol!");

    const std::string ext = extensieFisier(numeFisier);
    if (ext != "csv" && ext != "html" && ext != "htm")
        throw ValidareException("Format nesuportat! Foloseste .csv sau .html");

    std::ofstream out(numeFisier);
    if (!out.is_open())
        throw ValidareException("Nu s-a putut deschide fisierul pentru scriere!");

    const auto& lista = repo.getListaSpalate();

    if (ext == "csv") {
        // Format CSV: o linie per masina, campuri separate prin virgula
        for (const auto& m : lista) {
            out << m.getNrInmatriculare() << ","
                << m.getProducator() << ","
                << m.getModel() << ","
                << m.getTip() << ","
                << (m.getInchiriata() ? 1 : 0) << "\n";
        }
    }
    else {
        // Format HTML cu tabel
        out << "<!DOCTYPE html>\n<html>\n<head>\n"
            << "<meta charset=\"UTF-8\">\n"
            << "<title>Lista masini de spalat</title>\n"
            << "<style>table{border-collapse:collapse;}th,td{border:1px solid #333;padding:6px;}</style>\n"
            << "</head>\n<body>\n"
            << "<h1>Lista masini de spalat</h1>\n"
            << "<table>\n"
            << "<tr><th>Nr. Inmatriculare</th><th>Producator</th><th>Model</th><th>Tip</th><th>Status</th></tr>\n";
        for (const auto& m : lista) {
            out << "<tr><td>" << m.getNrInmatriculare()
                << "</td><td>" << m.getProducator()
                << "</td><td>" << m.getModel()
                << "</td><td>" << m.getTip()
                << "</td><td>" << (m.getInchiriata() ? "inchiriata" : "disponibila")
                << "</td></tr>\n";
        }
        out << "</table>\n</body>\n</html>\n";
    }
}

/* ===== Implementare raport  ===== */

/* Genereaza un raport: pentru fiecare tip de masina (sedan, SUV, etc.)
   returneaza un DTO cu numele tipului si numarul de masini de acel tip
   Foloseste std::map - cheia e tipul, valoarea e DTO cu numar de aparitii
   @param: - ; @return: dictionar tip -> DTO(tip, nrAparitii) */
std::map<std::string, DTO> Service::analizaMasiniDupaTip() const {
    std::map<std::string, DTO> rezultat;

    // Range-based for peste toate masinile din repo
    for (const auto& m : repo.getAll()) {
        const std::string& tip = m.getTip();
        // Daca tipul e deja in raport, incrementam aparitiile
        if (rezultat.contains(tip)) {
            rezultat[tip].incrementAparitii();
        }
        else {
            // Daca e tip nou, il adaugam cu 1 aparitie
            rezultat[tip] = DTO(tip, 1);
        }
    }
    return rezultat;
}