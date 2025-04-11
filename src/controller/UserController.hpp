#pragma once
#pragma execution_character_set("utf-8")
#include "ControllerDefines.hpp"
#include "../service/UserService.hpp"
#include "../TokenAuthorizationHandler.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 * @brief 用户接口
 * @details 以 RESTful 风格提供用户相关的 CRUD 接口。
 * @author LiMuhua
 * @date 2025-04-10
 */
class UserController : public ApiController {
  private:
    UserService m_userService; // 用户Service
  public:
    /** 构造Controller **/
    explicit UserController(const shared_ptr<ObjectMapper> &objectMapper) : ApiController(objectMapper) {
        // TODO: Token验证完善, 现在比较简陋
        //setDefaultAuthorizationHandler(make_shared<TokenAuthorizationHandler>());
    }
    /** 静态工厂方法 **/
    static shared_ptr<UserController> createShared(OATPP_COMPONENT(shared_ptr<ObjectMapper>, objectMapper)) {
        return make_shared<UserController>(objectMapper);
    }

    /********************* 登录接口 *********************/
    ENDPOINT_INFO(login) { info->summary = "登录"; info->addTag("UserController"); }
    ENDPOINT("POST", "login", login, BODY_DTO(Object<UserDto>, userDto)) {
        printf("userId %d", userDto->id.getValue(-1));
        auto response = createDtoResponse(Status::CODE_200, m_userService.login(userDto));
        response->putHeader("Content-Type", JSON_UTF8);
        return response;
    }

    /********************* 新增接口 *********************/
    ENDPOINT_INFO(createUser) {
        info->summary = "创建新用户"; info->addTag("UserController");
        info->addConsumes<Object<UserDto >> (JSON_UTF8);
        info->addResponse<Object<UserDto >> (Status::CODE_200, JSON_UTF8);
        info->addResponse<Object<StatusDto >> (Status::CODE_404, JSON_UTF8);
        info->addResponse<Object<StatusDto >> (Status::CODE_500, JSON_UTF8);
    }
    ENDPOINT("POST", "users", createUser, BODY_DTO(Object<UserDto>, userDto)) {
        return createDtoResponse(Status::CODE_200, m_userService.createUser(userDto));
    }

    /********************* 更新接口 *********************/
    ENDPOINT_INFO(putUser) {
        info->summary = "更新用户信息"; info->addTag("UserController");
        info->addConsumes<Object<UserDto >> (JSON_UTF8);
        info->body.description = "参数描述";
        info->addResponse<Object<UserDto >> (Status::CODE_200, JSON_UTF8);
        info->addResponse<Object<StatusDto >> (Status::CODE_404, JSON_UTF8);
        info->addResponse<Object<StatusDto >> (Status::CODE_500, JSON_UTF8);
        info->pathParams["userId"].required = true;
        info->pathParams["userId"].description = "用户ID";
    }
    ENDPOINT("PUT", "users/{userId}", putUser, PATH(Int32, userId), BODY_DTO(Object<UserDto>, userDto)) {
        userDto->id = userId;
        return createDtoResponse(Status::CODE_200, m_userService.updateUser(userDto));
    }

    /********************* 查询单个接口 *********************/
    ENDPOINT_INFO(getUserById) {
        info->summary = "通过 ID 查询用户"; info->addTag("UserController");
        //info->addSecurityRequirement("Token");
        info->addResponse<Object<UserDto >> (Status::CODE_200, JSON_UTF8);
        info->addResponse<Object<StatusDto >> (Status::CODE_404, JSON_UTF8);
        info->addResponse<Object<StatusDto >> (Status::CODE_500, JSON_UTF8);
        info->pathParams["userId"].required = true;
        info->pathParams["userId"].description = "User Identifier";
    }
    ENDPOINT("GET", "users/{userId}", getUserById,
             //AUTHORIZATION(shared_ptr<TokenAuthorizationObject>, authObject),
        PATH(Int32, userId)
    ) {
        return createDtoResponse(Status::CODE_200, m_userService.getUserById(userId));
    }

    /********************* 查询所有接口 *********************/
    ENDPOINT_INFO(getUsers) {
        info->summary = "获取所有用户"; info->addTag("UserController");
        info->addResponse<oatpp::Object<UsersPageDto >> (Status::CODE_200, JSON_UTF8);
        info->addResponse<Object<StatusDto >> (Status::CODE_500, JSON_UTF8);
    }
    ENDPOINT("GET", "users/offset/{offset}/limit/{limit}", getUsers, PATH(UInt32, offset), PATH(UInt32, limit)) {
        return createDtoResponse(Status::CODE_200, m_userService.getAllUsers(offset, limit));
    }

    /********************* 删除接口 *********************/
    ENDPOINT_INFO(deleteUser) {
        info->summary = "通过 ID 删除用户"; info->addTag("UserController");
        info->addResponse<Object<StatusDto >> (Status::CODE_200, JSON_UTF8);
        info->addResponse<Object<StatusDto >> (Status::CODE_500, JSON_UTF8);
        info->pathParams["userId"].description = "User Identifier";
    }
    ENDPOINT("DELETE", "users/{userId}", deleteUser, PATH(Int32, userId)) {
        return createDtoResponse(Status::CODE_200, m_userService.deleteUserById(userId));
    }
};

#include OATPP_CODEGEN_END(ApiController)
