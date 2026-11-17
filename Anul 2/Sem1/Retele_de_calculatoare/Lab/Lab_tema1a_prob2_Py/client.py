import socket
import struct

def recv_all(s, n):
    data = b''
    while len(data) < n:
        bucata = s.recv(n- len(data))
        if not bucata:
            raise ConnectionError("Connection closed")
        data += bucata
    return data

# SOCKET
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# CONNECT
s.connect(('127.0.0.1', 1234))

# SEND
sir = input("Introduceti sirul: ")
date = sir.encode()   #  date = b"ana are mere"      text - octeti

s.sendall(struct.pack("!H", len(date)))
s.sendall(date)

#RECV
spatii = struct.unpack("!H", recv_all(s, 2))[0]
print("nr de spatii" , spatii)

s.close()