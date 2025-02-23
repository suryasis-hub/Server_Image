#ifndef IMAGE_OPERATION_H
#define IMAGE_OPERATION_H

#include "OperationType.h"


struct ImageOperationPair
{
    std::string filePath;
    OperationType operationType;
};

OperationType stringToOperationType(const std::string &opStr) 
{
    if (opStr == "COPY") return OperationType::COPY;
    if (opStr == "RESIZE") return OperationType::RESIZE;
    if (opStr == "COMPRESS") return OperationType::COMPRESS;
    return OperationType::UNKNOWN;
}

std::string operationTypeToString(OperationType opType) 
{
    switch (opType) {
        case OperationType::COPY: return "COPY";
        case OperationType::RESIZE: return "RESIZE";
        case OperationType::COMPRESS: return "COMPRESS";
        default: return "UNKNOWN";
    }
}
#endif