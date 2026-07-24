class Sedinte:

    def __init__(self, data, ora, subiect, stare):
        self.data = data
        self.ora = ora
        self.subiect = subiect
        self.stare = stare

    def get_data(self):
        return self.data
    def get_ora(self):
        return self.ora
    def get_subiect(self):
        return self.subiect
    def get_stare(self):
        return self.stare

    def set_data(self, data):
        self.data = data
    def set_ora(self, ora):
        self.ora = ora
    def set_subiect(self, subiect):
        self.subiect = subiect
    def set_stare(self, stare):
        self.stare = stare