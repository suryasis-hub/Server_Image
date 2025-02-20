#ifndef FILE_OPERATION_FACTORY_H
#define FILE_OPERATION_FACTORY_H

#include <memory>
#include "IOperation.h"
#include "CopyOperation.h"
#include "OperationType.h"

class FileOperationFactory {
public:
    static std::unique_ptr<IOperation> GetOperation(OperationType type) {
        switch (type) {
            case OperationType::COPY:
                return std::make_unique<CopyOperation>();
            default:
                throw std::invalid_argument("Invalid operation type");
        }
    }
};

#endif // FILE_OPERATION_FACTORY_H
