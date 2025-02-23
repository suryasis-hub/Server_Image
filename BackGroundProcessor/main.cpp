#include <iostream>
#include <memory>

#include "IQueue.h"
#include "FileQueue.h"
#include "FileOperationFactory.h"
#include "IOperation.h"
#include "CopyOperation.h"
#include "OperationType.h"
#include "../external/loguru/loguru.hpp"


int main(int argc, char* argv[])
{
    loguru::init(argc, argv);
    LOG_F(INFO, "Background processor started");
    std::unique_ptr<FileQueue> queue = std::make_unique<FileQueue>("Images.txt");
    while(true)
    {
        auto fileValue = queue->pop();
        if (fileValue.has_value())
        {
            std::unique_ptr<IOperation>  fileOperation = FileOperationFactory::GetOperation(OperationType::COPY);
            fileOperation->doOperation(fileValue->filePath);
        }

    }
    return 0;
}