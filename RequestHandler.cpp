#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <iostream>
#include <unordered_map>
#include <functional>

using namespace Pistache;


std::string handleHello(const Http::Request& request) 
{
    return "Hello from Pistache!";
}

std::string handleStatus(const Http::Request& request) 
{
    return "Server is running...";
}

class RequestHandler 
{
    private:
        std::unordered_map<std::string, std::function<std::string(const Http::Request&)>> routerMapForFunction;

    public:
        RequestHandler() 
        {
            // Register handler functions
            routerMapForFunction["/hello"] = handleHello;
            routerMapForFunction["/status"] = handleStatus;
        }

        void onRequest(const Http::Request& request, Http::ResponseWriter response) 
        {
            std::string path = request.resource();
            auto it = routerMapForFunction.find(path);
            if (it != routerMapForFunction.end()) 
            {
                std::string responseData = it->second(request);  // Call the mapped function
                response.send(Http::Code::Ok, responseData);
            } 
            else 
            {
                response.send(Http::Code::Not_Found, "404 - Not Found");
            }
        }
};
