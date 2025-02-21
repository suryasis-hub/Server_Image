#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <iostream>
#include <fstream>
#include "RequestHandler.h"

using namespace Pistache;

void handleImageUpload(const Pistache::Http::Request& request) 
{
        auto contentType = request.headers().get<Http::Header::ContentType>();
        std::ofstream file("uploaded_image.jpg", std::ios::binary);
        file << request.body();
        file.close();
}

// Corrected function definition
void RequestHandler::onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response) {
    std::string path = request.resource();

    // Check if the path exists in the router map
    auto it = routerMapForFunction.find(path);
    if (it != routerMapForFunction.end()) {
        it->second(request);  // Call the mapped function
        response.send(Pistache::Http::Code::Ok);
    } else {
        response.send(Pistache::Http::Code::Not_Found, "404 - Not Found");
    }
}
