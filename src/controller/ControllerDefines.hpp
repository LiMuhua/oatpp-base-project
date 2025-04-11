// 本文件包含 Controller 层的前向类型声明及命名空间引用
#pragma once
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
using std::move;
using oatpp::String;
using std::shared_ptr;
using std::make_shared;
using oatpp::base::Environment;
using oatpp::web::protocol::http::Status;
using oatpp::web::server::api::ApiController;
using oatpp::web::server::handler::AuthorizationObject;
using oatpp::web::server::handler::BearerAuthorizationHandler;
