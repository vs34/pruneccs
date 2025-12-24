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
```

## Testing

```bash
cd test
./regression
````

### Test Workflow

1.  **`prune_ccs`**: Runs `./build/prune` to generate pruned library for all CCS/normal library.
2.  **`check_prune`**: Validates that all CCS/SI groups have been removed from the output.
3.  **OpenSTA Verification**: Runs standard analysis (`delay_calc`, `power`,etc) on the pruned library to ensure NLDM timing and power data remain intact and accurate.


