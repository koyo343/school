from machine import Pin
from utime import sleep, ticks_ms

led = Pin(17, Pin.OUT | Pin.IN)
switch = Pin(22, Pin.IN)
first = 0


def handler(pin):
    global first

    now = ticks_ms()
    if now - first < 500:
        return
    first = now

    sleep(0.1)
    if switch.value() == 0:
        return

    if led.value() == 0:
        led.value(1)
    else:
        led.value(0)

switch.irq(handler, Pin.IRQ_RISING)

while True:
    sleep(1)