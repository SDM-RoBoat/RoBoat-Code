import serial
import socket

TCP_IP_CLIENT = '0.0.0.0'  # IP of client
TCP_IP_SERVER = '0.0.0.0'  # IP of the server
s1, s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
TCP_PORT = 5005
BUFFER_SIZE = 1024


# make sure to unblock firewall communication if need be

# client


def serial_out(data):
    s1.connect((TCP_IP_CLIENT, TCP_PORT))

    # testing a quick message
    s1.send(bytes("test!", "utf-8"))
    s1.close()
    # data will be
    # [[x, y, type, color], [x, y, type, color], [x, y, type, color]]
    # needs to sent to raspberry pi
    return 0

# server


def serial_in():

    s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s2.bind((TCP_IP_SERVER, TCP_PORT))
    s2.listen(4)

    conn, addr = s2.accept()
    print('Connection address:', addr)
    while 1:
        data = conn.recv(BUFFER_SIZE)
        if not data:
            break
        print("received data: ", data.decode("utf-8"))
    conn.close()
