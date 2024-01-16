import tkinter as tk
import ctypes
import time
import threading



class launchpadinterface:

    def __init__(self, led_per_row=8,led_per_col=8):
        gridSize = 8

        sizeH = 1
        SizeW = 1

        self.buttons = []

        self.ui = tk.Tk()
        # ui = tk.Canvas(height=sizeH, width=SizeW)

        self.ui.title("Fake LED WALL")

        self.ui.grid()

        for i in range(led_per_row):
            for j in range(led_per_col):
                Btn = tk.Button(height=sizeH, width=SizeW, relief="flat",
                                bg='black', fg='black')
                Btn.grid(column=j, row=i, columnspan=1, rowspan=1)
                Btn.number = i * led_per_col + j
                self.buttons.append(Btn)

        self.ui.update()

    def __del__(self):
        self.ui.destroy()
    def ControlAll(self, colour):
        self.LedAllOn('black')

    def LedAllOn(self, colour):
        for button in self.buttons:
            button.configure(bg=colour)
        self.ui.update()

    def changeLED (self, LED_id, red, green, blue):
        if LED_id < len(self.buttons):
            self.buttons[LED_id].configure(bg=f"#{red:02x}{green:02x}{blue:02x}")
        self.ui.update()

    def updateLEDS(self, led_data, n_leds):
        for i in range(n_leds):
            self.buttons[i].configure(bg=f"#{led_data[i*3]:02x}{led_data[3*i+1]:02x}{led_data[3*i+2]:02x}")
        self.ui.update()


class LED_data(ctypes.Structure):
    _fields_=[("red", ctypes.c_uint8),
              ("green", ctypes.c_uint8),
              ("blue", ctypes.c_uint8)]

class LED_buffer(ctypes.Structure):
    pass

if __name__ == "__main__":
    testlib=ctypes.cdll.LoadLibrary("./build/python_test.so")

    n_cols = int.from_bytes(ctypes.c_uint16.in_dll(testlib, 'n_cols'), byteorder='little')
    n_rows = int.from_bytes(ctypes.c_uint16.in_dll(testlib, 'n_rows'), byteorder='little')
    n_leds = int.from_bytes(ctypes.c_uint16.in_dll(testlib, 'n_leds'), byteorder='little')
    frame_size = n_leds * 3

    LED_buffer._fields_ = [("data", ctypes.c_uint8*(3*n_leds))]

    window=launchpadinterface(n_rows, n_cols)

    #testlib.cycle_effects()

    led_data = LED_buffer.in_dll(testlib, 'led_buffer')
    while True:
        window.updateLEDS(led_data.data,n_leds)
        testlib.tx_led_buffer()
        time.sleep(0.1)



    pass

