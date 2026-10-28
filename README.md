# System Primitives

> A collection of low-level C and C++ system primitives focusing on raw memory manipulation, binary file I/O, and hardware-level execution.

## Repository Structure

```text
.
├── 01-bmp-grayscale/
│   ├── Samples/
│   │   ├── input.bmp
│   │   ├── output.bmp
│   │   └── sample.bmp
│   ├── TIL.txt
│   └── main.c
├── 02-wav-parser/
│   ├── Samples/
│   │   ├── input.wav
│   │   └── reversed.wav
│   └── main.c
└── README.md~~~

```

## Projects

### 1. BMP Grayscale Filter (01-bmp-grayscale)
Reads a raw .bmp image file, manually parses the 54-byte binary header, and manipulates the RGB byte values within the flat 1D pixel array to output a mathematically accurate grayscale image.

**How to run it:**
To run the filter, navigate to the project directory, compile the C source file, copy the sample input file from the Samples/ directory into your current working directory so the executable can read it, and then execute the program.

```cd 01-bmp-grayscale
gcc main.c -o run_grayscale
cp Samples/input.bmp .
./run_grayscale

```

### 2. WAV Audio Processor (02-wav-parser)
Parses the RIFF header of a .wav file to read, extract, and directly modify raw 16-bit stereo audio samples at the byte level.

**How to run it:**
To run the processor, navigate to the project directory, compile the C source file, copy the sample input file from the Samples/ directory into your current working directory, and then execute the program.

```cd 02-wav-parser
gcc main.c -o run_wav
cp Samples/input.wav .
./run_wav

```