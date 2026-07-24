import unittest
from Error.repository_error import Repo_error
from Domain.domain_inscriere import Participare
from Repository.file_repo_inscriere import FileRepositoryInscriere

class TestFileRepoInscriere(unittest.TestCase):

    def setUp(self):
        self.test_file = "test_inscrieri.txt"
        open(self.test_file, "w").close()
        self.repo = FileRepositoryInscriere(self.test_file)

    def tearDown(self):
        open(self.test_file, "w").close()

    def test_addInscriere(self):
        inscriere = Participare(10, 200)
        self.repo.addinscriere(inscriere)

        lista = self.repo.get_list()
        self.assertEqual(len(lista), 1)
        self.assertEqual(lista[0].get_id_person(), 10)
        self.assertEqual(lista[0].get_id_eveniment(), 200)


        with self.assertRaises(Repo_error):
            self.repo.addinscriere(inscriere)

    def test_lista(self):

        self.assertEqual(len(self.repo.get_list()), 0)

        p1 = Participare(1, 100)
        p2 = Participare(2, 101)
        self.repo.addinscriere(p1)
        self.repo.addinscriere(p2)

        lista = self.repo.get_list()
        self.assertEqual(len(lista), 2)

        self.assertEqual(lista[0].get_id_person(), 1)
        self.assertEqual(lista[1].get_id_eveniment(), 101)