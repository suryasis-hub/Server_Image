#ifndef FILEQUEUE_H
#define FILEQUEUE_H

#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <optional>

#include "ImageOperation.h"
#include "../external/loguru/loguru.hpp"

class FileQueue : public IQueue {
private:
    std::string filePath;

public:
    FileQueue(const std::string& file) : filePath(file) 
    {
        LOG_F(INFO, "FileQueue initialized with file path: %s", filePath.c_str());
    }
    
    void push(const ImageOperationPair &imageOperationPair) override 
    {
        std::ofstream file(filePath, std::ios::app);
        if (!file) {
            LOG_F(ERROR, "Error opening file for writing: %s", filePath.c_str());
            return;
        }
        file << imageOperationPair.filePath <<" "<<operationTypeToString(imageOperationPair.operationType)<<std::endl;
        file.close();
        LOG_F(INFO, "Pushed image path to queue: %s with operation %s", imageOperationPair.filePath.c_str(), operationTypeToString(imageOperationPair.operationType).c_str());
    }

    ImageOperationPair parse(const std::string &firstLine) 
    {
        std::istringstream stream(firstLine);
        std::string imagePath, operationStr;
        
        if (!(stream >> imagePath >> operationStr)) 
        {
            LOG_F(ERROR, "Error parsing queue entry: %s", firstLine.c_str());
            return {"", OperationType::UNKNOWN};
        }

        return {imagePath, stringToOperationType(operationStr)};
    }

    std::optional<ImageOperationPair> pop() override 
    {
        std::ifstream file(filePath);
        if (!file) {
            LOG_F(ERROR, "Error opening file for reading: %s", filePath.c_str());
            return std::nullopt;
        }

        std::string firstLine;
        if (!std::getline(file, firstLine)) {
            file.close();
            LOG_F(WARNING, "Queue is empty, nothing to pop.");
            return std::nullopt;
        }

        std::string remainingLines;
        std::string line;
        while (std::getline(file, line)) {
            remainingLines += line + "\n";
        }
        file.close();

        std::ofstream outFile(filePath, std::ios::trunc);
        if (!outFile) {
            LOG_F(ERROR, "Error opening file for writing after pop: %s", filePath.c_str());
            return std::nullopt;
        }
        outFile << remainingLines;
        outFile.close();

        LOG_F(INFO, "Popped image path from queue: %s", firstLine.c_str());
        return parse(firstLine);
    }

    bool isEmpty() override 
    {
        std::ifstream file(filePath);
        bool empty = file.peek() == std::ifstream::traits_type::eof();
        file.close();
        LOG_F(INFO, "Queue is %s", empty ? "empty" : "not empty");
        return empty;
    }
};

#endif // FILEQUEUE_H
