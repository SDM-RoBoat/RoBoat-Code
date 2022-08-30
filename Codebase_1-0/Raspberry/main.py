from Serial import Serial
import socket

# main testing function
def main():
    ser = Serial()
    while True:
        data = ser.serial_in()
        print(data.decode("utf-8"))
