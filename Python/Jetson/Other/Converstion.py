import numpy as np
import math as m


def deg_rad(deg):
    return deg * np.pi / 180


def ft_m(ft):
    return 0.3048*ft


def polar_rectangular(l, angle):
    x = l*m.cos(angle)
    y = l*m.sin(angle)
    return [x, y]


def rectangular_polar(x, y):
    r = np.sqrt(x*x + y*y)
    theda = np.arctan(y/x)
    return [r, theda]


# pixel is the number of pixels in an x or y direction
# length is the represented length in meters in an x or y direction
# value is the item to be converted
def meters_pixels(pixels, length, value):
    return int(value*(pixels/length))


def clip_pixel(pixel, max_pixel):
    if pixel < 0:
        return 0
    elif pixel >= max_pixel:
        return max_pixel-1
    else:
        return pixel


def scale(value, percent):
    return int(value*percent)


def translate(x, y, x_offset, y_offset):
    return x_offset+x, y_offset+y
