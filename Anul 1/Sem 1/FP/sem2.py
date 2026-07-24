def convert_str_to_int_list(s:str)->list:

    """
    Transforma un sir dat intr o lista de numere
    :param s: sirul de transformat, preconditiei: sir sub forma 1 2 3
    :return: lista de numere obtinute din sir
    """
    initial_list= s.split()
    number_list=[]
    for i in range (len(initial_list)):
        number_list.append(int(initial_list[i]))
    return number_list
   # for el in initial_list:
   #     print(el)
   # for index, el in enumerate(initial_list):
   #     print(el)

def read_list_ui():
    list_string = input("Introduceti lista:")
    list_on_nrs = convert_str_to_int_list(list_string)
    print(f"Lista curenta este: {list_on_nrs}")
    return list_on_nrs


def print_menu():
    print("1. Citire lista")
    print("2. Exit")

def run():
    while True:
        print_menu()
        option =input("Introduceti optiunea:")
        if option == '1':
            list_of_numbers = read_list_ui()
        elif option == '2':
            break
        elif option.upper() == 'p':
            print(f"Lista curenta este:")

run()