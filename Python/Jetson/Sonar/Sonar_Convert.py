import Jetson.Other.Converstion as convert


# returns [(x-offset, y-offset), angle] in meters and rads
def get_model(sensor_num):
    # dimensions of robot sonar sensors and orientations
    # vars in feet
    w = 3
    l = 4
    a = 1.5
    b = 1 / 3

    # documented
    data = {1: [(-w / 2, (l / 2) - b - 2 * a), 180],
            2: [(-w / 2, (l / 2) - b - a), 180],
            3: [(-w / 2, (l / 2) - b), 180],
            4: [(-w / 2, l / 2), 135],
            5: [(0, l / 2), 90],
            6: [(w / 2, l / 2), 45],
            7: [(w / 2, (l / 2) - b), 0],
            8: [(w / 2, (l / 2) - b - a), 0],
            9: [(w / 2, (l / 2) - b - 2 * a), 0],
            10: [(0, -l / 2), 270],
            }

    temp = data[sensor_num]

    return [(convert.ft_m(temp[0][0]), -convert.ft_m(temp[0][1])), convert.deg_rad(temp[1])]


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


def create_sensors(image_size, length_per_side, scale):
    sensors = []

    for i in range(10):
        (x, y), angle = get_model(i+1)
        x = convert.meters_pixels(image_size[0], length_per_side[0], x)
        y = convert.meters_pixels(image_size[1], length_per_side[1], y)
        x = convert.scale(x, scale)
        y = convert.scale(y, scale)
        sensors.append((x, y))
    return sensors


# (pixel, pixel), meter, #, meter
def process_point(image_size, length_per_side, sonar_number, value):
    (x, y), angle = get_model(sonar_number)
    x = convert.meters_pixels(image_size[0], length_per_side[0], x)
    y = convert.meters_pixels(image_size[1], length_per_side[1], y)

    # location of sensor
    x_value, y_value = convert.polar_rectangular(value, angle)
    x_value = convert.meters_pixels(image_size[0], length_per_side[0], x_value)
    y_value = convert.meters_pixels(image_size[1], length_per_side[1], y_value)

    x_total = x + x_value
    y_total = y - y_value

    if x_total >= image_size[0] or y_total >= image_size[1]:
        return 0, 0
    return x_total, y_total


def process_sonar(image_size, length_per_side, args):
    sonar = []
    # sensor values
    for i in range(len(args)):
        if i > 10:
            print(F"Process_Sonar: Unable to map sonar # {i + 1}")
            exit(1)

        if args[i] != 0:
            x, y = process_point(image_size, length_per_side, i+1, args[i]/100)
            x, y = convert.translate(x, y, int(image_size[0] / 2), int(image_size[1] / 2))

            if 0 <= x < image_size[0]:
                if 0 <= y < image_size[1]:
                    # note change i to 255 to see in image
                    sonar.append([y, x, i])
    # debug code don't delete

    # center point
    # x, y = 0, 0
    # x, y = convert.translate(x, y, int(image_size[0] / 2), int(image_size[1] / 2))
    # sonar.append([y, x, 100])

    # boat box
    # box = create_box(image_size, length_per_side)
    # for x, y in box:
    #     x, y = convert.translate(x, y, int(image_size[0]/2), int(image_size[1]/2))
    #     sonar.append([y, x, 255])

    # sensor locations
    # sensors = create_sensors(image_size, length_per_side, 0.95)
    # for x, y in sensors:
    #     x, y = convert.translate(x, y, int(image_size[0] / 2), int(image_size[1] / 2))
    #     sonar.append([y, x, 255])

    return sonar
