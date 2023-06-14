#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H

#include "dto/UserDto.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

/**
 * Custom Request Handler
 */
class Handler : public oatpp::web::server::HttpRequestHandler
{
private:
    std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper> m_objectMapper;

public:
    /**
     * Handle incoming request and return outgoing response.
     */
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest> &request) override
    {
        auto message = MessageDto::createShared();
        message->statusCode = 1024;
        message->message = "Hello DTO!";
        return ResponseFactory::createResponse(Status::CODE_200, message, m_objectMapper);
    }
    /**
     * Constructor with object mapper.
     * @param objectMapper - object mapper used to serialize objects.
     */
    Handler(const std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper> &objectMapper) : m_objectMapper(objectMapper) {}
};

void run()
{
    /* Create json object mapper */
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    /* Create Router for HTTP requests routing */
    auto router = oatpp::web::server::HttpRouter::createShared();
    /* Route GET - "/hello" requests to Handler */
    router->route("GET", "/hello", std::make_shared<Handler>(objectMapper /* json object mapper */));

    /* Create HTTP connection handler with router */
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    /* Create TCP connection provider */
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8000, oatpp::network::Address::IP_4});

    /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
    oatpp::network::Server server(connectionProvider, connectionHandler);

    /* Print info about server port */
    OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData());

    /* Run server */
    server.run();
}

#endif // _WEB_SERVER_H