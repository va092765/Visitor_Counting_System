# Interrupt-Driven Automatic Visitor Counting System

An embedded C project for the **LPC2129 (ARM7TDMI-S)** microcontroller that counts people entering and exiting a room using IR sensors, displays live occupancy on an LCD, and indicates presence with an LED — all driven by hardware interrupts rather than polling.

## Features

- Real-time entry/exit detection using external interrupts (EINT0 / EINT1)
- Live occupancy count shown on a 16x2 LCD (4-bit mode)
- Cumulative "total entered" count recallable via a push switch
- LED indicator that reflects whether anyone is currently inside
- Millisecond timebase from Timer0 for debounce/delay handling

## Hardware

| Component | Function |
|---|---|
| LPC2129 dev board | Core MCU |
| IR sensor 1 | Entry detection — EINT0 (P0.1) |
| IR sensor 2 | Exit detection — EINT1 (P0.3) |
| 16x2 LCD (4-bit mode) | Displays live count / entered count |
| Push switch | Shows cumulative entered count on demand |
| LED | ON while occupancy > 0, OFF when empty |

## Pin mapping

| Signal | Pin |
|---|---|
| LCD RS / EN / D4-D7 | P1.18 - P1.23 |
| LED | P1.16 |
| IR sensor 1 (entry) | P0.1 (EINT0) |
| IR sensor 2 (exit) | P0.3 (EINT1) |
| Switch | P0.14 |

## How it works

- Each sensor pulls its output line low when its IR beam is broken, triggering a falling-edge interrupt.
- The entry ISR increments both the live occupancy count and the cumulative entered count, and turns the LED on.
- The exit ISR decrements occupancy, and turns the LED off once it reaches zero.
- The main loop polls the switch; while held, the LCD shows the cumulative entered total instead of the live count.

## Known issues / in progress

- IR sensor chatter near the detection threshold can cause a single pass to register as multiple triggers; sensitivity potentiometer tuning and/or a software debounce lockout are being investigated.

## Toolchain

Built with Keil µVision for the LPC2129 (ARM7). Flash via the onboard ISP header.

## License

MIT
