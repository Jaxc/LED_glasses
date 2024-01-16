import tkinter as tk
import ctypes
import time
import threading
import numpy as np

from PIL import Image, ImageTk



class fake_wall:

    def __init__(self, led_per_row=8,led_per_col=8, change_callback=None, stop_callback=None, start_callback=None, step_callback = None, change_bpm_callback = None):
        gridSize = 8
        pixels_per_led = 20
        self.SizeH = led_per_col*pixels_per_led
        self.SizeW = led_per_row*pixels_per_led

        self.change_callback = change_callback
        self.stop_callback = stop_callback
        self.start_callback = start_callback
        self.step_callback = step_callback
        self.change_bpm_callback = change_bpm_callback

        self.ui = tk.Tk()
        self.ui.title("Fake LED WALL")

        self.buttons_frame = tk.Frame()
        self.callback_button = tk.Button(self.buttons_frame, text="Cycle Effects", command=self.change_callback)
        self.stop_button = tk.Button(self.buttons_frame, text="Stop", command=self.stop_callback)
        self.start_button = tk.Button(self.buttons_frame, text="Start", command=self.start_callback)
        self.step_button = tk.Button(self.buttons_frame, text="Step", command=self.step_callback)
        self.BPM_field = tk.Text(self.buttons_frame, width=7, height=1)
        self.change_BPM_button = tk.Button(self.buttons_frame, text="Change BPM", command=self.change_bpm_callback)

        self.BPM_field.insert(tk.END,"128")

        self.callback_button.pack(side = "left")
        self.start_button.pack(side = "left")
        self.stop_button.pack(side = "left")
        self.step_button.pack(side="left")
        self.BPM_field.pack(side="left")
        self.change_BPM_button.pack(side="left")

        self.canvas = tk.Canvas(self.ui, height=self.SizeW, width=self.SizeH)
        self.canvas.pack(fill="both", expand=True, side="top")

        self.buttons_frame.pack()





        self.ui.update()
    def __del__(self):
        self.ui.destroy()

    def get_bpm_field(self):
        text_input = self.BPM_field.get("1.0", tk.END)
        try:
            bpm = int(text_input)
        except:
            bpm = 128

        return bpm

    def poll_ui(self):
        self.image = self.canvas.create_image(0, 0, anchor='nw', image=self.tk_image)
        self.ui.update()


    def updateLEDS(self, led_data):

        for i in range(0, len(led_data) - 1, 3):
            led_data[i], led_data[i+1] = led_data[i+1], led_data[i]

        img_array = bytearray(led_data)

        PIL_image = Image.frombytes('RGB', (25, 15), img_array).convert('RGB')
        PIL_image = PIL_image.resize((self.SizeH, self.SizeW), Image.Resampling.NEAREST)
        self.tk_image = ImageTk.PhotoImage(PIL_image)

        #self.label = tk.Label(self.ui, image=tk_image)
        self.image = self.canvas.create_image(0, 0, anchor='nw', image=self.tk_image)
        self.ui.update()


class LED_data(ctypes.Structure):
    _fields_=[("red", ctypes.c_uint8),
              ("green", ctypes.c_uint8),
              ("blue", ctypes.c_uint8)]

class LED_buffer(ctypes.Structure):
    pass


class Led_wall_simulator:

    def __init__(self):
        self.testlib = ctypes.cdll.LoadLibrary("./build/python_test.so")

        self.n_cols = int.from_bytes(ctypes.c_uint16.in_dll(self.testlib, 'n_cols'), byteorder='little')
        self.n_rows = int.from_bytes(ctypes.c_uint16.in_dll(self.testlib, 'n_rows'), byteorder='little')
        self.n_leds = int.from_bytes(ctypes.c_uint16.in_dll(self.testlib, 'n_leds'), byteorder='little')

        LED_buffer._fields_ = [("data", ctypes.c_uint8 * (3 * self.n_leds))]

        self.window = fake_wall(self.n_rows, self.n_cols, change_callback=self.cycle_effects, stop_callback=self.stop_running, start_callback=self.start_running, step_callback = self.step_effect, change_bpm_callback = self.change_bpm)
        self.testlib.led_initialization()
        # testlib.cycle_effects()

        self.led_data = LED_buffer.in_dll(self.testlib, 'led_buffer')
        self.beat_start_time = time.time()
        self.bpm = 128
        self.keep_running = True
        self.led_data = LED_buffer.in_dll(self.testlib, 'led_buffer')
    def update(self):
        if (time.time() - self.beat_start_time > (1.0/(self.bpm/60))):
            self.testlib.beat_start()
            self.beat_start_time = time.time()

        self.testlib.tx_led_buffer()
        self.window.updateLEDS(self.led_data.data)


        if self.keep_running:
            time.sleep(1/15)
        else:
            while self.keep_running is not True:
                self.window.poll_ui()


    def stop_running(self):
        self.keep_running = False

    def start_running(self):
        self.keep_running = True
    def cycle_effects(self):
        self.testlib.cycle_effects()

    def step_effect(self):
        if self.keep_running is not True:
            self.testlib.tx_led_buffer()
            self.window.updateLEDS(self.led_data.data)

    def change_bpm(self):
        self.bpm = self.window.get_bpm_field()



if __name__ == "__main__":

    fake_wall = Led_wall_simulator()

    while True:
        fake_wall.update()


    pass

