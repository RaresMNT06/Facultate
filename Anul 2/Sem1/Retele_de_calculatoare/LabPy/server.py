import socket    # socket, bind, listen, accept, recv, sendall
import struct    # pack / unpack: numere <-> octeți

def recv_all(c, n):
    data = b""                              # sir de octeti
    while len(data) < n:                    # pana am toti cei n octeti
        bucata = c.recv(n- len(data))       # cer cat imi mai lipseste
        if not bucata:                      # cealalta parte a inchis
            raise ConnectionError("Connection closed by the server")
        data += bucata
    return data


# [soket]
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)#refoloire port

#[bind]
s.bind(("0.0.0.0", 1234))

#[listen]
s.listen(5)

while True:
    #[accept]
    print("Serverul asteapta clienti ...")
    c, addr = s.accept()        # blocheaza pana vine un client
    print("S-a conectat", addr)

    #[recv]
    n = struct.unpack("!H", recv_all(c, 2))[0]

    suma = 0
    for i in range(n):
        x = struct.unpack("!H", recv_all(c, 2))[0]
        print("  am primit", x)
        suma += x


    #[send]
    c.sendall(struct.pack("!I", suma))
    c.close()