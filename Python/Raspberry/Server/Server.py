import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((socket.gethostname(), 5005))


#currently only printing so we can test connection and data received
while True:
    data = s.recv(1024)
    print(data.decode("utf-8"))
