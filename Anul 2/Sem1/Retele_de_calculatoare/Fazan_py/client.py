import socket
import struct


SERVER_IP = '127.0.0.1'
PORT_TCP = 1234
IP_MEU = "127.0.0.1"

def cuvant_valid(anterior, cuvant):
    return len(cuvant) >= 2 and cuvant.startswith(anterior[-2:])

port_udp = int(input("Port UDP pe care ascult (ex. 5001): "))

# 1. [UDP] intai deschid socket-ul UDP, ca sa fiu gata cand imi scrie serverul
u = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
u.bind(("0.0.0.0", port_udp))
    
# 2. [TCP] ma conectez si trimit IP-ul (4 octeti) + portul UDP (2 octeti)
t = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
t.connect((SERVER_IP, PORT_TCP))
t.sendall(socket.inet_aton(IP_MEU))                 # "127.0.0.1" -> 4 octeti, ordinea retelei
t.sendall(struct.pack("!H", port_udp))
t.close()                                           # TCP-ul si-a facut treaba
print(f"Am trimis {IP_MEU}:{port_udp}. Astept cuvantul serverului pe UDP...")

# 3. [JOC prin UDP]
while True:
    date, srv_udp = u.recvfrom(100)                 # srv_udp = adresa de la care scrie serverul
    primit = date.decode()

    if primit == "STOP":
        print("Serverul a trimis STOP. Joc incheiat.")
        break
    print("Server:", primit)

    # citesc un cuvant pana respecta regula (sau "stop")
    while True:
        cuvant = input(f'Cuvantul tau (incepe cu "{primit[-2:]}", sau stop): ').strip().lower()
        if cuvant == "stop" or cuvant_valid(primit, cuvant):
            break
        print("Nu respecta regula, mai incearca.")

    u.sendto(cuvant.encode(), srv_udp)              # raspund la adresa de la care mi-a scris
    if cuvant == "stop":
        print("Ai abandonat. Joc incheiat.")
        break

u.close()