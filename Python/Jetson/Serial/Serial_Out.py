import socket


# make sure to unblock firewall communication if need be

# client
def serial_out(data):

    TCP_IP_CLIENT = '0.0.0.0'  # IP of client
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # creation of socket
    TCP_PORT = 5005
    BUFFER_SIZE = 1024 # make sure this is big enough to handle data
    s.bind((TCP_IP_CLIENT, TCP_PORT))
    s.listen(5)

    while True:
        clientsocket, address = s.accept()
        print(f"Connection from {address} has been established!")
        clientsocket.send(bytes(data, "utf-8"))
        
    return 0




