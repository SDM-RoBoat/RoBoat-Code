import serial


def serial_in():
    # collects all the serial in ques for both arduous
    # [[id, num_in_array, [data]], [id, num_in_array, [data]], [id, num_in_array, [data]]]
    serial_data = []

    # this would be one line of serial
    # copy and change name to read in a different line
    with serial.Serial('sd', 19200, time_out=1) as ser:
        temp = handle_one_serial(ser)
        serial_data.append(temp)

    return serial_data


def handle_one_serial(ser):
    serial_data = []
    while ser.read() != 's':
        print("Finding Message Start")
    print("Found Message")
    id_handle = ser.read()
    print(f"ID: {id_handle}")
    if id_handle == 'i':
        print("imu")
        data = imu(ser)
        serial_data.append((id_handle, data))
    elif id_handle == 's':
        print("sonar")
        data = sonar(ser)
        data = serial_data.append((id_handle, data))
    elif id_handle == 'l':
        print("lidar")
        data = lidar(ser)
        serial_data.append((id_handle, data))
    else:
        print(f"Could not find Id: {id_handle}")
        while ser.read() != 'e':
            print("Looking for end of message")
        print("Found End of message")

    return serial_data


def sonar(ser):
    size = ser.read()
    data = []

    for i in range(size):
        value = ser.read()
        data.append(int(value))

    if ser.read() != 'e':
        print("Issue reading data")

    return data


def imu(ser):
    size = ser.read()
    data = []

    for i in range(size):
        value = ser.read()
        data.append(int(value))

    if ser.read() != 'e':
        print("Issue reading data")

    return data


def lidar(ser):
    size = ser.read()
    data = []
    for i in range(size):
        x = ser.read(2)
        y = ser.read(2)
        t = ser.read()
        data.append([x, y, t])

    if ser.read() != 'e':
        print("Issue reading data")

    return data
