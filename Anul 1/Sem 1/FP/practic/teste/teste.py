from domain.domain_sedinte import Sedinte
from repo.repo_sedinte import Repo_sedinte
from repo.repo_exeption import RepoException

def test_adaugare():

    f_test = "test_sedinte.txt"
    open(f_test, "w").close()
    """
    Test de verificare adaugare
    """

    repo = Repo_sedinte(f_test)

    s1 = Sedinte("20.02", "08:00", "informatii", "normala")
    repo.adaugare_sedinta(s1)

    assert len(repo.get_all_sedinta()) ==1
    assert repo.get_all_sedinta()[0].get_data()== "20.02"

    repo2 = Repo_sedinte(f_test)
    assert len(repo2.get_all_sedinta()) ==1
    """
    Test sa nu se adauge aceeasi sedinta
    """
    try:
        repo2.adaugare_sedinta(s1)
        assert False

    except RepoException:
        assert True
    open(f_test, "w").close()
    """
    Test pentru data inainte de data de azi
    """
    repo3 = Repo_sedinte(f_test)
    s2 = Sedinte("02.02", "08:00", "informatii", "normala")
    try:
        repo3.adaugare_sedinta(s2)
        assert False
    except RepoException:
        assert True




