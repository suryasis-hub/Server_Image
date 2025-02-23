# Pistache HTTP Server for OpenCV Backend

## Overview
This project sets up a **Pistache HTTP server** to act as a backend for OpenCV image processing. The server handles incoming HTTP requests from a frontend, processes images, and returns responses.

## Prerequisites
Ensure you have the following dependencies installed:

### **1. Install Pistache (macOS - Homebrew)**
```sh
brew install pistache
```

### **2. Install OpenCV (if required)**
```sh
brew install opencv
```

### **3. Install Required Libraries**
```sh
brew install cmake make clang
```

---

## **Compilation & Execution**
### **Step 1: Compile the Server**
Use the following `clang++` command to compile the server:

```sh
clang++ -o server pistacheServer.cpp RequestHandler.cpp  external/loguru/loguru.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lpistache -lpthread -std=c++17
```

**Explanation of flags:**
- `-o server` → Output file named `server`
- `pistacheServer.cpp RequestHandler.cpp` → Source files
- `-I/opt/homebrew/include` → Include directory for Pistache
- `-L/opt/homebrew/lib` → Library directory for Pistache
- `-lpistache -lpthread` → Link Pistache and pthread
- `-std=c++17` → Use C++17 standard

### **Step 2: Run the Server**
After compilation, start the server by running:
```sh
./server
```
The server will start listening on `http://localhost:9081`.

---

## **API Endpoints**
### **1. Health Check**
**Request:**
```sh
curl -X GET http://localhost:9081/hello
```


## **Testing the Server**
### **Option 1: Using Curl**
```sh
curl -X GET http://localhost:9081/hello
```
```sh
curl -X POST http://localhost:9081/upload  -H "Content-Type: image/jpeg" --data-binary @"/Users/suryasispaul/Downloads/IMG_4238.jpg"
```


## **Future Enhancements**
- Add OpenCV processing functions to handle received images.
- Extend API for additional image processing tasks.
- Add authentication for secure API access.
