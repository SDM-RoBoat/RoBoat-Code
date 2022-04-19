import serial

class get_serial:
    length = 0

    def add_serial(self, port):
        self.length += 1
        self.ports[self.length] = port

    def serial_in(self):
        # collects all the serial in ques for both arduous
        # [[id, num_in_array, [data]], [id, num_in_array, [data]], [id, num_in_array, [data]]]
        serial_data = []

        # this would be one line of serial
        # copy and change name to read in a different line
        for i in range(1, self.length):
            with serial.Serial(self.ports[i], 19200, time_out=1) as ser:
                temp = self.handle_one_serial(ser)
                serial_data.append(temp)

        return serial_data

    def handle_one_serial(self, ser):
        serial_data = []
        while ser.read() != 's':
            print("Finding Message Start")
        print("Found Message")
        id_handle = ser.read()
        print(f"ID: {id_handle}")
        if id_handle == 'i':
            print("imu")
            data = self.imu(ser)
            serial_data.append((id_handle, data))
        elif id_handle == 's':
            print("sonar")
            data = self.sonar(ser)
            data = serial_data.append((id_handle, data))
        elif id_handle == 'l':
            print("lidar")
            data = self.lidar(ser)
            serial_data.append((id_handle, data))
        else:
            print(f"Could not find Id: {id_handle}")
            while ser.read() != 'e':
                print("Looking for end of message")
            print("Found End of message")

        return serial_data

    def sonar(ser):
        size = ser.read(2)
        data = []

        for i in range(size):
            value = ser.read(2)
            data.append(int(value))

        if ser.read() != 'e':
            print("Issue reading data")

        return data

    def imu(ser):
        size = ser.read(2)
        data = []

        for i in range(size):
            if (i < 3):
                value = ser.read(2) / 1000
            else:
                value = ser.read(2)

        data.append(int(value))

        if ser.read() != 'e':
            print("Issue reading data")

        return data

    def lidar(ser):
        size = ser.read(2)
        data = []
        for i in range(size):
            x = ser.read(2)
            y = ser.read(2)
            t = ser.read()
            data.append([x, y, t])

        if ser.read() != 'e':
            print("Issue reading data")

        return data
