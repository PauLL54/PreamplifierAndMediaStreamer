#!/usr/bin/env python

import RPi.GPIO as GPIO

PIN = 23

def main():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(PIN, GPIO.OUT)
    
    GPIO.output(PIN, GPIO.LOW)
    return 0

main()
