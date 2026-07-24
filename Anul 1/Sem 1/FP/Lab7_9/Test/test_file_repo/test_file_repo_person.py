from Error.repository_error import Repo_error
from Domain.domain_person import Person
from Repository.file_repo_person import FileRepositoryPer
import unittest

class TestFileRepoPersoane(unittest.TestCase):

    def setUp(self):
        self.test_file = "test_persoane.txt"
        open(self.test_file, "w").close()
        self.repo = FileRepositoryPer(self.test_file)

    def tearDown(self):
        open(self.test_file, "w").close()

    def test_addPerson(self):
        p = Person(12, "Ana", "Strada Mare")
        self.repo.addPerson(p)

        lista = self.repo.read_list()
        self.assertEqual(len(lista), 1)
        self.assertEqual(lista[0].get_id(), 12)
        self.assertEqual(lista[0].get_nume(), "Ana")
        self.assertEqual(lista[0].get_adresa(), "Strada Mare")


        with self.assertRaises(Repo_error):
            self.repo.addPerson(p)

    def test_deletePerson(self):
        p = Person(12, "Ana", "Strada Mare")
        self.repo.addPerson(p)


        self.repo.deletePerson(Person(12, None, None))
        lista = self.repo.read_list()
        self.assertEqual(len(lista), 0)


        with self.assertRaises(Repo_error):
            self.repo.deletePerson(Person(99, None, None))

    def test_updatePerson(self):
        p = Person(12, "Ana", "Strada Mare")
        self.repo.addPerson(p)


        found = self.repo.updatePerson(Person(12, None, None))
        found.set_nume("Maria")
        self.repo.write_to_file()

        lista = self.repo.read_list()
        self.assertEqual(lista[0].get_nume(), "Maria")


        with self.assertRaises(Repo_error):
            self.repo.updatePerson(Person(99, None, None))