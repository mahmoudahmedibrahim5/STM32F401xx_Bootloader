import serial

if __name__ == "__main__":
    val = 0
    ser = serial.Serial(port='COM4', baudrate=9600)
    while True:
        val = ser.read(1)
        print(val)