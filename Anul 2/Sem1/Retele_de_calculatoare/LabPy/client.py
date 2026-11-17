import struct
import socket

def recv_all(s, n):
    data = b""
    while len(data) < n:
        bucata = s.recv(n - len(data))
        if not bucata:
            raise ConnectionError("serverul a inchis conexiunea")
        data += bucata
    return data

#[soket]
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#[connect]
s.connect(("127.0.0.1", 1234))

#[send]
n = int(input())
s.sendall(struct.pack("!H", n))

for i in range(n):
    x = int(input())
    s.sendall(struct.pack("!H", x))

#[recv]
suma = struct.unpack("!I", recv_all(s, 4))[0]
print("Suma este = ",suma)

s.close()