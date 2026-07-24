import unittest
from Domain.domain_person import Person
from Domain.validator.validator_persoana import Person_Val
from Error.validator_error import Val_error


class TestValidatorPersoana(unittest.TestCase):

    def test_person_validator_valid(self):
        p = Person(12, "Ana", "Cluj")
        validator = Person_Val(p)


        validator.validate()

    def test_person_validator_invalid_name_contains_digits(self):
        p = Person(12, "An4", "Cluj")
        validator = Person_Val(p)

        with self.assertRaises(Val_error):
            validator.validate()

    def test_person_validator_invalid_name_empty(self):
        p = Person(12, "", "Cluj")
        validator = Person_Val(p)

        with self.assertRaises(Val_error):
            validator.validate()

    def test_person_validator_invalid_address_empty(self):
        p = Person(12, "Ana", "")
        validator = Person_Val(p)

        with self.assertRaises(Val_error):
            validator.validate()

    def test_person_validator_invalid_id(self):
        p = Person(1, "Ana", "Cluj")
        validator = Person_Val(p)

        with self.assertRaises(Val_error):
            validator.validate()


