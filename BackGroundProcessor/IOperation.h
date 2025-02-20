#ifndef IOPERATION_H
#define IOPERATION_H

#include <string>

class IOperation {
public:
    virtual ~IOperation() = default;  // Virtual destructor for proper cleanup
    virtual std::string doOperation(const std::string &filePath) = 0; // Pure virtual function
};

#endif // IOPERATION_H
