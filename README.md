# Multitasking
COMPX203 kernel exercises for parallel and serial task scheduling in C and assembly.

## Project 🌳
```
.
├── kernel_q3.s
├── kernel_q4.s
├── parallel_entry.c
├── parallel_task.c
├── serial_entry.c
└── serial_task.c
```

### Usage
Compile on the lab machines using the course build environment:
```bash
gcc -o parallel parallel_entry.c parallel_task.c
gcc -o serial serial_entry.c serial_task.c
```

## Commands
1. To compile the parallel program use `gcc -o parallel parallel_entry.c parallel_task.c`.
2. To compile the serial program use `gcc -o serial serial_entry.c serial_task.c`.
