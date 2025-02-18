#include "RequestHandler.h"
#include <iostream>

std::string handleHello(const Pistache::Http::Request& request) {
    return "Hello from Pistache!";
}

std::string handleStatus(const Pistache::Http::Request& request) {
    return "Server is running...";
}

// Corrected function definition
void RequestHandler::onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response) {
    std::string path = request.resource();

    // Check if the path exists in the router map
    auto it = routerMapForFunction.find(path);
    if (it != routerMapForFunction.end()) {
        std::string responseData = it->second(request);  // Call the mapped function
        response.send(Pistache::Http::Code::Ok, responseData);
    } else {
        response.send(Pistache::Http::Code::Not_Found, "404 - Not Found");
    }
}
