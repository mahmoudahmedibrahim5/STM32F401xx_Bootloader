import serial

def sendFile():
    print("File")
    f = open('GreenLED.hex', 'r')
    lines = f.readlines()
    ser = serial.Serial(port="COM4", baudrate=9600)
    for i in lines:
        ser.write(i.encode("utf-8"))    

if __name__ == "__main__":
    print("Hello")
    sendFile()
    print("Finished")
    