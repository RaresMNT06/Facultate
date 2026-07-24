import unittest


from Service.tractor_service import TractorService
from Repo.repo_tractor import Repo_tractor

class TestTractorService(unittest.TestCase):

    def setUp(self):
        self.filename = "test_service.txt"

        # Creăm date de test
        with open(self.filename, "w") as f:
            f.write("1,JohnDeere,verde,1.5,50,250\n")   # cel mai economic
            f.write("2,Case,rosu,2.2,40,200\n")
            f.write("3,Fendt,albastru,3.0,20,300\n")   # autonomie mică

        self.repo = Repo_tractor(self.filename)
        self.service = TractorService(self.repo)

    def tearDown(self):
        open(self.filename, "w").close()

    def test_search_by_consumption(self):
        results = self.service.search_by_consumption(2.0)

        self.assertEqual(len(results), 1)
        self.assertEqual(results[0].get_number(), 1)


    def test_rent_tractor(self):
        rental = self.service.rent_tractor(20, 3)

        # Tractorul 1 are autonomie 50/1.5 = 33 (OK)
        self.assertIsNotNone(rental)
        self.assertEqual(rental.get_tractor().get_number(), 1)
        self.assertEqual(rental.get_tractor_price(), 750)  # 250 * 3

    def test_rent_removes_tractor(self):
        self.service.rent_tractor(20, 3)
        tractors = self.repo.getAll()

        numbers = [t.get_number() for t in tractors]

        # Tractorul 1 trebuie eliminat
        self.assertNotIn(1, numbers)
        self.assertEqual(len(numbers), 2)

    def test_no_eligible_tractor(self):
        # Niciun tractor nu poate parcurge 100 km
        rental = self.service.rent_tractor(100, 2)
        self.assertIsNone(rental)