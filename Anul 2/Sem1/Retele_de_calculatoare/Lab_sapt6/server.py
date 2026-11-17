import os
import signal
import socket
import struct
import sys

PORT_TCP = 1235


def recv_all(c, n):
    data = b""
    while len(data) < n:
        bucata = c.recv(n - len(data))
        if not bucata:
            raise ConnectionError("clientul a inchis conexiunea")
        data += bucata
    return data



def pasareasca(sir):
    rezultat  = ""
    for ch in sir:
        rezultat += ch
        if ch.lower() in "aeiou":
            rezultat += "p" + ch
    return rezultat


def comunica(ip, port):

    client = (ip, port)

    u = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    while True:

        sir = sys.stdin.readline().strip()

        u.sendto(sir.encode(), client)
        if sir == "STOP":
            print(f"[{ip}:{port}] Stop clientul respectiv")
            break

        date, de_la = u.recvfrom(1024)
        tradus = date.decode()
        print(f"[{ip}:{port}] Client -> {tradus}")

        if tradus == pasareasca(sir):
            print(f"[{ip}:{port}] Traducere corecta")
        else:
            print(f"[{ip}:{port}] Traducere gresita")

    u.close()


def main():

    signal.signal(signal.SIGCHLD, signal.SIG_IGN)

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(("0.0.0.0", PORT_TCP))
    s.listen(5)


    while True:
        print(f"Astept clienti ... ", flush=True)
        c, addr = s.accept()

        try:
            ip = socket.inet_ntoa(recv_all(c, 4))
            port = struct.unpack("!H", recv_all(c, 2))[0]
        except ConnectionError:
            print("Client TCP fara date complete")
            c.close()
            continue
        c.close()

        print(f"Client: comunica cu {ip}:{port} prin UDP", flush=True)


        pid = os.fork()
        if pid == 0:
            s.close()
            comunica(ip, port)
            os._exit(0)



main()





