#include "RequestHandler.h"
#include <opencv2/opencv.hpp>

using namespace Pistache;

void RequestHandler::onRequest(const Http::Request &request, Http::ResponseWriter response) {
    auto query = request.query();
    if (query.has("name")) {
        std::string name = query.get("name").value();
        std::cout << "Query Parameter [name]: " << name << std::endl;
    }
    response.headers().add<Http::Header::AccessControlAllowOrigin>("http://localhost:8000");
    response.headers().add<Http::Header::AccessControlAllowOrigin>("*");
    response.headers().add<Http::Header::AccessControlAllowHeaders>("Content-Type");
    response.send(Http::Code::Ok, "Hello from Pistache on macOS!");
}
