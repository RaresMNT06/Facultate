import socket
import struct

def recv_all(c , n):
    data = b""
    while len(data) < n:
        bucata = c.recv(n - len(data))
        if not bucata:
            raise ConnectionError("Connection closed by the server")
        data += bucata
    return data

# SOCKET
s =  socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# BIND
s.bind(("127.0.0.1", 1234))

#LISTEN
s.listen(5)

while True:
    #ACCEPT
    print("Waiting for connection")
    c, addr = s.accept()
    print("Connection from", addr)

    #RECV
    lungime = struct.unpack("!H", recv_all(c, 2))[0]
    sir = recv_all(c, lungime).decode()

    spatii = sir.count(" ")


    #SEND
    c.sendall(struct.pack("!H", spatii))


    c.close()
