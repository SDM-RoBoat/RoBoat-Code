from Jetson.Serial.Serial_Out import serial_out
from Jetson.Serial.Serial_In import serial_in


from Jetson.Sonar.Sonar_Convert import process_sonar
from Jetson.Image.Get_Image import get_image
from Jetson.Image.Process_Image import process_image


import cv2
import numpy as np

Fake_Data = (10, 20, 30, 40, 50, 60, 70, 80, 90, 500)

image_size = (300, 300)
# unit in meters
length_per_side = (6, 6)


def main():

    sonar = process_sonar(image_size, length_per_side, Fake_Data)
    print(f"Data: {sonar}")

    world = np.zeros([image_size[0], image_size[1]])
    for (x, y, i) in sonar:
        world[x][y] = i
    cv2.imwrite('test.jpeg', world)

    return 0


if __name__ == '__main__':
    main()
    # os.system("PAUSE")
