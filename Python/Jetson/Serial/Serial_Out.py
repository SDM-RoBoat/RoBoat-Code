import serial
import socket

TCP_IP_CLIENT = '0.0.0.0'  # IP of client
TCP_IP_SERVER = '0.0.0.0'  # IP of the server
s1, s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
TCP_PORT = 5005
BUFFER_SIZE = 1024
MESSAGE = "test!"

# make sure to unblock firewall communication if need be

# client


def serial_out(data):
    s1.connect((TCP_IP_CLIENT, TCP_PORT))
    # testing a quick message
    s1.send(MESSAGE)
    data = s1.recv(BUFFER_SIZE)
    s1.close()
    # data will be
    # [[x, y, type, color], [x, y, type, color], [x, y, type, color]]
    # needs to sent to raspberry pi
    return 0

# server


def serial_in():

    s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s2.bind((TCP_IP_SERVER, TCP_PORT))
    s2.listen(1)

    conn, addr = s2.accept()
    print('Connection address:', addr)
    while 1:
        received_data = conn.recv(BUFFER_SIZE)
        if not received_data:
            break
        print("received data:", received_data)
        conn.send(received_data)  # echo
    conn.close()
