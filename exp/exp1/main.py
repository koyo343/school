from machine import Pin
from utime import sleep

led = Pin(17, Pin.OUT)

while True:
  led.value(1)
  sleep(0.5)
  led.value(0)
  sleep(0.5)