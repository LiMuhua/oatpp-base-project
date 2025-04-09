
#ifndef UserController_hpp
#define UserController_hpp

#include "../service/UserService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
using oatpp::web::protocol::http::Status;
class TokenAuthorizationObject : public oatpp::web::server::handler::AuthorizationObject
{
public:
  TokenAuthorizationObject(const oatpp::String &pUserId)
      : userId(pUserId)
  {
  }

  oatpp::String userId;
};

class TokenBearerAuthorizationHandler : public oatpp::web::server::handler::BearerAuthorizationHandler
{

public:
  TokenBearerAuthorizationHandler()
      : BearerAuthorizationHandler("my-realm")
  {
  }

  std::shared_ptr<AuthorizationObject> authorize(const oatpp::String &token) override
  {
    printf("authorize token %s", token.getValue("").c_str());
    if (token == "4e99e8c12de7e01535248d2bac85e732")
    {
      return std::make_shared<TokenAuthorizationObject>("uid-admin");
    }
    return nullptr;
  }

  std::shared_ptr<AuthorizationObject> handleAuthorization(const oatpp::String &header)
  {
    
    // printf("handleAuthorization token %s", header.getValue("").c_str());
    OATPP_LOGD("TokenBearerAuthorizationHandler", "handleAuthorization token '%s'", header.getValue("666").c_str());
    if (header && header->size() > 6 && oatpp::utils::String::compare(header->data(), 6, "Token ", 6) == 0)
    {

      oatpp::String token = oatpp::String(header->c_str() + 6, header->size() - 6);

      auto authResult = authorize(token);
      if (authResult)
      {
        return authResult;
      }

      // OATPP_ASSERT_HTTP(false, Status::CODE_401, "Unauthorized");
      OATPP_ASSERT_HTTP(false, Status::CODE_401, "Unauthorized");
    }

    OATPP_ASSERT_HTTP(false, Status::CODE_401, "The authorization is required. Login");
  }
};

/**
 * User REST controller.
 */
class UserController : public oatpp::web::server::api::ApiController
{

public:
  UserController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper)
  {
    setDefaultAuthorizationHandler(std::make_shared<TokenBearerAuthorizationHandler>());
  }

private:
  UserService m_userService; // Create user service.
  // std::shared_ptr<AuthorizationHandler> m_bearerAuthHandler = std::make_shared<TokenBearerAuthorizationHandler>();
public:
  static std::shared_ptr<UserController> createShared(
      OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  )
  {
    return std::make_shared<UserController>(objectMapper);
  }

  ENDPOINT_INFO(login)
  {
    info->summary = "登录";
    info->addTag("UserController");
  }
  ENDPOINT("POST", "login", login, BODY_DTO(Object<UserDto>, userDto))
  {
    // OATPP_ASSERT_HTTP(authObject->userId == "uid-admin", Status::CODE_401, "Unauthorized");
    // std::cout << "userId " << authObject->userId << std::endl ;
    printf("userId %d", userDto->id.getValue(-1));

    return createDtoResponse(Status::CODE_200, m_userService.login(userDto));
  }

  ENDPOINT_INFO(createUser)
  {
    info->summary = "Create new User";
    info->addTag("UserController");
    info->addConsumes<Object<UserDto>>("application/json");

    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "users", createUser,
           BODY_DTO(Object<UserDto>, userDto))
  {
    return createDtoResponse(Status::CODE_200, m_userService.createUser(userDto));
  }

  ENDPOINT_INFO(putUser)
  {
    info->summary = "更新用户信息";
    info->addTag("UserController");
    info->addConsumes<Object<UserDto>>("application/json");
    info->body.description = "参数描述";

    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["userId"].required = true;
    info->pathParams["userId"].description = "用户ID";
  }
  ENDPOINT("PUT", "users/{userId}", putUser,
           PATH(Int32, userId),
           BODY_DTO(Object<UserDto>, userDto))
  {
    userDto->id = userId;
    return createDtoResponse(Status::CODE_200, m_userService.updateUser(userDto));
  }

  ENDPOINT_INFO(getUserById)
  {
    info->summary = "Get one User by userId";
    info->addTag("UserController");
    info->addSecurityRequirement("Token");
    info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    info->pathParams["userId"].required = true;
    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("GET", "users/{userId}", getUserById,
           AUTHORIZATION(std::shared_ptr<TokenAuthorizationObject>, authObject),
           PATH(Int32, userId))
  {
    return createDtoResponse(Status::CODE_200, m_userService.getUserById(userId));
  }

  ENDPOINT_INFO(getUsers)
  {
    info->summary = "get all stored users";
    info->addTag("UserController");

    info->addResponse<oatpp::Object<UsersPageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "users/offset/{offset}/limit/{limit}", getUsers,
           PATH(UInt32, offset),
           PATH(UInt32, limit))
  {
    return createDtoResponse(Status::CODE_200, m_userService.getAllUsers(offset, limit));
  }

  ENDPOINT_INFO(deleteUser)
  {
    info->summary = "Delete User by userId";
    info->addTag("UserController");
    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["userId"].description = "User Identifier";
  }
  ENDPOINT("DELETE", "users/{userId}", deleteUser,
           PATH(Int32, userId))
  {
    return createDtoResponse(Status::CODE_200, m_userService.deleteUserById(userId));
  }
};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* UserController_hpp */
