import serial
from tkinter import filedialog

def GET_VERSION():
    print("\n************************** GET VERSION ************************** \n")
    ser.write("1".encode())
    for i in range(3):
        print(ser.readline().decode(), end="")
    print("")

def GET_HELP():
    print("\n************************** GET HELP ************************** \n")
    ser.write("2".encode())
    print(ser.readline().decode())
  
def MASS_ERASE():
    ser.write("3".encode())  
    
def SECTOR_ERASE():
    sector = 0
    while ((sector == 0) | (sector > 7)):
        print("Enter the number of sector to be erased: ")
        sector = int(input())
        if sector>7:
            print("Invalid Sector number")
    print("Sector %d to be erased" %(sector))
    ser.write("4".encode())
    ack = ser.readline().decode()
    ser.write(str(sector).encode())
    print("Sector %d has been erased\n" %(sector))

def FLASH_WRITE():
    file_path = filedialog.askopenfilename()
    f = open(file_path, "r")
    lines = f.readlines()
    f.close()
    ser.write("5".encode())
    ser.write(str(lines[1]).encode())
    print(lines[1])
    
def EXIT():
    ser.write("0".encode())


if __name__ == "__main__":
    print("Welcome To Bootloader")
    print("Enter The name of The port")
    com = input()
    
    ser = serial.Serial(port=com, baudrate=9600)
    print("\nPort Opened Succesufully")
    print("Waiting for the mcu to say Hello\n")
    print(ser.readline().decode())
    
    while True:
        print("********** Bootloader Command List **********\n")
        print("1- BL_GET_VERSION")
        print("2- BL_GET_HELP")
        print("3- BL_MASS_ERASE")
        print("4- BL_SECTOR_ERASE")
        print("5- BL_FLASH_WRITE")
        print("\n0- Exit\n")
        
        print("Enter the number of the command : ")
        option = int(input())
        
        if(option == 1):
            GET_VERSION()
        elif(option == 2):
            GET_HELP()
        elif(option == 3):
            MASS_ERASE()
        elif(option == 4):
            SECTOR_ERASE()
        elif(option == 5):
            FLASH_WRITE()
        elif(option == 0):
            EXIT()
            break
        else:
            print("Invalid Command Number\n")
    