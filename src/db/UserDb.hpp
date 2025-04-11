#pragma once
#pragma execution_character_set("utf-8")
#include "DbDefines.hpp"
#include "../dto/UserDto.hpp"
#include OATPP_CODEGEN_BEGIN(DbClient)

/**
 * @brief 用户数据库访问类
 *        执行用户相关的数据库操作，包括数据库模式迁移以及用户数据的CURD操作。
 *        通过 QUERY 宏定义 SQL 语句，使用参数绑定实现数据安全注入。
 * @author LiMuhua
 * @date 2025-04-10
 */
class UserDb : public DbClient {
  public:
    /**
     * @brief 构造函数，初始化 UserDb 对象，
     *        基于传入的 Executor 对象执行数据库模式迁移。若迁移过程中遇到错误，将会抛出异常。
     * @param executor 数据库执行器，负责具体的 SQL 执行和事务管理。
     */
    UserDb(const std::shared_ptr<Executor> &executor) : DbClient(executor) {
        // 执行数据库迁移
        SchemaMigration migration(executor);
        migration.addFile(1, DATABASE_MIGRATIONS "/001_init.sql");
        // TODO - 后续版本添加更多迁移文件，不要用于生产环境, 会被覆盖数据
        migration.migrate(); // 执行迁移；若出错则会抛出异常

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("UserDb", "Migration - OK. Version=%lld.", version)
    }

    /*************** 新增用户数据 ***************/
    QUERY(createUser,
          "INSERT INTO AppUser"
          "(username, email, password, role) VALUES "
          "(:user.username, :user.email, :user.password, :user.role);",
          PARAM(Object<UserDto>, user))

    /*************** 更新用户数据 ***************/
    QUERY(updateUser,
          "UPDATE AppUser "
          "SET "
          " username=:user.username, "
          " email=:user.email, "
          " password=:user.password, "
          " role=:user.role "
          "WHERE "
          " id=:user.id;",
          PARAM(Object<UserDto>, user))

    /*************** 通过ID查询用户 ***************/
    QUERY(getUserById,
          "SELECT * FROM AppUser WHERE id=:id;",
          PARAM(Int32, id))

    /*************** 分页查询用户 ***************/
    QUERY(getAllUsers,
          "SELECT * FROM AppUser LIMIT :limit OFFSET :offset;",
          PARAM(UInt32, offset),
          PARAM(UInt32, limit))

    /*************** 通过ID删除用户 ***************/
    QUERY(deleteUserById,
          "DELETE FROM AppUser WHERE id=:id;",
          PARAM(Int32, id))
};

#include OATPP_CODEGEN_END(DbClient)
