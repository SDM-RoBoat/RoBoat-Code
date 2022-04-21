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


# draws dots that repersent the location of each sonar
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
def process_point(sonar_number, value):
    (x, y), angle = get_model(sonar_number)

    # location of sensor
    x_value, y_value = convert.polar_rectangular(value, angle)

    x_total = x + x_value
    y_total = y - y_value

    return x_total, y_total


def process_sonar(sensor_data):
    sonar = []
    # sensor values
    for i in range(len(sensor_data)):
        if i > 10:
            print(F"Process_Sonar: Unable to map sonar # {i + 1}")
            exit(1)

        if sensor_data[i] != 0:
            x, y = process_point(i + 1, sensor_data[i] / 100)

            # note change i to 255 to see in image
            sonar.append([y, x, i])

    return sonar
