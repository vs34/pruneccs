# prune-liberty-ccs

A tool to reduce the size of Liberty (`.lib`) files by pruning unnecessary Composite Current Source (CCS) and power modeling data. It uses the OpenSTA parser and writer for robust handling of the Liberty format.


## Build Instructions

This project uses OpenSTA as a submodule.


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
./build/prune <input_file.lib> --outfile <output_file.lib>
