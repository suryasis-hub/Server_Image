#include <pistache/http.h>
#include <pistache/router.h>
#include <unordered_map>
#include <functional>


void handleImageUpload(const Pistache::Http::Request& request);

class RequestHandler : public Pistache::Http::Handler {
public:
    HTTP_PROTOTYPE(RequestHandler)
     std::unordered_map<std::string, std::function<void(const Pistache::Http::Request&)>> routerMapForFunction = 
     {
    {"/hello", [](const Pistache::Http::Request& request) 
    { 
    }},
    {"/upload", [](const Pistache::Http::Request& request) 
        { 
            handleImageUpload(request);
        }}
    };



    RequestHandler() = default;

    void onRequest(const Pistache::Http::Request &request, Pistache::Http::ResponseWriter response) override;

private:
    Pistache::Rest::Router router;
};
