#pragma once
#pragma execution_character_set("utf-8")
#include "UserDto.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
* @brief 分页数据对象 (DTO) 模板类
* @details 定义分页数据的字段结构。
* @author LiMuhua
* @date 2025-04-10
*/
template<class T>
class PageDto : public DTO {

    DTO_INIT(PageDto, DTO)

    DTO_FIELD_INFO(offset) { info->description = "偏移量"; }
    DTO_FIELD(UInt32, offset, "offset");

    DTO_FIELD_INFO(limit) { info->description = "单页数量"; }
    DTO_FIELD(UInt32, limit, "limit");

    DTO_FIELD_INFO(count) { info->description = "总数据量"; }
    DTO_FIELD(UInt32, count, "count");

    DTO_FIELD_INFO(items) { info->description = "数据容器"; }
    DTO_FIELD(Vector<T>, items, "items");

};


/**
* @brief 用户Dto的分页封装
* @author LiMuhua
* @date 2025-04-10
*/
class UsersPageDto : public PageDto<Object<UserDto >> {
    DTO_INIT(UsersPageDto, PageDto)
};

#include OATPP_CODEGEN_END(DTO)
