#include "service.h"
#include "exceptii.h"
#include <algorithm>
#include <iterator>
#include <random>
#include <chrono>
#include <fstream>

/* Constructor - initializeaza referinta la repo (abstract) si lista de undo goala
   @param repo: referinta la Repository
   @return: - */
Service::Service(Repository& repo) noexcept : repo{ repo } {}

/* Verifica daca caracterul este litera (a-z sau A-Z)
   @param c: caracterul ; @return: true/false */
bool Service::esteLitera(char c) const noexcept {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/* Verifica daca caracterul este cifra (0-9)
   @param c: caracterul ; @return: true/false */
bool Service::esteCifra(char c) const noexcept {
    return c >= '0' && c <= '9';
}

/* Valideaza formatul numarului de inmatriculare
   Format: 1-2 litere mari, spatiu, 2-3 cifre, spatiu, 3 litere mari
   Exemple valide: "CJ 01 ABC", "B 67 MNT", "B 123 XYZ"
   @param nr: numarul de validat ; @return: true daca formatul e valid */
bool Service::esteNrInmatriculareValid(const std::string& nr) const {
    if (nr.empty()) return false;

    size_t i = 0;
    // Prima parte: 1-2 litere mari
    if (i >= nr.size() || !esteLitera(nr[i])) return false;
    ++i;
    if (i < nr.size() && esteLitera(nr[i])) ++i;

    // Spatiu
    if (i >= nr.size() || nr[i] != ' ') return false;
    ++i;

    // A doua parte: 2-3 cifre
    if (i >= nr.size() || !esteCifra(nr[i])) return false;
    ++i;
    if (i >= nr.size() || !esteCifra(nr[i])) return false;
    ++i;
    if (i < nr.size() && esteCifra(nr[i])) ++i;

    // Spatiu
    if (i >= nr.size() || nr[i] != ' ') return false;
    ++i;

    // A treia parte: exact 3 litere mari
    for (int k = 0; k < 3; k++) {
        if (i >= nr.size() || !esteLitera(nr[i]) || nr[i] < 'A' || nr[i] > 'Z') return false;
        ++i;
    }

    // Nu trebuie sa fie nimic dupa
    return i == nr.size();
}

/* Valideaza si adauga o masina, salveaza UndoAdauga in lista
   @param ... ; @return: - */
void Service::adaugaMasina(const std::string& nrInmatriculare, const std::string& producator,
    const std::string& model, const std::string& tip, bool inchiriata) {
    if (nrInmatriculare.empty() || producator.empty() || model.empty() || tip.empty())
        throw ValidareException("Toate campurile sunt obligatorii!");
    if (!esteNrInmatriculareValid(nrInmatriculare))
        throw ValidareException("Format invalid! Exemple: 'CJ 01 ABC' sau 'B 67 MNT'");

    Masina m{ nrInmatriculare, producator, model, tip, inchiriata };
    repo.adauga(m);

    // Daca a reusit adaugarea, salvam actiunea pentru undo
    actiuniUndo.push_back(std::make_unique<UndoAdauga>(repo, nrInmatriculare));
}

/* Valideaza si sterge masina, salveaza UndoSterge in lista
   IMPORTANT: salvam masina inainte de stergere, ca sa o putem reface la undo
   @param nrInmatriculare: cheia ; @return: - */
void Service::stergeMasina(const std::string& nrInmatriculare) {
    if (nrInmatriculare.empty())
        throw ValidareException("Numarul de inmatriculare nu poate fi gol!");

    // Salvam masina inainte de stergere (cauta arunca daca nu exista)
    Masina masinaSteasa = repo.cauta(nrInmatriculare);
    repo.sterge(nrInmatriculare);

    // Salvam actiunea pentru undo
    actiuniUndo.push_back(std::make_unique<UndoSterge>(repo, masinaSteasa));
}

/* Valideaza si modifica masina, salveaza UndoModifica in lista
   IMPORTANT: salvam masina inainte de modificare cu starea ei completa
   @param ... ; @return: - */
void Service::modificaMasina(const std::string& nrInmatriculare, const std::string& producator,
    const std::string& model, const std::string& tip) {
    if (nrInmatriculare.empty() || producator.empty() || model.empty() || tip.empty())
        throw ValidareException("Toate campurile sunt obligatorii!");
    if (!esteNrInmatriculareValid(nrInmatriculare))
        throw ValidareException("Format invalid! Exemple: 'CJ 01 ABC' sau 'B 67 MNT'");

    // Salvam masina inainte de modificare
    Masina masinaVeche = repo.cauta(nrInmatriculare);
    repo.modifica(nrInmatriculare, producator, model, tip);

    // Salvam actiunea pentru undo (cu masina veche cu toate datele)
    actiuniUndo.push_back(std::make_unique<UndoModifica>(repo, masinaVeche));
}

/* Cauta masina - returneaza copie (interfata abstracta nu garanteaza stocare contigua)
   @param nrInmatriculare: cheia ; @return: copia masinii */
Masina Service::cautaMasina(const std::string& nrInmatriculare) const {
    if (nrInmatriculare.empty())
        throw ValidareException("Numarul de inmatriculare nu poate fi gol!");
    return repo.cauta(nrInmatriculare);
}

/* Returneaza toate masinile - copie pentru polimorfism
   @param: - ; @return: vector cu toate masinile */
std::vector<Masina> Service::getToateMasinile() const {
    return repo.getAll();
}

/* Filtreaza masinile dupa producator folosind std::copy_if
   @param producator: producatorul cautat ; @return: vector filtrat */
std::vector<Masina> Service::filtreazaDupaProducator(const std::string& producator) const {
    std::vector<Masina> rezultat;
    auto toate = repo.getAll();
    std::copy_if(toate.cbegin(), toate.cend(), std::back_inserter(rezultat),
        [&producator](const Masina& m) { return m.getProducator() == producator; });
    return rezultat;
}

/* Filtreaza masinile dupa tip folosind std::copy_if
   @param tip: tipul cautat ; @return: vector filtrat */
std::vector<Masina> Service::filtreazaDupaTip(const std::string& tip) const {
    std::vector<Masina> rezultat;
    auto toate = repo.getAll();
    std::copy_if(toate.cbegin(), toate.cend(), std::back_inserter(rezultat),
        [&tip](const Masina& m) { return m.getTip() == tip; });
    return rezultat;
}

/* Sortare dupa nrInmatriculare folosind std::sort
   @param crescator: ordine ; @return: vector sortat */
std::vector<Masina> Service::sorteazaDupaNrInmatriculare(bool crescator) const {
    auto rezultat = repo.getAll();
    std::sort(rezultat.begin(), rezultat.end(), [crescator](const Masina& a, const Masina& b) {
        if (crescator) return a.getNrInmatriculare() < b.getNrInmatriculare();
        return a.getNrInmatriculare() > b.getNrInmatriculare();
        });
    return rezultat;
}

/* Sortare dupa tip ; @param crescator: ordine ; @return: vector sortat */
std::vector<Masina> Service::sorteazaDupaTip(bool crescator) const {
    auto rezultat = repo.getAll();
    std::sort(rezultat.begin(), rezultat.end(), [crescator](const Masina& a, const Masina& b) {
        if (crescator) return a.getTip() < b.getTip();
        return a.getTip() > b.getTip();
        });
    return rezultat;
}

/* Sortare dupa producator + model ; @param crescator: ordine ; @return: vector sortat */
std::vector<Masina> Service::sorteazaDupaProducatorModel(bool crescator) const {
    auto rezultat = repo.getAll();
    std::sort(rezultat.begin(), rezultat.end(), [crescator](const Masina& a, const Masina& b) {
        if (a.getProducator() == b.getProducator()) {
            if (crescator) return a.getModel() < b.getModel();
            return a.getModel() > b.getModel();
        }
        if (crescator) return a.getProducator() < b.getProducator();
        return a.getProducator() > b.getProducator();
        });
    return rezultat;
}

/* Marcheaza o masina ca inchiriata, salveaza UndoModifica
   @param nrInmatriculare: cheia ; @return: - */
void Service::inchiriazaMasina(const std::string& nrInmatriculare) {
    if (nrInmatriculare.empty())
        throw ValidareException("Numarul de inmatriculare nu poate fi gol!");

    Masina masinaVeche = repo.cauta(nrInmatriculare);
    if (masinaVeche.getInchiriata())
        throw ValidareException("Masina este deja inchiriata!");

    repo.setStatusInchiriere(nrInmatriculare, true);
    // Salvam pentru undo - UndoModifica reseteaza si statusul
    actiuniUndo.push_back(std::make_unique<UndoModifica>(repo, masinaVeche));
}

/* Marcheaza o masina ca returnata, salveaza UndoModifica
   @param nrInmatriculare: cheia ; @return: - */
void Service::returneazaMasina(const std::string& nrInmatriculare) {
    if (nrInmatriculare.empty())
        throw ValidareException("Numarul de inmatriculare nu poate fi gol!");

    Masina masinaVeche = repo.cauta(nrInmatriculare);
    if (!masinaVeche.getInchiriata())
        throw ValidareException("Masina este deja disponibila!");

    repo.setStatusInchiriere(nrInmatriculare, false);
    actiuniUndo.push_back(std::make_unique<UndoModifica>(repo, masinaVeche));
}

/* ===== Implementari pentru lista de spalare (cerinta 9) ===== */

/* Adauga o masina in lista de spalare dupa cautarea ei in repo
   Valideaza formatul si verifica sa nu fie deja in lista
   Arunca ValidareException pentru format invalid sau duplicat
   Arunca MasinaInexistentaException daca nu exista in garaj
   @param nrInmatriculare: cheia masinii ; @return: - */
void Service::adaugaInListaSpalate(const std::string& nrInmatriculare) {
    if (!esteNrInmatriculareValid(nrInmatriculare))
        throw ValidareException("Format invalid! Exemple: 'CJ 01 ABC' sau 'B 67 MNT'");
    // Verificam ca exista in garaj (cauta arunca daca nu exista)
    Masina m = repo.cauta(nrInmatriculare);
    if (repo.existaInListaSpalate(nrInmatriculare))
        throw ValidareException("Masina este deja in lista de spalare!");
    repo.adaugaInListaSpalate(m);
    notifyAll();  // Observer: notificam toate ferestrele deschise pe cos
}

/* Goleste complet lista de spalare prin repo
   @param: - ; @return: - */
void Service::golesteListaSpalate() {
    repo.golesteListaSpalate();
    notifyAll();  // Observer: notificam toate ferestrele deschise pe cos
}

/* Genereaza o lista de spalare aleatoare cu n masini
   Optimizat: foloseste forEachMasina pentru a evita copia vectorului din getAll()
   @param nrMasini: numarul de masini ; @return: - */
void Service::genereazaListaSpalate(size_t nrMasini) {
    // Numaram masinile fara sa le copiem
    size_t total = 0;
    repo.forEachMasina([&total](const Masina&) { ++total; });

    if (nrMasini > total)
        throw ValidareException("Nu exista suficiente masini in garaj pentru generare!");

    repo.golesteListaSpalate();

    // Strangem indici si pointeri la masini fara sa le copiem
    // Folosim un vector<const Masina*> - doar pointeri, nu copiem masinile
    std::vector<const Masina*> pointeri;
    pointeri.reserve(total);
    repo.forEachMasina([&pointeri](const Masina& m) { pointeri.push_back(&m); });

    // Amestecam aleator pointerii (foarte ieftin - doar adrese)
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(pointeri.begin(), pointeri.end(), std::default_random_engine(static_cast<unsigned>(seed)));

    // Adaugam primele nrMasini in lista de spalare prin pointer
    // (push_back face copia inevitabila - vectorul stocheaza valori)
    for (size_t i = 0; i < nrMasini; i++) {
        repo.adaugaInListaSpalate(*pointeri.at(i));
    }
    notifyAll();  // Observer: notificam toate ferestrele deschise pe cos
}

/* Returneaza lista de spalare prin repo (copie)
   @param: - ; @return: vector cu toate masinile de spalat */
std::vector<Masina> Service::getListaSpalate() const {
    return repo.getListaSpalate();
}

/* Returneaza numarul de masini din lista de spalare
   @param: - ; @return: numarul de masini de spalat */
size_t Service::lungimeListaSpalate() const {
    return repo.lungimeListaSpalate();
}

/* Helper local pentru extragerea extensiei fisierului
   @param numeFisier: calea fisierului ; @return: extensia in lowercase */
static std::string extensieFisier(const std::string& numeFisier) {
    auto poz = numeFisier.find_last_of('.');
    if (poz == std::string::npos) return "";
    std::string ext = numeFisier.substr(poz + 1);
    for (auto& c : ext) c = static_cast<char>(std::tolower(c));
    return ext;
}

/* Exporta lista de spalare in fisier CSV sau HTML
   @param numeFisier: calea fisierului ; @return: - */
void Service::exportListaSpalate(const std::string& numeFisier) const {
    if (numeFisier.empty())
        throw ValidareException("Numele fisierului nu poate fi gol!");

    const std::string ext = extensieFisier(numeFisier);
    if (ext != "csv" && ext != "html" && ext != "htm")
        throw ValidareException("Format nesuportat! Foloseste .csv sau .html");

    std::ofstream out(numeFisier);
    if (!out.is_open())
        throw ValidareException("Nu s-a putut deschide fisierul pentru scriere!");

    auto lista = repo.getListaSpalate();

    if (ext == "csv") {
        for (const auto& m : lista) {
            out << m.getNrInmatriculare() << ","
                << m.getProducator() << ","
                << m.getModel() << ","
                << m.getTip() << ","
                << (m.getInchiriata() ? 1 : 0) << "\n";
        }
    }
    else {
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

/* ===== Raport / Analiza (cerinta cu dictionar) ===== */

std::map<std::string, DTO> Service::analizaMasiniDupaTip() const {
    std::map<std::string, DTO> rezultat;
    // Folosim forEachMasina pentru a evita copia vectorului
    repo.forEachMasina([&rezultat](const Masina& m) {
        const std::string& tip = m.getTip();
        if (rezultat.contains(tip)) {
            rezultat[tip].incrementAparitii();
        }
        else {
            rezultat[tip] = DTO(tip, 1);
        }
    });
    return rezultat;
}

/* ===== UNDO (cerinta iteratia 2) ===== */

/* Anuleaza ultima actiune folosind polimorfism
   Apelam doUndo() pe pointerul abstract - executia merge la clasa concreta corecta
   @param: - ; @return: - */
void Service::undo() {
    if (actiuniUndo.empty())
        throw ValidareException("Nu mai exista actiuni de anulat!");

    // Apel polimorfic - se executa metoda din clasa derivata corecta
    actiuniUndo.back()->doUndo();
    // unique_ptr eliberează automat memoria la pop_back (e implementat ca destroy + erase)
    actiuniUndo.pop_back();
}

/* Returneaza numarul de actiuni in stiva
   @param: - ; @return: numar de actiuni */
size_t Service::numarActiuniUndo() const noexcept {
    return actiuniUndo.size();
}

/* ===== Implementare OBSERVER PATTERN ===== */

/* Inregistreaza un observer
   Apelata de fereastra in constructor
   @param o: pointer la observer ; @return: - */
void Service::addObserver(Observer* o) {
    observatori.push_back(o);
}

/* Sterge un observer din lista
   Apelata in destructorul ferestrei
   Foloseste std::find pentru a gasi pointerul si erase pentru a-l scoate
   @param o: pointer la observer ; @return: - */
void Service::removeObserver(Observer* o) {
    auto it = std::find(observatori.begin(), observatori.end(), o);
    if (it != observatori.end()) {
        observatori.erase(it);
    }
}

/* Notifica toti observatorii ca s-a schimbat cosul
   Apeleaza polimorfic update() pe fiecare
   @param: - ; @return: - */
void Service::notifyAll() {
    for (auto* obs : observatori) {
        obs->update();
    }
}
