from Jetson.Sonar.Sonar_Convert import process_sonar as sonar
from Jetson.IMU.Process_IMU import process_IMU as imu
from Jetson.Lidar.Process_Lidar import process_lidar as lidar


def process_serial(serial_data):
    data_sonar = []
    data_imu = []
    data_lidar = []
    for (id_handle, sensor_data) in serial_data:
        print(f"ID_Handle: {id_handle}, sensor_data: {sensor_data}")
        if id_handle == 's':
            temp = sonar(sensor_data)
            for obj in temp:
                data_sonar.append(obj)
        elif id_handle == 'i':
            temp = imu(sensor_data)
            data_imu.append(temp)
        elif id_handle == 'l':
            temp = lidar(sensor_data)
            for obj in temp:
                data_lidar.append(obj)
        else:
            print("Unreachable")

    return [data_sonar, data_imu, data_lidar]
