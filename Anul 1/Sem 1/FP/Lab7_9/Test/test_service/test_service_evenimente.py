import unittest
from Repository.repository_eveniment import RepositoryEv
from Controller.service_eveniment import ServiceEv
from Error.repository_error import Repo_error
from Error.validator_error import Val_error


class TestServiceEveniment(unittest.TestCase):

    def setUp(self):
        self.repo = RepositoryEv()
        self.service = ServiceEv(self.repo)

    def test_add_eveniment(self):
        """ White-box: testare ramură validă și ramură duplicat """

        self.service.add_ev(12, "2025-01-01", "10:00", "Nunta")
        lista = self.service.get_list_evenimente()

        self.assertEqual(len(lista), 1)
        self.assertEqual(lista[0].get_id_ev(), 12)
        self.assertEqual(lista[0].get_data(), "2025-01-01")
        self.assertEqual(lista[0].get_timp(), "10:00")
        self.assertEqual(lista[0].get_descriere(), "Nunta")

        # duplicat → trebuie să ridice Repo_error
        with self.assertRaises(Repo_error):
            self.service.add_ev(12, "2025-02-02", "22:00", "Concert")

    def test_add_eveniment_invalid(self):
        """ Black-box test: doar testăm input invalid, fără a vedea implementarea """

        with self.assertRaises(Val_error):
            self.service.add_ev(21, "", "10:00", "Test")

        with self.assertRaises(Val_error):
            self.service.add_ev(31, "2025-01-01", "", "Test")

        with self.assertRaises(Val_error):
            self.service.add_ev(41, "2025-01-01", "10:00", "")

    def test_update_eveniment(self):


        self.service.add_ev(12, "2025-01-01", "10:00", "Nunta")

        ev = self.service.update_eveniment(12)
        self.assertEqual(ev.get_id_ev(), 12)
        self.assertEqual(ev.get_descriere(), "Nunta")

        # eveniment inexistent
        with self.assertRaises(Repo_error):
            self.service.update_eveniment(99)

        # update efectiv
        ev.set_descriere("Petrecere")

        lista = self.service.get_list_evenimente()
        self.assertEqual(lista[0].get_descriere(), "Petrecere")
        self.assertEqual(lista[0].get_timp(), "10:00")

    def test_delete_eveniment(self):


        self.service.add_ev(12, "2025-01-01", "10:00", "Nunta")
        self.service.add_ev(21, "2025-02-02", "20:00", "Botez")

        self.service.delete_eveniment(12)

        lista = self.service.get_list_evenimente()

        self.assertEqual(len(lista), 1)
        self.assertEqual(lista[0].get_id_ev(), 21)
        self.assertEqual(lista[0].get_descriere(), "Botez")


