#pragma once
#include "db/UserDb.hpp"
#include "RootDefines.hpp"

/**
 * @brief 数据库组件类
 * @details 创建与配置数据库相关的组件，包括数据库连接池和数据库客户端。
 * @author LiMuhua
 * @date 2025-04-10
 */
class DatabaseComponent {
    typedef oatpp::sqlite::Connection Connection;

  public:
    /** 创建 Sqllite 数据库连接提供者组件, 负责提供 Sqllite 数据库连接 **/
    OATPP_CREATE_COMPONENT(shared_ptr<Provider<Connection >>, dbConnectionProvider)([] {
        // 创建数据库专用的连接池，设置最大连接数和连接存活时间(s); 默认空密码连接文件
        auto connectionProvider = make_shared<SqlConnectionProvider>(DATABASE_FILE);
        return ConnectionPool::createShared(connectionProvider, 10, seconds(5));
    }());


    /** 创建数据库客户端组件, 负责创建 UserDb 数据库客户端 **/
    OATPP_CREATE_COMPONENT(shared_ptr<UserDb>, userDb)([] {
        // 通过依赖注入获取数据库连接提供者组件
        OATPP_COMPONENT(shared_ptr<Provider<Connection >>, connectionProvider);
        // 创建针对 SQLite 的 Executor，用以执行 SQL 操作
        auto executor = make_shared<SqlExecutor>(connectionProvider);
        // 创建数据库客户端 UserDb 实例
        return make_shared<UserDb>(executor);
    }());

};