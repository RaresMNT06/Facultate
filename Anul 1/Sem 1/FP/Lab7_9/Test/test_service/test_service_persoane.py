import unittest
from Error.repository_error import Repo_error
from Error.validator_error import Val_error
from Repository.repository_person import RepositoryPer
from Controller.service_person import ServicePer


class TestServicePersoane(unittest.TestCase):

    def test_add_person(self):
        repo = RepositoryPer()
        service = ServicePer(repo)

        service.add_persoana(12, "Rares", "Cluj")

        lista = service.get_list_persoane()
        self.assertEqual(len(lista), 1)
        self.assertEqual(lista[0].get_id(), 12)
        self.assertEqual(lista[0].get_nume(), "Rares")
        self.assertEqual(lista[0].get_adresa(), "Cluj")

    def test_add_person_invalid(self):
        repo = RepositoryPer()
        service = ServicePer(repo)

        with self.assertRaises(Val_error):
            service.add_persoana(21, "Ra2res", "Cluj")

    def test_add_duplicate_person(self):
        repo = RepositoryPer()
        service = ServicePer(repo)

        service.add_persoana(12, "Rares", "Cluj")

        with self.assertRaises(Repo_error):
            service.add_persoana(12, "Ana", "Oradea")

    def test_update_person(self):
        repo = RepositoryPer()
        service = ServicePer(repo)

        service.add_persoana(12, "Rares", "Cluj")
        persoana = service.update_persoana(12)

        self.assertEqual(persoana.get_id(), 12)
        self.assertEqual(persoana.get_nume(), "Rares")
        self.assertEqual(persoana.get_adresa(), "Cluj")

        # Persoana inexistentă
        with self.assertRaises(Repo_error):
            service.update_persoana(99)

        # Actualizare nume
        persoana.set_nume("Ana")
        lista = service.get_list_persoane()

        self.assertEqual(lista[0].get_nume(), "Ana")
        self.assertEqual(lista[0].get_adresa(), "Cluj")

    def test_delete_person(self):
        repo = RepositoryPer()
        service = ServicePer(repo)

        service.add_persoana(12, "Rares", "Cluj")
        service.add_persoana(21, "Ana", "Oradea")

        service.delete_persoana(12)

        lista = service.get_list_persoane()
        self.assertEqual(len(lista), 1)
        self.assertEqual(lista[0].get_id(), 21)
        self.assertEqual(lista[0].get_nume(), "Ana")


