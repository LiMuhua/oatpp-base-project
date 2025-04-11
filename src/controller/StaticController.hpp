
#pragma once
#pragma execution_character_set("utf-8")
#include "ControllerDefines.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 * @brief 静态接口
 * @details 以 RESTful 风格提供静态资源相关的接口。
 * @author LiMuhua
 * @date 2025-04-10
 */
class StaticController : public ApiController {
  public:
    /** 构造Controller **/
    StaticController(const shared_ptr<ObjectMapper> &objectMapper) : ApiController(objectMapper) {}
    /** 静态工厂方法 **/
    static shared_ptr<StaticController> createShared(OATPP_COMPONENT(shared_ptr<ObjectMapper>, objectMapper)) {
        return make_shared<StaticController>(objectMapper);
    }

    /********************* 根目录 *********************/
    ENDPOINT("GET", "/", root) {
        const char* html =
            "<html lang='en'>"
            "  <head>"
            "    <meta charset=utf-8/>"
            "  </head>"
            "  <body>"
            "    <p>Hello CRUD example project!</p>"
            "    <a href='swagger/ui'>Checkout Swagger-UI page</a>"
            "  </body>"
            "</html>";
        auto response = createResponse(Status::CODE_200, html);
        response->putHeader(Header::CONTENT_TYPE, "text/html");
        return response;
    }

};

#include OATPP_CODEGEN_END(ApiController)
