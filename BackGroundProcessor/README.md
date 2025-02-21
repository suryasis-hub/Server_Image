This contains the background processor for the image processing unit
# Background Processor

## Overview
The **Background Processor** is a simple C++ application designed for processing tasks in the background. It is compiled using **Clang++** with C++17 support.

## Prerequisites
Ensure you have the necessary dependencies installed:

```sh
brew install llvm  # macOS
sudo apt install clang  # Linux
```

## Compilation
Compile the Background Processor using:

```sh
clang++ -I../external/loguru -o BackgroundProcessor4 main.cpp ../external/loguru/loguru.cpp -std=c++17
```

## Running the Application
Run the compiled binary:

```sh
./BackGroundProcessor
```
