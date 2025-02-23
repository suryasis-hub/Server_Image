#include <optional>

#include "ImageOperation.h"

class IQueue
{
    public:
        virtual std::optional<ImageOperationPair> pop() = 0;
        virtual void push(const ImageOperationPair &imageOperationPair) = 0;
        virtual bool isEmpty() = 0;    
};