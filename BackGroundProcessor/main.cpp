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
#include "IOperation.h"
#include "CopyOperation.h"


int main()
{
    std::unique_ptr<FileQueue> queue = std::make_unique<FileQueue>("Images.txt");
    std::unique_ptr<IOperation> copyFileOperation = std::make_unique<CopyOperation>();
    while(true)
    {
        auto fileValue = queue->pop();
        if (fileValue.has_value())
        {
            copyFileOperation->doOperation(*fileValue);
        }
    }
    return 0;
}