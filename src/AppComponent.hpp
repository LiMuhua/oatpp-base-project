#pragma once
#pragma execution_character_set("utf-8")
#include "RootDefines.hpp"
#include "ErrorHandler.hpp"
#include "SwaggerComponent.hpp"
#include "DatabaseComponent.hpp"

/**
 * @brief 应用程序组件类
 * @details 用于创建和持有应用程序所需的各个组件，
 *          并将这些组件注册到 oatpp::base::Environment 中。
 * @note 组件初始化顺序依赖于类成员定义顺序，确保依赖关系正确。
 * @author LiMuhua
 * @date 2025-04-10
 */
class AppComponent {
  public:

    /** Swagger 组件: 负责处理 Swagger 相关功能，用于生成 API 文档 **/
    SwaggerComponent swaggerComponent;

    /** 数据库组件: 负责管理数据库连接及相关操作 **/
    DatabaseComponent databaseComponent;

    /**
     * 创建 ObjectMapper 组件
     * 以在 Controller API 中对数据传输对象（DTO）进行序列化和反序列化。
     */
    OATPP_CREATE_COMPONENT(shared_ptr<ObjectMapper>, apiObjectMapper)([] {
        auto objectMapper = JsonObjectMapper::createShared();
        objectMapper->getDeserializer()->getConfig()->allowUnknownFields = false;
        return objectMapper;
    }());

    /** 创建 ConnectionProvider 组件: 提供网络连接功能，监听指定的 IP 和端口 **/
    OATPP_CREATE_COMPONENT(shared_ptr<ServerConnectionProvider>, serverConnectionProvider)([] {
        return ConnectionProvider::createShared({ "0.0.0.0", 8000, Address::IP_4 });
    }());

    /** 创建 Router 组件: 用于处理 HTTP 请求路由，将请求分发给对应的处理器 **/
    OATPP_CREATE_COMPONENT(shared_ptr<HttpRouter>, httpRouter)([] {
        return HttpRouter::createShared();
    }());

    /** 创建 ConnectionHandler 组件: 使用 Router 组件来路由 HTTP 请求，并设置错误处理器 **/
    OATPP_CREATE_COMPONENT(shared_ptr<ConnectionHandler>, serverConnectionHandler)([] {

        OATPP_COMPONENT(shared_ptr<HttpRouter>, router);        // 获取 Router 组件
        OATPP_COMPONENT(shared_ptr<ObjectMapper>, objectMapper);// 获取 ObjectMapper 组件

        auto connectionHandler = HttpConnectionHandler::createShared(router);
        connectionHandler->setErrorHandler(make_shared<ErrorHandler>(objectMapper));
        return connectionHandler;
    }());

};