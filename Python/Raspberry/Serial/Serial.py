import socket

class Serial:
    def __init__(self):
        # creates a socket and connects it to specified IP and PORT
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.bind((socket.gethostname(), 5005))
        self.s.listen(5)

    def serial_in(self):
        # obtain data here
        clientsocket, address = self.s.accept()
        print(f"Connection from {address} has been established!")
        data = clientsocket.recv(1024)
        return data