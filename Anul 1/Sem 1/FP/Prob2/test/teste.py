from domain.domain_automobile import DomainAutomobile
from repo.repo_automobile import RepoAutomobile
from repo.repo_exeption import RepoExeption
import os


def test_repo_automobile():
    filename = "test_auto.txt"

    open(filename, "w").close()

    repo = RepoAutomobile(filename)

    # 1. Test Adăugare
    a1 = DomainAutomobile(1, "Dacia", 5000, "Logan", "2022-01-01")
    repo.adaugare_automobile(a1)
    assert len(repo.get_all()) == 1  # Accesăm variabila privată pentru test

    # 2. Test Adăugare Duplicat (trebuie să arunce RepoExeption)
    try:
        repo.adaugare_automobile(a1)
        assert False, "Ar fi trebuit să arunce RepoExeption pentru ID duplicat"
    except RepoExeption as e:
        assert str(e) == "Id ul deja exista"

    # 3. Test Ștergere bazată pe cifră în preț
    # Adăugăm încă un automobil
    a2 = DomainAutomobile(2, "Audi", 1234, "A4", "2021-05-10")
    repo.adaugare_automobile(a2)

    # Prețuri actuale: 5000 (conține cifra 5 și 0) și 1234 (conține 1, 2, 3, 4)
    # Ștergem automobilele care au cifra 3 în preț (doar Audi are)
    nr_sterse = repo.stergere_automobile(3)
    assert nr_sterse == 1
    assert len(repo.get_all()) == 1

    # Ștergem cu cifra 0 (Dacia are 5000)
    nr_sterse = repo.stergere_automobile(0)
    assert nr_sterse == 1
    assert len(repo.get_all()) == 0

    # Curățăm fișierul după test
    if os.path.exists(filename):
        os.remove(filename)

    print("Toate testele pentru Repo au trecut cu succes!")

test_repo_automobile()