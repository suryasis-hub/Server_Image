#include "RequestHandler.h"
#include <opencv2/opencv.hpp>

using namespace Pistache;

void RequestHandler::onRequest(const Http::Request &request, Http::ResponseWriter response) {
    auto query = request.query();
    Http::Method method = request.method();
    // Check the method type
    if (method == Http::Method::Get) {
        std::cout << "Received a GET request" << std::endl;
    } else if (method == Http::Method::Post) {
        std::cout << "Received a POST request" << std::endl;
    } else if (method == Http::Method::Put) {
        std::cout << "Received a PUT request" << std::endl;
    } else if (method == Http::Method::Delete) {
        std::cout << "Received a DELETE request" << std::endl;
    } else {
        std::cout << "Received an unknown request type" << std::endl;
    }

    // Continue processing based on method
    response.send(Http::Code::Ok, "Request processed");
}
