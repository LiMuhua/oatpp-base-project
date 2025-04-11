#pragma once
#pragma execution_character_set("utf-8")
#include "../db/UserDb.hpp"
#include "../dto/PageDto.hpp"
#include "../dto/StatusDto.hpp"
#include "ServiceDefines.hpp"

/**
 * @brief 用户服务类, 负责处理与用户相关的业务逻辑
 * @author LiMuhua
 * @date 2025-04-10
 */
class UserService {

  private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
    OATPP_COMPONENT(shared_ptr<UserDb>, m_database); // 注册数据处理层

  public:
    /**
    * @brief 用户登录
    * @param dto 用户数据对象，包含登录信息
    * @return 用户对象的共享指针
    */
    Object<UserDto> login(const Object<UserDto> &dto) const;

    /**
     * @brief 创建用户
     * @param dto 用户数据对象，包含用户信息
     * @return 新用户对象的共享指针
     */
    Object<UserDto> createUser(const Object<UserDto> &dto) const;

    /**
     * @brief 更新用户
     * @param dto 用户数据对象，包含用户信息
     * @return 更新后用户对象的共享指针
     */
    Object<UserDto> updateUser(const Object<UserDto> &dto) const;

    /**
     * @brief 根据ID获取用户
     * @param id 用户唯一标识符
     * @param connection 数据库连接（可选，默认空）
     * @return 用户对象的共享指针
     */
    Object<UserDto> getUserById(const Int32& id, const ResourceHandle<Connection> &connection = nullptr) const;

    /**
     * @brief 获取所有用户（分页）
     * @param offset 分页偏移量
     * @param limit 每页数量
     * @return 用户分页对象的共享指针
     */
    Object<PageDto<Object<UserDto >>> getAllUsers(const UInt32& offset, const UInt32& limit) const;

    /**
     * @brief 根据ID删除用户
     * @param id 用户唯一标识符
     * @return 操作状态对象的共享指针
     */
    Object<StatusDto> deleteUserById(const Int32& id) const;

};
