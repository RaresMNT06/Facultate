import socket
import struct

SERVER_IP = "127.0.0.1"
PORT_TCP = 1235
IP_MEU = ("127.0.0.1")


def pasareasca(sir):
    rezultat = ""
    for ch in sir:
        rezultat += ch
        if ch.lower() in "aeiou":
            rezultat += "p" + ch
    return rezultat


port_udp = int(input("Port UDP : "))


u = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
u.bind(("0.0.0.0", port_udp))

t = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
t.connect((IP_MEU, PORT_TCP))
t.send(socket.inet_aton(IP_MEU))
t.send(struct.pack("!H", port_udp))
t.close()

print(f"{IP_MEU}:{port_udp}. Astepta siruri pe UDP...")


while True:
    date, srv_udp = u.recvfrom(1024)
    sir = date.decode()

    if sir == "STOP":
        print("Serverul a trimis STOP. Gata.")
        break

    print("Am primit:", sir)
    tradus = pasareasca(sir)
    print("Trimit inapoi:", tradus)
    u.sendto(tradus.encode(), srv_udp)


u.close()




