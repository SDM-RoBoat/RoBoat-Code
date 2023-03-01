import Jetson.Other.Converstion as convert
from Jetson.Sonar.Sonar_Convert import create_sensors
import numpy as np
import cv2


def Draw_Local_Map(sensors):
    # sonars
    j = 1
    # lidar

    # imu


def draw_Image(sonars, image_size, length_per_side):
    sonar_world = []

    temp = Convert_to_Pixels(sonars, image_size, length_per_side)

    # draws sonars
    for x, y in temp:
        x, y = convert.translate(x, y, int(image_size[0] / 2), int(image_size[1] / 2))
        sonar_world.append([y, x, 255])

    # center point
    x, y = 0, 0
    x, y = convert.translate(x, y, int(image_size[0] / 2), int(image_size[1] / 2))
    sonar_world.append([y, x, 100])

    # boat box
    box = create_box(image_size, length_per_side)
    for x, y in box:
        x, y = convert.translate(x, y, int(image_size[0] / 2), int(image_size[1] / 2))
        sonar_world.append([y, x, 255])

    # sensor locations
    sensors = create_sensors(image_size, length_per_side, 0.95)
    for x, y in sensors:
        x, y = convert.translate(x, y, int(image_size[0] / 2), int(image_size[1] / 2))
        sonar_world.append([y, x, 255])

    world = np.zeros([image_size[0], image_size[1]])
    for (x, y, i) in sonar_world:
        world[x][y] = i
    cv2.imwrite('test.jpeg', world)


def Convert_to_Pixels(sonars, image_size, length_per_side):
    # x, y = convert.translate(x, y, int(image_size[0] / 2), int(image_size[1] / 2))
    #
    # #model
    # x = convert.meters_pixels(image_size[0], length_per_side[0], x)
    # y = convert.meters_pixels(image_size[1], length_per_side[1], y)

    # if x_total >= image_size[0] or y_total >= image_size[1]:
    #     return 0, 0

    return []


# draws a box in the place where the boat would be
def create_box(image_size, length_per_side):
    box = []
    # dimensions of robot sonar sensors and orientations
    # vars in feet
    w = convert.ft_m(3)
    l = convert.ft_m(4)

    x_max_in_pixels = convert.meters_pixels(image_size[0], length_per_side[0], w)
    y_max_in_pixels = convert.meters_pixels(image_size[1], length_per_side[1], l)
    x_offset = int(-x_max_in_pixels / 2)
    y_offset = int(-y_max_in_pixels / 2)

    for x in range(x_max_in_pixels):
        for y in range(y_max_in_pixels):
            if x == x_max_in_pixels-1 or x == 0 or y == 0 or y == y_max_in_pixels-1:
                x_total = x + x_offset
                y_total = y + y_offset

                box.append((x_total, y_total))
    return box
