# CMakeList项目：oatpp-base 在此处构建项目架构
cmake_minimum_required(VERSION 3.16)
project ("oatpp-base" VERSION 0.1 LANGUAGES CXX)
include(${CMAKE_CURRENT_SOURCE_DIR}/utility/cmake-utils.cmake)

# 如果支持，为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 前置资源定义
link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/libs/sqlite3/lib )


# Start 项目架构设置 
# 设置源代码目录和构建目录
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
# 全局通配资源扫描
file(GLOB_RECURSE HEADERS "*.h" "*.hpp")
file(GLOB_RECURSE SOURCES "*.cpp" "*.cxx" "*.cc")
file(GLOB_RECURSE RESOURCES "*.png" "*.jpg" "*.css")
# 排除输出目录和三方依赖, 不构建到项目目录
file(GLOB_RECURSE LIBS_SOURCES "out/*/*.*" "build/*/*.*" "libs/*/*.*" "doc/*/*.*" "*temp*/*/*.*" "test/*.*")
list(REMOVE_ITEM HEADERS ${LIBS_SOURCES})
list(REMOVE_ITEM SOURCES ${LIBS_SOURCES})
list(REMOVE_ITEM RESOURCES ${LIBS_SOURCES})

# 按文件类型分组
source_group(TREE ${SOURCE_DIR} PREFIX "Header" FILES ${HEADERS})
source_group(TREE ${SOURCE_DIR} PREFIX "Source" FILES ${SOURCES})
source_group(TREE ${SOURCE_DIR} PREFIX "Resource" FILES ${RESOURCES})
# 合并资源列表
set(SRCS ${SOURCES} ${HEADERS} ${RESOURCES})

# 根据项目名、类型标识、资源列表、资源文件创建可执行文件
add_executable(${PROJECT_NAME} ${SRCS})
# End 项目架构设置 

# 库配置
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/sqlite3/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/oatpp/include/oatpp-1.3.0/oatpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/oatpp/include/oatpp-1.3.0/oatpp-sqlite
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/oatpp/include/oatpp-1.3.0/oatpp-swagger
)
find_multiple_packages(
    PACKAGES oatpp oatpp-swagger oatpp-sqlite
    VERSION 1.3.0 EXACT REQUIRED
    PATHS  ${CMAKE_CURRENT_SOURCE_DIR}/libs/oatpp/lib/win-x64
    TARGET ${PROJECT_NAME} PUBLIC
    TARGET_DEPENDENCIES 
        oatpp::oatpp oatpp::oatpp-swagger 
        oatpp::oatpp-sqlite oatpp::oatpp-test
        sqlite3
)

# 预处理宏定义, 声明一些资源路径
add_definitions(
    # 定义 swagger-ui 静态资源文件夹的路径
    -DOATPP_SWAGGER_RES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/libs/oatpp/include/oatpp-1.3.0/bin/oatpp-swagger/res"
    # SQLite 数据库文件
    -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/resources/sql/db.sqlite"
    # SQLite 测试数据库文件 TODO: 缺少文件
    -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test-db.sqlite"
    # 数据库迁移脚本路径
    -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/resources/sql"
)

# 将资源文件复制到构建目录
set(RESOURCE_DIR "${SOURCE_DIR}/resources" )
if(EXISTS "${RESOURCE_DIR}")
  file(COPY ${RESOURCE_DIR} DESTINATION ${BINARY_DIR})
endif()


# 测试用例配置 TODO: 配置不全编译缺失资源
file(GLOB_RECURSE TEST_HEADERS "test/*.h" "test/*.hpp")
file(GLOB_RECURSE TEST_SOURCES "test/*.cpp" "test/*.cxx" "test/*.cc")
file(GLOB_RECURSE TEST_RESOURCES "test/*.png" "test/*.jpg" "test/*.css")
source_group(TREE ${SOURCE_DIR} PREFIX "Header" FILES ${TEST_HEADERS})
source_group(TREE ${SOURCE_DIR} PREFIX "Source" FILES ${TEST_SOURCES})
source_group(TREE ${SOURCE_DIR} PREFIX "Resource" FILES ${TEST_RESOURCES})
set(TEST_SRCS ${TEST_SOURCES} ${TEST_HEADERS} ${TEST_RESOURCES})
add_executable(${PROJECT_NAME}-test ${TEST_SRCS})
enable_testing()
add_test(project-tests ${PROJECT_NAME}-test)
