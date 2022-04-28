class real_obj:
    def __init__(self, pos, t, color):
            (self.x, self.y) = pos
            self.t = t
            self.color = color


world = []

world.append(real_obj((1, 0), 2, "red"))
world.append(real_obj((1, 6), 2, "green"))
world.append(real_obj((3, 6), 1, "green"))
world.append(real_obj((3, 0), 2, "red"))
world.append(real_obj((3, 3), 1, "yellow"))
world.append(real_obj((8, 3), 2, "red"))


colest = []

temp_size = len(world)
for i in range(3):
    if i > temp_size:
        break
    obj = world[(temp_size-i)-1]
    colest.append(obj)

new_list = []

for new_obj in local_map:
    for old_obj in colest:
        bound = 5
        if old_obj.t == new_obj.t:
            if old_obj.c == new_obj.c:
                if old_obj.x-bound < new_obj.x < old_obj+bound:
                    if (smae for y):
                        object is the same

                        if not
                            new_list.append(new_obj)

for obj in new_list:
    world.append(obj)




def get_nearist(rag):
    x, y = get_location()
    for obj in world:
        if x > tol:
            if y > tol:

        r, theda = rect_polr(x-obj.x, y-obj.y)
        if r < rag:
            return obj



()
{}
[]

world = {5: obj, 6: obj}


try world[4]:
    found
except:
    pass


