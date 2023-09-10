import serial

ser = serial.Serial(port='COM4', baudrate=9600)

while True:
    value = input()
    ser.write(value.encode('ascii'))
