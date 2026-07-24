from Domain.domain_tractorrental import TractorRental

class TractorService:

    def __init__(self, repo):
        self.__repo = repo


    def search_by_consumption(self, max_consumption):
        tractors = self.__repo.getAll()
        result = []

        for t in tractors:
            if t.get_consumption() <= max_consumption:
                result.append(t)

        return result

    def rent_tractor(self, km_teren, zile):
        tractors = self.__repo.getAll()

        eligible = []
        for t in tractors:
            # Tractor potrivit doar dacă are autonomie suficientă
            if t.get_volume() / t.get_consumption() >= km_teren:
                eligible.append(t)

        # Dacă NU există tractor potrivit
        if len(eligible) == 0:
            return None

        # Alegem tractorul cu cel mai mic consum
        best = eligible[0]
        for t in eligible:
            if t.get_consumption() < best.get_consumption():
                best = t

        # Calculăm prețul total
        total_price = best.get_price() * zile

        # Ștergem tractorul închiriat din repo
        self.__repo.removeByNumber(best.get_number())

        # Returnăm un obiect TractorRental (nu tractor simplu!)
        rental = TractorRental(best, total_price)
        return rental