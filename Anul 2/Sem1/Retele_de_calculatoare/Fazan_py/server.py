import os
import random
import signal
import socket
import struct
import sys


PORT_TCP = 1234
CUVINTE_START = ["fazan", "masina", "carte", "telefon", "pisica"]

def recv_all(c, n):
    data = b""
    while len(data) < n:
        bucata = c.recv(n - len(data))
        if not bucata:
            raise ConnectionError("clientul a inchis conexiunea")
        data += bucata
    return data


def cuvant_valid(anterior, cuvant):
    return len(cuvant) > 2 and cuvant.startswith(anterior[-2:])

def joaca(ip, port):
    """Jocul cu UN client, prin udp (ruleaza procesul copil)"""

    client = (ip, port)
    eticheta = f"{ip}:{port}"


    u = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    u.settimeout(120)

    anterior = random.choice(CUVINTE_START)
    u.sendto(anterior.encode(), client)
    print(f"[{eticheta}] Server -> {anterior}")

    while True:
        try:
            date, de_la = u.recvfrom(100)
        except socket.timeout:
            print(f"[{eticheta}] Clientul nu a raspuns la timp. Joc incheiat.")
            break

        cuvant = date.decode().strip().lower()
        print(f"[{eticheta}] Client -> {cuvant}")

        if cuvant == "stop":
            print(f"[{eticheta}] Clientul a abandonat. Joc incheiat.")
            break

        if not cuvant_valid(anterior, cuvant):
            print(f"[{eticheta}] Cuvant invalid de la client -> STOP")
            u.sendto(b"STOP", client)
            break
        anterior = cuvant

        print(f'[{eticheta}] Cuvantul serverului (incepe cu "{anterior[-2:]}"): ', end="", flush=True)
        al_meu = sys.stdin.readline().strip().lower()

        if not cuvant_valid(anterior, al_meu):
            print(f"[{eticheta}] Cuvantul serverului nu respecta regula -> STOP")
            u.sendto(b"STOP", client)
            break
        u.sendto(al_meu.encode(), client)
        anterior = al_meu

    u.close()

def main():
    signal.signal(signal.SIGINT, signal.SIG_DFL)

    # [SOCKET] + [BIND] + [LISTEN] TCP
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(("0.0.0.0", PORT_TCP))
    s.listen(5)

    while True:
        # [ACCEPT]
        print(f"Astept clienti pe TCP {PORT_TCP}...", flush=True)
        c, addr = s.accept()

        # [RECV] IP-ul (4 octeti) si portul UDP (2 octeti)
        try:
            ip = socket.inet_ntoa(recv_all(c, 4))
            port = struct.unpack("!H", recv_all(c, 2))[0]
        except ConnectionError:
            print("Client TCP fara date complete")
            c.close()
            continue
        c.close()
        print(f"Client nou: joc UDP cu {ip}:{port}", flush=True)

        # [FORK] un proces separat pentru fiecare client
        pid = os.fork()
        if pid == 0:
            # COPILUL
            joaca(ip, port)
            os._exit(0)

        # PARINTELE: se intoarce la accept


main()

