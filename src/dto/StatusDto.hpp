#pragma once
#pragma execution_character_set("utf-8")
#define JSON_UTF8 oatpp::String("application/json; charset=utf-8")
#include "DtoDefines.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * @brief 状态数据传输对象 (DTO)
 * @details 定义响应状态数据的字段结构。
 * @author LiMuhua
 * @date 2025-04-10
 */
class StatusDto : public DTO {
    DTO_INIT(StatusDto, DTO)

    DTO_FIELD_INFO(status) { info->description = "简短的状态信息"; }
    DTO_FIELD(String, status, "status");

    DTO_FIELD_INFO(code) { info->description = "状态码"; }
    DTO_FIELD(Int32, code, "code");

    DTO_FIELD_INFO(message) { info->description = "详细信息"; }
    DTO_FIELD(String, message, "message");
};

#include OATPP_CODEGEN_END(DTO)

