import socket


# make sure to unblock firewall communication if need be

# client
class Serial:
    def __init__(self):
        # creates a socket and connects it to specified IP and PORT
        self.s = socket.socket()
        self.s.connect(('0.0.0.0', 5005))

    def serial_out(self, data):
        # obtain data here
        self.s.send(data)



