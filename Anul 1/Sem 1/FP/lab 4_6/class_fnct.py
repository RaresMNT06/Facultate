import math

def get_imag(x):
    return x.imag

def get_real(x):
    return x.real
def get_mod(x):
    mod = math.sqrt(get_real(x) ** 2 + get_imag(x) ** 2)
    return mod