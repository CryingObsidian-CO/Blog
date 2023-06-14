#include <iostream>
#include "XMySql.h"
#include "WebServer.h"

// auto logger = Loggers::getLogger("default_Logger");
#include "UniversalTools/uuidGenerator.hpp"

int main()
{
    Loggers::init();

    // system("chcp 65001");
    XMySql MySql("localhost", "MyBlogTest", "123456", "MyBlog_Test", 3306);
    /*
    oatpp::base::Environment::init();
    run();
    oatpp::base::Environment::destroy();
    */

    std::cout << "\033[0;34m Start JsonUtils.h tese!! \033[0m" << std::endl;

    Loggers::Log("default_Logger", spdlog::level::level_enum::info, uuid::generate());
    // Log("default_Logger", spdlog::level::level_enum::info, "Hello, {}!：{}", "World", "←↑→↓↖↙↗↘↕");
    // spdlog::debug("Hello, {}!：{}", "World", "OK!");

    return EXIT_SUCCESS;
}