# prune-liberty-ccs

A tool to reduce the size of Liberty (`.lib`) files by pruning unnecessary Composite Current Source (CCS).


## Build Instructions

This project uses OpenSTA as a submodule.

**clone:**
```bash
git clone --recursive https://github.com/vs34/prune-liberty-ccs.git
cd prune-liberty-ccs
```
**Build using CMake:**
```bash
mkdir build
cd build
cmake ..
make
```


The executable `prune` will be created in the `build` directory.

## Usage

Run the tool by providing an input `.lib` file and an output destination.

```bash
./build/prune [input_file.lib] > [output_file.lib]
