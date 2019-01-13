import serial
import matplotlib.pyplot as plt
from drawnow import *
import atexit

values = []

plt.ion()
cnt = 0

serialArduino = serial.Serial('COM5', 9600)

#####
#def SHtoCM(value):
#    dyst = value * 5 / 1023.0
#    if (dyst >= 0.4 and dyst < 0.5):
#        return (-200 * dyst + 160)
#    if (dyst >= 0.5 and dyst < 0.65):
#        return (-67 * dyst + 93)
#    if (dyst >= 0.65 and dyst < 0.75):
#        return (-100 * dyst + 115)
#    if (dyst >= 0.75 and dyst < 0.9):
#        return (-67 * dyst + 90);
#    if (dyst >= 0.9 and dyst < 1.3):
#        return (-25 * dyst + 52.5);
#    if (dyst >= 1.3 and dyst < 2.5):
#        return (-10 * dyst + 30);
#    else:
#        return 80

##########
def plotValues():
    plt.grid(True)
    plt.ylabel('Values')
    plt.plot(values, 'rx-', label='values')
    plt.legend(loc='upper right')


def doAtExit():
    serialArduino.close()
    print("Close serial")
    print("serialArduino.isOpen() = " + str(serialArduino.isOpen()))


atexit.register(doAtExit)

print("serialArduino.isOpen() = " + str(serialArduino.isOpen()))

# pre-load dummy data
for i in range(0, 26):
    values.append(0)

while True:
    while (serialArduino.inWaiting() == 0):
        pass
    print("readline()")
    valueRead = serialArduino.readline(500)

    # check if valid value can be casted
    try:
        valueInInt = int(valueRead)
        valueInCm=SHtoCM(valueInInt)

        print(valueInCm)

        if valueInCm >= 0:
            values.append(valueInCm)
            values.pop(0)
            drawnow(plotValues)


        else:
            print("Invalid! too large")
    except ValueError:
        print("Invalid! cannot cast")



