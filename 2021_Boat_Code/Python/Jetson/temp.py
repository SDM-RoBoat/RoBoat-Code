import numpy as np

from Software_Wolrd_Map.main import generate_world
import Jetson.Other.Converstion as convert
from Jetson.Sonar.Sonar_Convert import get_model

# this file is ment to simmulate accutal data from the boat (hand caculated)


# rangeLidar [meters], rangeSonar[cm], pos[m]
# IMU = [x, y, z, roll, yaw, pitch]
def get_fake_serial_data(seed, rangeLidar, rangeSonar, pos, IMU):
    world_software = generate_world(seed)
    print(world_software)

    serial = []

    Lidar = []
    Sonar = []
    pos[0] = convert.ft_m(pos[0])
    pos[1] = convert.ft_m(pos[1])

    for color, (x, y), _ in world_software:

        x = convert.ft_m(x)
        y = convert.ft_m(y)

        x_temp = x
        y_temp = y
        x, y = convert.translate(x, y, -pos[0], -pos[1])
        # print(f"Convert: Color: {color} || x {x_temp} | y {y_temp} | pos[0]: {pos[0]} | pos[1]: {pos[1]} >>> x {x} | y {y}")
        if x == 0:
            x += 0.001
        if y == 0:
            y += 0.001

        r, theda = convert.rectangular_polar(x, y)

        print(f"Color: {color} | X = {x}, Y = {y} | r = {r}")
        if r <= rangeLidar:
            Lidar.append((x, y, r))
            print(f"Sonar: {r} <= {rangeSonar[1]/100}\n")
            if r <= rangeSonar[1]/100:
                Sonar.append((r, theda))

    print(f"Sonar: {Sonar}\n"
          f"Lidar: {Lidar}")

    serial.append(["i", IMU])

    for (x, y, r) in Lidar:
        t = 0
        if r < rangeLidar/3:
            t = 1
        elif r < rangeLidar - rangeLidar/3:
            t = 2
        else:
            t = 3

        serial.append(["l", [x, y, t]])

    temp = [0]*10
    print(temp)
    for (r, theda) in Sonar:
        d = int(np.floor(theda / (np.pi/10)))
    print(f"Temp: {temp}")
    serial.append(['s', temp])


    print(serial)





# def get_fake_serial_data(seed, rangeLidar, rangeSonar, pos, IMU)

get_fake_serial_data(0, 9, [3, 80], [6, 84.1875], [0, 0, 0, 0, 0, 0])
