from Jetson.Serial.Serial_Out import serial_out
from Jetson.Serial.Serial_In import serial_in
from Jetson.Serial.Process_Serial import process_serial
import Serial.Serial_Out



from Jetson.Image.Get_Image import get_image
from Jetson.Image.Process_Image import process_image


import cv2
import numpy as np


fake_serial = [['s', [10, 20, 30, 40, 50, 60, 70, 80, 90, 10]],
               ['s', [10, 20, 30, 40, 50, 60, 70, 80, 90, 10]],
               ['i', [6, 5, 4, 3, 2, 1]],
               ['l', [[1, 2, 3], [4, 5, 6], [7, 8, 9]]]
               ]

image_size = (300, 300)
# unit in meters
length_per_side = (6, 6)


# def main():
#     print(process_serial(fake_serial))
#     # world = np.zeros([image_size[0], image_size[1]])
#     # for (x, y, i) in sonar:
#     #     world[x][y] = i
#     # cv2.imwrite('test.jpeg', world)
#     return 0

def main():
    ser = Serial()
    while True:
        ser.serial_out(12)


if __name__ == '__main__':
    main()
    # os.system("PAUSE")
