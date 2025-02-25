#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <iostream>
#include <fstream>
#include "RequestHandler.h"
#include "external/loguru/loguru.hpp"
#include "BackgroundProcessor/IQueue.h"
#include "BackgroundProcessor/IOperation.h"
#include "BackgroundProcessor/FileOperationFactory.h"
using namespace Pistache;

void handleImageUpload(const Pistache::Http::Request& request) 
{
    auto contentType = request.headers().get<Http::Header::ContentType>();
    auto queryParams = request.query();
    std::string filename = queryParams.get("filename").value_or("uploaded_image.jpg");
    std::string operation =  queryParams.get("operation").value_or("COPY");
    std::ofstream file(filename, std::ios::binary);
    file << request.body();
    LOG_F(INFO, "File name  and operation%s, %s", filename.c_str(), operation.c_str());
    file.close();
    std::unique_ptr<IOperation>  fileOperation = FileOperationFactory::GetOperation(stringToOperationType(operation));
    fileOperation->doOperation(filename);
}

void serveImage(const Pistache::Http::Request &request, Pistache::Http::ResponseWriter &response) 
{
    auto query = request.query();
    std::string fileName = query.get("file").value_or("sample.jpg");
    LOG_F(INFO, "File name %s", fileName.c_str());

    std::string imagePath = fileName; 
    if (!std::filesystem::exists(imagePath)) 
    {
        response.send(Pistache::Http::Code::Not_Found, "Image not found");
        return;
    }

    std::ifstream file(imagePath, std::ios::binary | std::ios::ate);
    if (!file) 
    {
        response.send(Pistache::Http::Code::Internal_Server_Error, "Error opening image");
        return;
    }

    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(fileSize);

    if (!file.read(buffer.data(), fileSize)) 
    {
        response.send(Pistache::Http::Code::Internal_Server_Error, "Error reading image");
        return;
    }
    file.close();

    std::string contentType = "image/jpeg"; 
    response.headers().add<Pistache::Http::Header::ContentType>(contentType);
    response.send(Pistache::Http::Code::Ok, buffer.data(), buffer.size(), Pistache::Http::Mime::MediaType::fromString(contentType));
}

void RequestHandler::onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response) 
{
    std::string path = request.resource();
    auto it = routerMapForFunction.find(path);
    if (it != routerMapForFunction.end()) 
    {
        it->second(request);
        response.send(Pistache::Http::Code::Ok);
    } 
    else if(path.find("download") != std::string::npos)
    {
        serveImage(request, response);
    }
    else 

    {
        response.send(Pistache::Http::Code::Not_Found, "404 - Not Found");
    }
}
