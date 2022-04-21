import pygame
import random
import numpy as np
import os
from Software_Wolrd_Map.gazebo_world import Generate_World_File

display_width = 200
display_height = 250

xWorldOffset = 50
yWorldOffset = 50

worldSeed = 0


colors = {"red": (255, 0, 0),
          "green": (0, 255, 0),
          "yellow": (255, 255, 0),
          "blue": (0, 0, 255)}


class Spline:
    def __init__(self, args):
        self.l = len(args)
        m = []
        y = []
        for item in args:
            tempM = []
            for n in range(self.l):
                if n == 0:
                    tempM.append(1)
                else:
                    mid = item[0]
                    for x in range(n-1):
                        mid = mid * item[0]
                    tempM.append(mid)
            m.append(tempM)
            y.append([item[1]])
        self.M = np.array(m)
        self.Y = np.array(y)
        self.A = np.dot(np.linalg.inv(self.M), self.Y)

    def getPair(self, x):
        result = 0
        for i in range(self.l):
            result += self.A[i][0] * pow(x, i)
        return int(result)


# Navigation Channel
def NChannel(world):
    # starting positions
    # color, min xy, buoy type
    xStart = -3
    yStart = 0
    objects = [["green",   [0, 0],    [0, 0],   2],
               ["green",   [0, 25],  [0, 100],  2],
               ["red", [0, 0],     [6, 0],    2],
               ["red", [0, 25],   [6, 100],   2]]

    yOffset = random.randrange(0, 75, 1)
    xOffset = random.randrange(0, 3, 1)

    for b in objects:
        if (b[1][0] - b[2][0]) != 0:
            x = b[2][0] + xOffset + xStart
        else:
            x = 0 + xStart

        if (b[1][1] - b[2][1]) != 0:
            y = b[1][1] + yOffset + yStart
        else:
            y = 0 + yStart

        world.append([b[0], [x, y], b[3]])
    return world


def OChannel(world, NChannelBMaxY):
    worldSize = len(world)

    xStart = 0
    yStart = NChannelBMaxY + random.randrange(5, 15, 1)

    yOffset = random.randrange(0, 25, 1)
    xOffset = 3 + random.randrange(0, 2, 1)
    xMaxOffset = random.randrange(6, 10, 1)

    # note: [y,x]
    # used for generating spline
    objects = [["blue",   [0, 0], 0],
               ["blue", [(75+yOffset)*(1/3), xMaxOffset], 0],
               ["blue", [(75+yOffset)*(2/3), -xMaxOffset], 0],
               ["blue", [(75+yOffset), 0], 0]]

    # for item in objects:
    #     world.append([item[0], [item[1][1]+xStart, item[1][0]+yStart], 1])

    OC = Spline([objects[0][1], objects[1][1], objects[2][1], objects[3][1]])

    # side channels
    # generates green and red
    dots = 9
    step = objects[3][1][0]/(dots - 1)
    maxX = world[len(world)-2][1][0]
    minX = world[len(world)-3][1][0]
    i = 0
    while i < objects[3][1][0]:
        result = OC.getPair(i)
        world.append(["green", [result-xOffset+xStart, i+yStart], 0])
        world.append(["red", [result+xOffset+xStart, i+yStart], 0])
        i += step
        if maxX < result+xOffset+xStart:
            maxX = result+xOffset+xStart
        if minX > result-xOffset+xStart:
            minX = result-xOffset+xStart
    result = OC.getPair(objects[3][1][0])
    world.append(["green", [result - xOffset + xStart, objects[3][1][0] + yStart], 0])
    world.append(["red", [result + xOffset + xStart, objects[3][1][0] + yStart], 0])

    # generates yellow objects

    world.append(["yellow", [
        OC.getPair(((world[worldSize + 1][1][1] - yStart) + (world[worldSize + 2][1][1] - yStart)) / 2) + xStart,
        (((world[worldSize + 1][1][1] - yStart) + (world[worldSize + 2][1][1] - yStart)) / 2) + yStart], 0])
    world.append(["yellow", [
        OC.getPair(((world[worldSize + 7][1][1] - yStart) + (world[worldSize + 8][1][1] - yStart)) / 2) + xStart,
        (((world[worldSize + 7][1][1] - yStart) + (world[worldSize + 8][1][1] - yStart)) / 2) + yStart], 0])
    world.append(["yellow", [
        OC.getPair(((world[worldSize + 11][1][1] - yStart) + (world[worldSize + 12][1][1] - yStart)) / 2) + xStart,
        (((world[worldSize + 11][1][1] - yStart) + (world[worldSize + 12][1][1] - yStart)) / 2) + yStart], 0])
    world.append(["yellow", [
        OC.getPair(((world[worldSize + 15][1][1] - yStart) + (world[worldSize + 16][1][1] - yStart)) / 2) + xStart,
        (((world[worldSize + 15][1][1] - yStart) + (world[worldSize + 16][1][1] - yStart)) / 2) + yStart], 0])

    return [minX, maxX], world


def SGate(world, NChannelBMaxX, NChannelBMaxY, NChannelBMinY):
    xStart = NChannelBMaxX + random.randrange(10, 30, 1)
    yStart = (NChannelBMaxY-NChannelBMinY)/2 + NChannelBMinY
    yOffset = 3 + random.randrange(0, 2, 1)
    xOffset = random.randrange(3, 6, 1)
    markDistance = random.randrange(40, 100, 1)

    objects = [["green", [xOffset, -yOffset], 1],
               ["red", [xOffset, yOffset], 1],
               ["blue", [xOffset+markDistance, 0], 1]]
    for item in objects:
        world.append([item[0], [item[1][0]+xStart, item[1][1]+yStart], item[2]])
    return world


def DrawWorld(world_window, world):
    for item in world:
        pygame.draw.circle(world_window,
                           colors[item[0]],
                           ((item[1][0]+xWorldOffset),
                            display_height-(item[1][1]+yWorldOffset)),
                           2)
    pygame.display.update()


def generate_world(seed):
    world = []

    NChannelBMinX = 0
    NChannelBMaxX = 0
    NChannelBMinY = 0
    NChannelBMaxY = 0

    OChannelMinX = 0
    OChannelMaxX = 0
    OChannelMinY = 0
    OChannelMaxY = 0

    SGateMinX = 0
    SGateMaxX = 0
    SGateMinY = 0
    SGateMaxY = 0

    random.seed(seed)

    sizeofWorld = len(world)
    world = NChannel(world)
    NChannelBMinX = world[sizeofWorld + 0][1][0]
    NChannelBMaxX = world[sizeofWorld + 2][1][0]
    NChannelBMinY = world[sizeofWorld + 0][1][1]
    NChannelBMaxY = world[sizeofWorld + 1][1][1]
    print("NChannel: ", "MinX: ", NChannelBMinX, ", MaxX: ", NChannelBMaxX,
          "MinY: ", NChannelBMinY, ", MaxY: ", NChannelBMaxY)

    sizeofWorld = len(world)
    temp, world = OChannel(world, NChannelBMaxY)
    OChannelMinX = temp[0]
    OChannelMaxX = temp[1]
    OChannelMinY = world[sizeofWorld + 0][1][1]
    sizeofWorld = len(world)
    OChannelMaxY = world[sizeofWorld - 1][1][1]
    print("OChannel: ", "MinX: ", OChannelMinX, ", MaxX: ", OChannelMaxX,
          "MinY: ", OChannelMinY, ", MaxY: ", OChannelMaxY)

    sizeofWorld = len(world)
    world = SGate(world, NChannelBMaxX, NChannelBMaxY, NChannelBMinY)
    SGateMinX = world[sizeofWorld + 0][1][0]
    SGateMaxX = world[sizeofWorld + 2][1][0]
    SGateMinY = world[sizeofWorld + 0][1][1]
    SGateMaxY = world[sizeofWorld + 1][1][1]
    print("SGate: ", "MinX: ", SGateMinX, ", MaxX: ", SGateMaxX,
          "MinY: ", SGateMinY, ", MaxY: ", SGateMaxY)

    return world


if __name__ == '__main__':
    pygame.init()
    window = pygame.display.set_mode((display_width, display_height))
    pygame.display.set_caption('Map of filed')

    world_final = generate_world(worldSeed)

    Gazebo_World = Generate_World_File(world_final)

    Gazebo_World_File = open("RoboBoat_"+str(worldSeed)+".world", "w")
    Gazebo_World_File.write(Gazebo_World)
    Gazebo_World_File.close()

    DrawWorld(window, world_final)
    os.system("PAUSE")
    quit()
