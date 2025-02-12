#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <pistache/http.h>
#include <pistache/router.h>
#include <iostream>

class RequestHandler : public Pistache::Http::Handler 
{
public:
    RequestHandler() {
    }

   // Correct return type to match Pistache's inheritance
    std::shared_ptr<Pistache::Tcp::Handler> clone() const override {
        return std::make_shared<RequestHandler>();  // Avoid copying, use default constructor
    }
    void onRequest(const Pistache::Http::Request &request, Pistache::Http::ResponseWriter response) override;
private:
    Pistache::Rest::Router router;
};

#endif // REQUESTHANDLER_H
