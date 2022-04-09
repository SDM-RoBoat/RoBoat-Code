import numpy


def space(n):
    temp_spaces = "  "
    for x in range(n):
        temp_spaces += "  "
    return temp_spaces


def Start_World():
    temp = ""
    temp += "<sdf version='1.7'>\n"
    temp += space(0) + "<world name='default'>\n"
    return temp


def Sun():
    temp = ""
    temp += space(1) + "<light name='sun' type='directional'>\n"
    temp += space(2) + "<cast_shadows>1</cast_shadows>\n"
    temp += space(2) + "<pose>0 0 10 0 -0 0</pose>\n"
    temp += space(2) + "<diffuse>0.8 0.8 0.8 1</diffuse>\n"
    temp += space(2) + "<specular>0.2 0.2 0.2 1</specular>\n"
    temp += space(2) + "<attenuation>\n"
    temp += space(3) + "<range>1000</range>\n"
    temp += space(3) + "<constant>0.9</constant>\n"
    temp += space(3) + "<linear>0.01</linear>\n"
    temp += space(3) + "<quadratic>0.001</quadratic>\n"
    temp += space(2) + "</attenuation>\n"
    temp += space(2) + "<direction>-0.5 0.1 -0.9</direction>\n"
    temp += space(2) + "<spot>\n"
    temp += space(3) + "<inner_angle>0</inner_angle>\n"
    temp += space(3) + "<outer_angle>0</outer_angle>\n"
    temp += space(3) + "<falloff>0</falloff>\n"
    temp += space(2) + "</spot>\n"
    temp += space(1) + "</light>\n"
    return temp


def Ground_Plane():
    temp = ""
    temp += space(1) + "<model name='ground_plane'>\n"
    temp += space(2) + "<static>1</static>\n"
    temp += space(2) + "<link name='link'>\n"

    temp += space(3) + "<collision name='collision'>\n"
    temp += space(4) + "<geometry>\n"
    temp += space(5) + "<plane>\n"
    temp += space(6) + "<normal>0 0 1</normal>\n"
    temp += space(6) + "<size>100 100</size>\n"
    temp += space(5) + "</plane>\n"
    temp += space(4) + "</geometry>\n"
    temp += space(4) + "<surface>\n"
    temp += space(5) + "<contact>\n"
    temp += space(6) + "<collide_bitmask>65535</collide_bitmask>\n"
    temp += space(6) + "<ode/>\n"
    temp += space(5) + "</contact>\n"
    temp += space(5) + "<friction>\n"
    temp += space(6) + "<ode>\n"
    temp += space(7) + "<mu>100</mu>\n"
    temp += space(7) + "<mu2>50</mu2>\n"
    temp += space(6) + "</ode>\n"
    temp += space(6) + "<torsional>\n"
    temp += space(7) + "<ode/>\n"
    temp += space(6) + "</torsional>\n"
    temp += space(5) + "</friction>\n"
    temp += space(5) + "<bounce/>\n"
    temp += space(4) + "</surface>\n"
    temp += space(4) + "<max_contacts>10</max_contacts>\n"
    temp += space(3) + "</collision>\n"

    temp += space(3) + "<visual name='visual'>\n"
    temp += space(4) + "<cast_shadows>0</cast_shadows>\n"
    temp += space(4) + "<geometry>\n"
    temp += space(5) + "<plane>\n"
    temp += space(6) + "<normal>0 0 1</normal>\n"
    temp += space(6) + "<size>100 100</size>\n"
    temp += space(5) + "</plane>\n"
    temp += space(4) + "</geometry>\n"
    temp += space(4) + "<material>\n"
    temp += space(5) + "<script>\n"
    temp += space(6) + "<uri>file://media/materials/scripts/gazebo.material</uri>\n"
    temp += space(6) + "<name>Gazebo/Grey</name>\n"
    temp += space(5) + "</script>\n"
    temp += space(4) + "</material>\n"
    temp += space(3) + "</visual>\n"

    temp += space(3) + "<self_collide>0</self_collide>\n"
    temp += space(3) + "<enable_wind>0</enable_wind>\n"
    temp += space(3) + "<kinematic>0</kinematic>\n"

    temp += space(2) + "</link>\n"
    temp += space(1) + "</model>\n"

    return temp


def Other_World_Properties():
    temp = ""

    temp += space(1) + "<gravity>0 0 -9.8</gravity>\n"

    temp += space(1) + "<magnetic_field>6e-06 2.3e-05 -4.2e-05</magnetic_field>\n"

    temp += space(1) + "<atmosphere type='adiabatic'/>\n"

    temp += space(1) + "<physics type='ode'>\n"
    temp += space(2) + "<max_step_size>0.001</max_step_size>\n"
    temp += space(2) + "<real_time_factor>1</real_time_factor>\n"
    temp += space(2) + "<real_time_update_rate>1000</real_time_update_rate>\n"
    temp += space(1) + "</physics>\n"

    temp += space(1) + "<scene>\n"
    temp += space(2) + "<ambient>0.4 0.4 0.4 1</ambient>\n"
    temp += space(2) + "<background>0.7 0.7 0.7 1</background>\n"
    temp += space(1) + "<shadows>1</shadows>\n"
    temp += space(1) + "</scene>\n"

    temp += space(1) + "<wind/>\n"

    temp += space(1) + "<spherical_coordinates>\n"
    temp += space(2) + "<surface_model>EARTH_WGS84</surface_model>\n"
    temp += space(2) + "<latitude_deg>0</latitude_deg>\n"
    temp += space(2) + "<longitude_deg>0</longitude_deg>\n"
    temp += space(2) + "<elevation>0</elevation>\n"
    temp += space(2) + "<heading_deg>0</heading_deg>\n"
    temp += space(1) + "</spherical_coordinates>\n"

    return temp


def End_World():
    temp = ""
    temp += space(1) + "<gui fullscreen='0'>\n"
    temp += space(2) + "<camera name='user_camera'>\n"
    temp += space(3) + "<pose>69.1407 110.554 243.855 -0 1.14764 -2.21099</pose>\n"
    temp += space(3) + "<view_controller>orbit</view_controller>\n"
    temp += space(3) + "<projection_type>perspective</projection_type>\n"
    temp += space(2) + "</camera>\n"
    temp += space(1) + "</gui>\n"

    temp += space(0) + "</world>\n"
    temp += "</sdf>\n"

    return temp


# *_Properties = [Mass (lbm),
#                 Ixx(lbm in^2), Ixy(lbm in^2), Ixz(lbm in^2), Iyy(lbm in^2), Iyz(lbm in^2), Izz(lbm in^2),
#                 X-Offset(in), Y-Offset(in), Z-Offset(in), Roll-Offset(deg), Pitch-Offset(deg), Yaw-Offset(deg)]
NChannel_Lookup = {"NChannel_Green", "NChannel_Red"}
NChannel_properties = [106.390, 64988.199, -393.555, -0.015, 2999.45, -2.372, 64990.698, 0, 4, 0, 0, 0, 0]
A_0_Lookup = {"A-0-Red", "A-0-Blue", "A-0-Green", "A-0-Yellow"}
A_0_properties = [4.173, 39.822, 0, 0, 24.606, 0, 39.822, 0, 4, 0, 0, 0, 0]
A_2_Lookup = {"A-2-Red", "A-2-Green", "A-2-Blue", "A-2-Yellow"}
A_2_properties = [23.513, 645.402, 0, 0, 462.859, 0, 645.402, 0, 0, 0, 0, 0, 0]


def deg_rad_convert(deg):
    return deg/180*numpy.pi


def in_m_convert(inch):
    return inch * 0.0254


def ft_m_convert(ft):
    return ft * (1/3.0)


def lbm_N_convert(lbm):
    return lbm * 0.453592


def lbmin2_to_kgm2(lbmin2):
    return lbmin2 * 0.0002926397


def Convert_Metric_Properties(properties):
    i = 0
    for value in properties:
        if i == 0:
            properties[i] = lbm_N_convert(value)
        elif 0 < i < 7:
            properties[i] = lbmin2_to_kgm2(value)
        elif 7 <= i < 11:
            properties[i] = in_m_convert(value)
        else:
            properties[i] = deg_rad_convert(value)
        i += 1
    return properties


def Object_Properties(mesh_name):
    if mesh_name in NChannel_Lookup:
        return Convert_Metric_Properties(NChannel_properties)
    if mesh_name in A_0_Lookup:
        return Convert_Metric_Properties(A_0_properties)
    if mesh_name in A_2_Lookup:
        return Convert_Metric_Properties(A_2_properties)
    else:
        print(f"Properties for {mesh_name} does not exits")
        exit()


# Scale for in to m
SCALE_FACTOR_Mesh = 0.0254


# Code for Custom objects
def Object(object_name, mesh_name, pos):
    mass, \
        ixx, ixy, ixz, iyy, iyz, izz,\
        X_Offset, Y_Offset, Z_Offset, Roll_Offset, Pitch_Offset, Yaw_Offset = Object_Properties(mesh_name)

    # print(f"Mass: {mass}\n"
    #       f"ixx: {ixx}, ixy: {ixy}, ixz: {ixz}, iyy: {iyy}, iyz: {iyz}, izz: {izz}\n"
    #       f"X_Offset: {X_Offset}, Y_Offset: {Y_Offset}, Z-Offset: {Z_Offset}\n"
    #       f"Roll_Offset: {Roll_Offset}, Pitch_Offset: {Pitch_Offset}, Yaw_Offset: {Yaw_Offset}")

    # convert pos to meters
    for value in pos:
        value = ft_m_convert(value)

    temp = ""
    temp += space(1) + "<model name='" + object_name + "'>\n"
    temp += space(2) + "<link name='link'>\n"
    temp += space(3) + "<inertial>\n"
    temp += space(4) + "<pose>0 0 0 0 -0 0</pose>\n"
    temp += space(4) + f"<mass>{mass}</mass>\n"
    temp += space(4) + "<inertia>\n"
    temp += space(5) + f"<ixx>{ixx}</ixx>\n"
    temp += space(5) + f"<ixy>{ixy}</ixy>\n"
    temp += space(5) + f"<ixz>{ixz}</ixz>\n"
    temp += space(5) + f"<iyy>{iyy}</iyy>\n"
    temp += space(5) + f"<iyz>{iyz}</iyz>\n"
    temp += space(5) + f"<izz>{izz}</izz>\n"
    temp += space(4) + "</inertia>\n"
    temp += space(3) + "</inertial>\n"

    temp += space(3) + "<collision name='collision'>\n"
    temp += space(4) + f"<pose>{X_Offset} {Y_Offset} {Z_Offset} 0 0 0</pose>\n"
    temp += space(4) + "<geometry>\n"
    temp += space(5) + "<mesh>\n"
    temp += space(6) + "<uri>model://" + mesh_name + "/meshes/" + mesh_name + ".dae</uri>\n"
    temp += space(5) + "</mesh>\n"
    temp += space(4) + "</geometry>\n"
    temp += space(4) + "<surface>\n"
    temp += space(5) + "<friction>\n"
    temp += space(6) + "<ode>\n"
    temp += space(7) + "<mu>1</mu>\n"
    temp += space(7) + "<mu2>1</mu2>\n"
    temp += space(6) + "</ode>\n"
    temp += space(6) + "<torsional>\n"
    temp += space(7) + "<ode/>\n"
    temp += space(6) + "</torsional>\n"
    temp += space(5) + "</friction>\n"
    temp += space(5) + "<contact>\n"
    temp += space(6) + "<ode>\n"
    temp += space(7) + "<kp>1e+07</kp>\n"
    temp += space(7) + "<kd>1</kd>\n"
    temp += space(7) + "<min_depth>0.001</min_depth>\n"
    temp += space(7) + "<max_vel>0.1</max_vel>\n"
    temp += space(6) + "</ode>\n"
    temp += space(5) + "</contact>\n"
    temp += space(5) + "<bounce/>\n"
    temp += space(4) + "</surface>\n"
    temp += space(4) + "<max_contacts>10</max_contacts>\n"
    temp += space(3) + "</collision>\n"

    temp += space(3) + "<visual name='visual'>\n"
    temp += space(4) + f"<pose>{X_Offset} {Y_Offset} {Z_Offset} 0 0 0</pose>\n"
    temp += space(4) + "<geometry>\n"
    temp += space(5) + "<mesh>\n"
    temp += space(6) + "<uri>model://" + mesh_name + "/meshes/" + mesh_name + ".dae</uri>\n"
    # convert Mesh to meters
    temp += space(6) + f"<scale>{SCALE_FACTOR_Mesh} {SCALE_FACTOR_Mesh} {SCALE_FACTOR_Mesh}</scale>"
    temp += space(5) + "</mesh>\n"
    temp += space(4) + "</geometry>\n"
    temp += space(3) + "</visual>\n"

    temp += space(3) + "<self_collide>0</self_collide>\n"
    temp += space(3) + "<enable_wind>0</enable_wind>\n"
    temp += space(3) + "<kinematic>0</kinematic>\n"
    temp += space(2) + "</link>\n"
    temp += space(2) + f"<pose>{pos[0]} {pos[1]} {pos[2]} 0 0 0</pose>\n"
    temp += space(1) + "</model>\n"

    return temp


COLOR_LOOKUP = {"green": "Green",
                "red": "Red",
                "yellow": "Yellow",
                "blue": "Blue"}
TYPE_LOOKUP = {0: "A-0-",
               1: "A-2-",
               2: "NChannel_"}


Model_Usage = {}


def Create_Name(color, type_0):
    return TYPE_LOOKUP[type_0] + COLOR_LOOKUP[color]


def Generate_World_File(world):
    world_file = ""
    world_file += Start_World()
    world_file += Sun()
    world_file += Ground_Plane()
    world_file += Other_World_Properties()

    # add the list of buies stored int world to the world file string
    for item in world:
        # create unique object names
        object_name = Create_Name(item[0], item[2])
        if object_name in Model_Usage:
            Model_Usage[object_name] += 1
        else:
            Model_Usage[object_name] = 1

        # set up var for Object function
        mesh_name = object_name
        object_name += "_" + str(Model_Usage[object_name])
        pos = [item[1][0], item[1][1], 0]

        # append the Object to the world file string
        world_file += Object(object_name, mesh_name, pos)

    world_file += End_World()
    return world_file
