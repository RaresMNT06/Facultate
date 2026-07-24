from Error.repository_error import Repo_error
from Domain.domain_eveniment import Eveniment
from Repository.file_repo_eveniment import FileRepositoryEv
import unittest

class TestFileRepo(unittest.TestCase):

    def setUp(self):
        self.test_file = "test_evenimente.txt"
        open(self.test_file, "w").close()
        self.repo = FileRepositoryEv(self.test_file)

    def tearDown(self):
        open(self.test_file, "w").close()

    def test_addEveniment(self):
        ev = Eveniment(1234, "data", "timp", "descriere")
        self.repo.addEveniment(ev)

        lista = self.repo.read_list()
        self.assertEqual(len(lista), 1)
        self.assertEqual(lista[0].get_id_ev(), 1234)
        self.assertEqual(lista[0].get_data(), "data")
        self.assertEqual(lista[0].get_timp(), "timp")
        self.assertEqual(lista[0].get_descriere(), "descriere")

        with self.assertRaises(Repo_error):
            self.repo.addEveniment(ev)

    def test_deleteEveniment(self):

        ev = Eveniment(1234, "data", "timp", "descriere")
        self.repo.addEveniment(ev)

        self.repo.deleteEveniment(Eveniment(1234, None, None, None))

        lista = self.repo.read_list()
        self.assertEqual(len(lista), 0)

        with self.assertRaises(Repo_error):
            self.repo.deleteEveniment(Eveniment(123, None, None, None))

    def test_updateEveniment(self):

        ev = Eveniment(1234, "data", "timp", "descriere")
        self.repo.addEveniment(ev)

        found = self.repo.updateEveniment(Eveniment(1234, None, None, None))
        found.set_descriere("Petrecere")
        self.repo.write_to_file()

        lista = self.repo.read_list()
        self.assertEqual(lista[0].get_descriere(), "Petrecere")

        with self.assertRaises(Repo_error):
            self.repo.updateEveniment(Eveniment(123, None, None,  None))


