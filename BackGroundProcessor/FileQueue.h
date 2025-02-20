#ifndef FILEQUEUE_H
#define FILEQUEUE_H

#include <iostream>
#include <fstream>
#include <string>
#include <optional>

class FileQueue : public IQueue {
private:
    std::string filePath;

public:
    FileQueue(const std::string& file) : filePath(file) {}
    
    void push(std::string imagePath) override {
        std::ofstream file(filePath, std::ios::app);
        if (!file) {
            std::cerr << "Error opening file for writing: " << filePath << std::endl;
            return;
        }
        file << imagePath << std::endl;
        file.close();
    }

    std::optional<std::string> pop() override {
        std::ifstream file(filePath);
        if (!file) {
            std::cerr << "Error opening file for reading: " << filePath << std::endl;
            return std::nullopt;
        }

        std::string firstLine;
        if (!std::getline(file, firstLine)) {
            file.close();
            return std::nullopt; 
        }

        std::string remainingLines;
        std::string line;
        while (std::getline(file, line)) {
            remainingLines += line + "\n";
        }
        file.close();

        std::ofstream outFile(filePath, std::ios::trunc);
        outFile << remainingLines;
        outFile.close();

        return firstLine;
    }

    bool isEmpty() override {
        std::ifstream file(filePath);
        return file.peek() == std::ifstream::traits_type::eof();
    }
};

#endif // FILEQUEUE_H
