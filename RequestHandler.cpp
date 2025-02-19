#include "RequestHandler.h"
#include <iostream>
#include <pistache/endpoint.h>
#include <pistache/http.h>

using namespace Pistache;

int main()

{
  Http::Endpoint server(Address(Ipv4::any(), Port(9081)));
  auto opts =
      Http::Endpoint::options().threads(1).maxRequestSize(1024 * 1024 * 10);
  server.init(opts);
  auto handler = std::make_shared<RequestHandler>();
  server.setHandler(handler);
  server.serve();
  return 0;
}
