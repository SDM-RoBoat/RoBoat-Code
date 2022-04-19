import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((socket.gethostname(), 5005))

while True:
    data = s.recv(1024)
    print(data.decode("utf-8"))
