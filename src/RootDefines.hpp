// 本文件包含 Root 层的前向类型声明及命名空间引用
#pragma once
#include "oatpp-swagger/Model.hpp"
#include "oatpp-sqlite/Executor.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp-sqlite/Connection.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp-sqlite/ConnectionProvider.hpp"
#include "oatpp/web/server/handler/ErrorHandler.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/web/protocol/http/outgoing/ResponseFactory.hpp"

using oatpp::String;
using std::shared_ptr;
using std::make_shared;
using std::chrono::seconds;
using oatpp::network::Address;
using oatpp::swagger::Resources;
using oatpp::provider::Provider;
using oatpp::swagger::DocumentInfo;
using oatpp::sqlite::ConnectionPool;
using oatpp::web::server::HttpRouter;
using oatpp::network::ConnectionHandler;
using oatpp::web::protocol::http::Status;
using oatpp::data::mapping::ObjectMapper;
using oatpp::network::ServerConnectionProvider;
using oatpp::web::server::HttpConnectionHandler;
using oatpp::network::tcp::server::ConnectionProvider;
using oatpp::web::protocol::http::outgoing::ResponseFactory;
using SqlExecutor = oatpp::sqlite::Executor;
using SqlConnectionProvider = oatpp::sqlite::ConnectionProvider;
using WebErrorHandler = oatpp::web::server::handler::ErrorHandler;
using JsonObjectMapper = oatpp::parser::json::mapping::ObjectMapper;
using OutgoingResponse = oatpp::web::protocol::http::outgoing::Response;
