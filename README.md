# MultiCompress

MultiCompress is a C++ project providing a library and command-line tools for various data compression algorithms. Currently, it includes implementations for Run-Length Encoding (RLE) and Huffman coding. The project is built using CMake and includes unit tests using Google Test.

## Features

* **Run-Length Encoding (RLE):**
    * Efficiently compresses data with consecutive repeating characters.
    * Provides functions for both compression and decompression.
* **Huffman Coding:**
    * A statistical lossless data compression algorithm.
    * Assigns variable-length codes to input characters based on their frequency.
    * Includes functions for compression and decompression.
* **Library (`multicompress_lib`):**
    * Offers C++ APIs for integrating compression and decompression functionalities into other projects.
* **Command-Line Interface (CLI):**
    * Provides executable tools (`multicompress.exe` on Windows, `multicompress` on other platforms) to compress and decompress files directly from the command line.
* **Unit Tests:**
    * Comprehensive unit tests using Google Test to ensure the correctness and reliability of the compression and decompression algorithms.
* **CMake Build System:**
    * Uses CMake for cross-platform build configuration.

## Build Instructions

These instructions assume you have CMake installed on your system.

1.  **Clone the Repository (if you haven't already):**
    ```bash
    git clone <repository_url>
    cd MultiCompress
    ```

2.  **Create a Build Directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Configure the Project with CMake:**
    ```bash
    cmake ..
    ```
    * This command tells CMake to read the `CMakeLists.txt` file in the parent directory (`..`) and generate the necessary build files for your system (e.g., Makefiles on Linux/macOS, Visual Studio project files on Windows).

4.  **Build the Project:**

    * **On Linux/macOS (using Make):**
        ```bash
        make -j$(nproc)
        ```
        * `-j$(nproc)` compiles in parallel, which can significantly speed up the build process.

    * **On Windows (using MSBuild):**
        ```bash
        cmake --build . --config Release
        ```
        or for Debug build:
        ```bash
        cmake --build . --config Debug
        ```
        * The `.` refers to the current build directory.
        * `--config Release` or `--config Debug` specifies the build configuration.

    * **Using Visual Studio (if you generated a `.sln` file):**
        1.  Open the `MultiCompress.sln` file located in your `build` directory with Visual Studio.
        2.  Select the desired build configuration (Debug or Release) from the dropdown menu.
        3.  Build the solution (Build -> Build Solution).

## Running the Tests

The project includes unit tests built using Google Test. To run the tests:

1.  **Build the `multicompress_test` target:** Ensure that the `multicompress_test` executable is built successfully. This is usually done when you build the entire project.

2.  **Execute the test executable:**

    * **From the `build/Debug` or `build/Release` directory (depending on your build configuration):**

        ```bash
        ./multicompress_test  # On Linux/macOS
        multicompress_test.exe # On Windows
        ```

    * The output will show the results of the Google Test run, indicating which tests passed or failed.

## Using the Command-Line Interface (CLI)

After building the project, you will find the `multicompress` executable (or `multicompress.exe` on Windows) in your `build/Release` or `build/Debug` directory (depending on your build configuration).

**Usage:**

```bash
multicompress <command> [options]
