#pragma once
#pragma execution_character_set("utf-8")
#include "DtoDefines.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)

/** 角色枚举定义 **/
ENUM(Role, v_int8,
     VALUE(GUEST, 0, "ROLE_GUEST"), // 游客
     VALUE(ADMIN, 1, "ROLE_ADMIN")  // 管理员
    )

/**
* @brief 用户数据传输对象 (DTO)
* @details 定义用户数据的字段结构。
* @author LiMuhua
* @date 2025-04-10
*/
class UserDto : public DTO {

    DTO_INIT(UserDto, DTO)

    DTO_FIELD_INFO(id) { info->description = "实例ID"; }
    DTO_FIELD(Int32, id, "id");

    DTO_FIELD_INFO(userName) { info->description = "用户名"; }
    DTO_FIELD(String, userName, "username");// 类型, 变量名, 字段名

    DTO_FIELD_INFO(password) { info->description = "密码"; }
    DTO_FIELD(String, password, "password");

    DTO_FIELD_INFO(email) { info->description = "电子邮箱"; }
    DTO_FIELD(String, email, "email");

    DTO_FIELD_INFO(token) { info->description = "登录返回的token"; }
    DTO_FIELD(String, token, "token");

    DTO_FIELD_INFO(role) { info->description = "用户角色"; }
    DTO_FIELD(Enum<Role>::AsString, role, "role");

};

#include OATPP_CODEGEN_END(DTO)
