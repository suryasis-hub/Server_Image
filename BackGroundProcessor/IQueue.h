#include <optional>

class IQueue
{
    public:
        virtual std::optional<std::string> pop() = 0;
        virtual void push(std::string imagePath) = 0;
        virtual bool isEmpty() = 0;    
};