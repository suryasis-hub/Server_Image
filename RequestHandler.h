#include <pistache/http.h>
#include <pistache/router.h>
#include <unordered_map>
#include <functional>

class RequestHandler : public Pistache::Http::Handler {
public:
    HTTP_PROTOTYPE(RequestHandler)

     std::unordered_map<std::string, std::function<std::string(const Pistache::Http::Request&)>> routerMapForFunction = {
        {"/hello", [](const Pistache::Http::Request& request) { return "Hello from Pistache!"; }},
        {"/status", [](const Pistache::Http::Request& request) { return "Server is running..."; }}
    };

    RequestHandler() = default;

    void onRequest(const Pistache::Http::Request &request, Pistache::Http::ResponseWriter response) override;

private:
    Pistache::Rest::Router router;
};
