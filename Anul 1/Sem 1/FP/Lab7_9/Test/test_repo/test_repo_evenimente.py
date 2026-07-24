import unittest
from Error.repository_error import Repo_error
from Domain.domain_eveniment import Eveniment
from Repository.repository_eveniment import RepositoryEv


class TestRepositoryEvenimente(unittest.TestCase):

    def setUp(self):
        self.repo = RepositoryEv()

    def tearDown(self):
        pass

    def test_add_ev(self):
        repo = RepositoryEv()
        ev = Eveniment(123, "2025-01-01", "10:00", "Nunta")

        repo.addEveniment(ev)

        lista = repo.read_list()
        self.assertEqual(len(lista), 1)
        self.assertEqual(lista[0].get_id_ev(), 123)
        self.assertEqual(lista[0].get_data(), "2025-01-01")
        self.assertEqual(lista[0].get_timp(), "10:00")
        self.assertEqual(lista[0].get_descriere(), "Nunta")


        with self.assertRaises(Repo_error):
            repo.addEveniment(ev)

    def test_read_list(self):
        repo = RepositoryEv()
        ev = Eveniment(123, "2025-01-01", "10:00", "Nunta")
        repo.addEveniment(ev)

        lista1 = repo.read_list()
        lista2 = repo.read_list()

        self.assertIsNot(lista1, lista2)
        self.assertEqual(lista1, lista2)

    def test_update_ev(self):
        repo = RepositoryEv()
        ev = Eveniment(1, "2025-01-01", "10:00", "Nunta")
        repo.addEveniment(ev)

        eveniment = repo.updateEveniment(Eveniment(1, None, None, None))

        self.assertEqual(eveniment.get_id_ev(), 1)
        self.assertEqual(eveniment.get_data(), "2025-01-01")
        self.assertEqual(eveniment.get_timp(), "10:00")
        self.assertEqual(eveniment.get_descriere(), "Nunta")

        # eveniment inexistent
        with self.assertRaises(Repo_error):
            repo.updateEveniment(Eveniment(2, None, None, None))

        # modificare
        eveniment.set_descriere("Petrecere")
        lista = repo.read_list()

        self.assertEqual(lista[0].get_descriere(), "Petrecere")
        self.assertEqual(lista[0].get_timp(), "10:00")

    def test_delete_ev(self):
        repo = RepositoryEv()
        ev1 = Eveniment(1, "2025-01-01", "10:00", "Nunta")
        ev2 = Eveniment(2, "2025-02-02", "20:00", "Botez")

        repo.addEveniment(ev1)
        repo.addEveniment(ev2)

        repo.deleteEveniment(Eveniment(1, None, None, None))

        lista = repo.read_list()

        self.assertEqual(len(lista), 1)
        self.assertEqual(lista[0].get_id_ev(), 2)


