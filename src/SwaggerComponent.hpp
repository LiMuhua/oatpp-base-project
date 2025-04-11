#pragma once
#pragma execution_character_set("utf-8")
#include "RootDefines.hpp"

/**
 * @brief Swagger 组件类, 配置和注册 Swagger UI 所需的组件，
 *        启动后后可通过以下 URL 访问 UI： http://127.0.0.1:8000/swagger/ui
 * @author LiMuhua
 * @date 2025-04-10
 */
class SwaggerComponent {
  public:

    /**
     * 创建全局 API 文档信息组件, 描述 API 的基本信息
     * 如标题、描述、版本、联系方式、证书信息以及服务器配置等。
     */
    OATPP_CREATE_COMPONENT(shared_ptr<DocumentInfo>, swaggerDocumentInfo)([] {

        // 配置安全认证方案
        DocumentInfo::SecuritySchemeBuilder securitySchemeBuilder;
        securitySchemeBuilder
        .setType("apiKey")
        .setName("Authorization")
        .setIn("header")
        .setDescription("Enter: \"Token the.jwt.token\"");

        // 通过 Builder 模式构造 API 文档信息
        DocumentInfo::Builder builder;
        builder
        .setTitle("Oat++ Base Service")
        .setDescription("一个带有 Swagger 文档的 CRUD API 示例项目")
        .setVersion("1.0")
        .setContactName("Oat++")
        .setContactUrl("https://oatpp.io/")
        .setLicenseName("Apache License, Version 2.0")
        .addSecurityScheme("Token", securitySchemeBuilder.build())
        .setLicenseUrl("http://www.apache.org/licenses/LICENSE-2.0")
        .addServer("http://127.0.0.1:8000", "本地服务");

        return builder.build();
    }());

    /**
     * 创建 Swagger UI 静态资源组件, 加载并提供 Swagger UI 的静态资源
     * 注意：请确保正确指定 oatpp-swagger/res 文件夹的完整路径
     */
    OATPP_CREATE_COMPONENT(shared_ptr<Resources>, swaggerResources)([] {
        return Resources::loadResources(OATPP_SWAGGER_RES_PATH);
    }());
};