import serial
import socket

TCP_IP_CLIENT = '0.0.0.0'  # IP of client
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # creation of socket
TCP_PORT = 5005
BUFFER_SIZE = 1024 # make sure this is big enough to handle data

# make sure to unblock firewall communication if need be

# client
def serial_out(data):
    s.connect((TCP_IP_CLIENT, TCP_PORT))
    s.send(bytes(data, "utf-8"))
    s.close()
    # data will be
    # [[x, y, type, color], [x, y, type, color], [x, y, type, color]]
    # needs to sent to raspberry pi
    return 0



