/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <memory>

#include "IQueue.h"
#include "FileQueue.h"
#include "FileOperationFactory.h"
#include "IOperation.h"
#include "CopyOperation.h"
#include "OperationType.h"


int main()
{
    std::unique_ptr<FileQueue> queue = std::make_unique<FileQueue>("Images.txt");
    std::unique_ptr<IOperation>  fileOperation = FileOperationFactory::GetOperation(OperationType::COPY);
    while(true)
    {
        auto fileValue = queue->pop();
        if (fileValue.has_value())
        {
            fileOperation->doOperation(*fileValue);
        }
    }
    return 0;
}