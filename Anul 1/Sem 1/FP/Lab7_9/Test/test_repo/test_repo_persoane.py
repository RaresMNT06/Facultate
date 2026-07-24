import unittest
from Error.repository_error import Repo_error
from Domain.domain_person import Person
from Repository.repository_person import RepositoryPer


class TestRepositoryPersoane(unittest.TestCase):

    def test_add_person(self):
        repo = RepositoryPer()
        p = Person(123, "Rares", "Cluj")

        repo.addPerson(p)
        lista = repo.read_list()

        self.assertEqual(len(lista), 1)
        self.assertEqual(lista[0].get_id(), 123)
        self.assertEqual(lista[0].get_nume(), "Rares")
        self.assertEqual(lista[0].get_adresa(), "Cluj")

        # Test duplicat
        with self.assertRaises(Repo_error):
            repo.addPerson(p)

    def test_read_list(self):
        repo = RepositoryPer()
        p = Person(123, "Rares", "Cluj")

        repo.addPerson(p)
        lista1 = repo.read_list()
        lista2 = repo.read_list()

        self.assertIsNot(lista1, lista2)   # liste diferite, obiecte diferite
        self.assertEqual(lista1, lista2)   # dar conținut identic

    def test_update_person(self):
        repo = RepositoryPer()
        p = Person(1, "Rares", "Cluj")

        repo.addPerson(p)

        persoana = repo.updatePerson(Person(1, None, None))

        self.assertEqual(persoana.get_id(), 1)
        self.assertEqual(persoana.get_nume(), "Rares")
        self.assertEqual(persoana.get_adresa(), "Cluj")

        # Test persoană inexistentă
        with self.assertRaises(Repo_error):
            repo.updatePerson(Person(2, None, None))

        # Test modificare
        persoana.set_nume("Ana")
        lista = repo.read_list()

        self.assertEqual(lista[0].get_nume(), "Ana")
        self.assertEqual(lista[0].get_adresa(), "Cluj")

    def test_delete_person(self):
        repo = RepositoryPer()
        p1 = Person(1, "Rares", "Cluj")
        p2 = Person(2, "Mihai", "Oradea")

        repo.addPerson(p1)
        repo.addPerson(p2)

        repo.deletePerson(Person(1, None, None))
        lista = repo.read_list()

        self.assertEqual(len(lista), 1)
        self.assertEqual(lista[0].get_id(), 2)


