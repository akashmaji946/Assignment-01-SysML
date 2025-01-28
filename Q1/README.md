# Assignment-01 (E0-294: Systems for ML)

This assignment involves implementing and comparing different convolution methods for machine learning systems.

## Setup
Make sure you run the following commands in Linux to set up the tools used:
```sh
sudo apt update  
sudo apt install linux-tools-common linux-tools-generic build-essential  
sudo echo "kernel.perf_event_paranoid=-1" | sudo tee -a /etc/sysctl.conf  
sudo sysctl -p  
```

## Files

- `part01.cpp`: Contains the implementation of the naive convolution method using a 7-layer loop.
- `part02.cpp`: Contains the implementation of the toeplitz convolution method using a 4-layer loop.
- `Makefile`: Used to compile the source files and generate the executables.

## Compilation

To compile the source files, run the following command in the terminal:

```sh
make
```

This will generate the following executables:
```sh
part01
part02
checker
```
Note: always run the executables in the above order.

## Usage:
##### __part01:__
The `part01` executable performs the following tasks:

- initializes structures with random values.
- saves the initialized values to files for performance comparison and consistency.
- performs naive convolution using a 7-layer loop.
- saves the output to OUTPUT1.txt.

To run the `part01` executable, use the following command: `$ ./part01`

##### __part02:__
The `part02` executable performs similar tasks as part01 but includes different convolution method, that is toeplitz convolution.

The `part02` executable does the following tasks:
- read same data as used by naive implementation
- flatten the maps(toeplitz conversion)
- do toeplitz convolution on same data for output similarity
- save the output into OUTPUT2.txt

To run the `part02` executable, use the following command: `$ ./part02`


##### __checker:__
The `checker` executable is used to verify the correctness of the convolution outputs.

To run the `checker` executable, use the following command: `$ ./checker`

## Cleaning Up
To clean up the generated files, run the following command:
```sh
make clean
```
Note:
This will remove the executables and any output files generated during the execution.

Notes:
Ensure that all required dependencies and compilers are installed on your system.
Modify the Makefile if additional source files or compilation flags are needed.

## Contact:
###### Akash Maji
###### akashmaji@iisc.ac.in