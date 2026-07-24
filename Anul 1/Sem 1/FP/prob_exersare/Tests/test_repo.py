import unittest
from Repo.repo_tractor import Repo_tractor

class TestRepoTractor(unittest.TestCase):

    def setUp(self):
        self.test_file = "test_tractoare.txt"

        with open(self.test_file, "w") as f:
            f.write("1,JohnDeere,verde,1.5,50,250\n")
            f.write("2,Case,rosu,2.2,40,200\n")

        self.repo = Repo_tractor(self.test_file)

    def tearDown(self):
        open(self.test_file, "w").close()

    def test_getAll(self):
        tractoare = self.repo.getAll()

        self.assertEqual(len(tractoare), 2)
        self.assertEqual(tractoare[0].get_number(), 1)
        self.assertEqual(tractoare[1].get_brand(), "Case")

    def test_removeByNumber(self):
        self.repo.removeByNumber(1)
        tractoare = self.repo.getAll()

        # trebuie să rămână doar tractorul 2
        self.assertEqual(len(tractoare), 1)
        self.assertEqual(tractoare[0].get_number(), 2)

        # verificăm și că fișierul a fost rescris corect
        with open(self.test_file, "r") as f:
            lines = f.readlines()

        self.assertEqual(len(lines), 1)
        self.assertTrue(lines[0].startswith("2,"))