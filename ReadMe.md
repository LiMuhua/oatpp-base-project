## Oatpp-Base-Project

一个使用`Oat++`构建的完整`CRUD`服务——`UserService`示例；可以作为作为基础的项目模板使用。

Forked From： [long-fu/oatpp_simple](https://github.com/long-fu/oatpp_simple)

本示例包括：

- 如何创建`CRUD`访问端点。
- 如何使用[oatpp ORM](https://oatpp.io/docs/components/orm/#high-level-overview) - `SQLite`示例。
- 如何使用`Swagger-UI`和`OpenApi 3.0.0`文档化`API`。
- 使用了以下`oatpp`模块：[oatpp](https://github.com/oatpp/oatpp)、[oatpp-swagger](https://github.com/oatpp/oatpp-swagger)、[oatpp-sqlite](https://github.com/oatpp/oatpp-sqlite)。

更多关于Oat++的信息：

- [Oat++官网](https://oatpp.io/)
- [Oat++ Github仓库](https://github.com/oatpp/oatpp)
- [开始使用](https://oatpp.io/docs/start)

### 项目布局

```shell
|- CMakeLists.txt                        // 项目的CMakeLists.txt
|- libs									 // 三方库依赖, 包括oatpp、sqlite等
|- resources/sql/                        // SQLite数据库的SQL迁移脚本、数据文件
|- src/
|   |- controller/                       // 包含REST控制器的文件夹(UserController)
|   |- db/                               // 包含数据库客户端的文件夹
|   |- dto/                              // 这里声明DTOs(数据传输对象)
|   |- service/                          // 服务业务逻辑类(UserService)
|   |- AppComponent.hpp                  // 服务配置
|   |- DatabaseComponent.hpp             // 数据库配置
|   |- SwaggerComponent.hpp              // Swagger-UI配置
|   |- App.cpp                           // main()函数在这里
|- test/                                 // 测试文件夹
|- utility						         // 安装所需oatpp模块的实用脚本、CMake工具
```

### 构建和运行

#### CMake

##### 前置要求

- `oatpp`
- `oatpp-swagger`
- `oatpp-sqlite` 带有 `-DOATPP_SQLITE_AMALGAMATION=ON` cmake标志。

**注意:** 可以运行 `utility/install-oatpp-modules.sh` 脚本来安装所需的`oatpp`模块。

TODO： Windows安装脚本

##### 构建项目

```
$ mkdir build && cd build
$ cmake ..
$ make 
$ ./oatpp-base        # - 运行应用程序
```

#### Docker

TODO：有待调整

```shell
$ docker build -t example-crud .
$ docker run -p 8000:8000 -t example-crud
```

### 访问端点

#### HTML

| HTTP方法 | URL                              | 描述           |
| -------- | -------------------------------- | -------------- |
| `GET`    | http://localhost:8000/           | 根页面         |
| `GET`    | http://localhost:8000/swagger/ui | Swagger UI页面 |

#### 用户接口

| HTTP方法 | URL                                                       | 描述             |
| -------- | --------------------------------------------------------- | ---------------- |
| `POST`   | http://localhost:8000/users                               | 创建新用户       |
| `PUT`    | http://localhost:8000/users/{userId}                      | 通过ID更新用户   |
| `GET`    | http://localhost:8000/users/{userId}                      | 通过ID获取用户   |
| `DELETE` | http://localhost:8000/users/{userId}                      | 通过ID删除用户   |
| `GET`    | http://localhost:8000/users/offset/{offset}/limit/{limit} | 分页获取所有用户 |

