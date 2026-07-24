import unittest
from Domain.domain_eveniment import Eveniment
from Domain.validator.validator_eveniment import Eveniment_Val
from Error.validator_error import Val_error


class TestValidatorEveniment(unittest.TestCase):

    def test_eveniment_validator_valid(self):
        ev = Eveniment(12, "2025-01-01", "10:00", "Conferinta")
        validator = Eveniment_Val(ev)

        #
        validator.validate_ev()

    def test_eveniment_validator_invalid_id(self):
        ev = Eveniment(1, "2025-01-01", "10:00", "Conferinta")
        validator = Eveniment_Val(ev)

        with self.assertRaises(Val_error):
            validator.validate_ev()

    def test_eveniment_validator_invalid_data(self):
        ev = Eveniment(12, "", "10:00", "Conferinta")
        validator = Eveniment_Val(ev)

        with self.assertRaises(Val_error):
            validator.validate_ev()

    def test_eveniment_validator_invalid_timp(self):
        ev = Eveniment(12, "2025-01-01", "", "Conferinta")
        validator = Eveniment_Val(ev)

        with self.assertRaises(Val_error):
            validator.validate_ev()

    def test_eveniment_validator_invalid_descriere(self):
        ev = Eveniment(12, "2025-01-01", "10:00", "")
        validator = Eveniment_Val(ev)

        with self.assertRaises(Val_error):
            validator.validate_ev()

