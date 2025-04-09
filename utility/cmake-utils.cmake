# CMake 工具函数集合
# 该文件包含了一些常用的 CMake 工具函数和宏定义

# 查找多个包，支持常见参数、版本控制、多个路径查找和链接目标：
#   该宏简化了 CMake 中对多个依赖包的查找和链接操作。用户可以指定包名、版本、查找路径，
#   并可选地将指定的依赖目标链接到目标。要求在链接时显式指定依赖目标名称。
# 参数：
#   - PACKAGES (多值参数，必填)：
#       要查找的包名称列表，例如 "oatpp oatpp-swagger oatpp-sqlite"。
#       每个包名对应一个 find_package 调用。
#   - VERSION (单值参数，可选)：指定所有包的统一版本号，例如 "1.3.0"。若指定，则所有包必须匹配该版本。
#   - VERSIONS (多值参数，可选)：
#       为每个包分别指定版本号，例如 "1.3.0 1.2.0 1.0.0"。
#       注意：数量必须与 PACKAGES 数量一致，否则会报错。
#       如果同时指定了 VERSION 和 VERSIONS，VERSIONS 将优先使用。
#   - EXACT (选项，可选)：
#       统一要求所有包的版本号精确匹配。必须与 VERSION 或 VERSIONS 一起使用，否则会被忽略并发出警告。
#   - EXACTS (多值参数，可选)：
#       分别控制每个包的版本是否精确匹配，值为 on/off，例如 "on off on"。
#       注意：数量必须与 PACKAGES 数量一致，并且必须与 VERSIONS 一起使用。
#       EXACT 和 EXACTS 不能同时指定。
#   - REQUIRED (选项，可选)：
#       若包未找到，则终止配置并报错。未指定时，包未找到仅发出警告。
#   - PATHS (多值参数，可选)：
#       自定义查找路径列表，例如 "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/oatpp/lib/win-x64"。
#       CMake 将按顺序搜索这些路径。
#   - TARGET (单值参数，可选)：
#       要链接到的目标名称，例如 "my_app"。必须是已定义的 CMake 目标（通过 add_executable 或 add_library 创建）。
#   - TARGET_DEPENDENCIES (多值参数，可选但与 TARGET 绑定)：
#       要链接的具体依赖目标名称列表，例如 "oatpp::oatpp oatpp::oatpp-swagger sqlite3"。
#       如果指定 TARGET，则必须同时提供 TARGET_DEPENDENCIES，否则报错。
#   - PUBLIC (选项，可选)：
#       以 PUBLIC 方式将依赖链接到 TARGET，依赖对目标的使用者可见。
#   - PRIVATE (选项，可选)：
#       以 PRIVATE 方式将依赖链接到 TARGET，依赖对目标的使用者不可见。
# 注意：
#   - 如果指定 EXACT 但未提供 VERSION 或 VERSIONS，会发出警告并忽略 EXACT。
#   - EXACT 和 EXACTS 不能同时指定，否则会报错。
#   - 如果指定 EXACTS，必须与 PACKAGES 数量相同，且值必须是 on 或 off。
#   - PUBLIC 和 PRIVATE 不能同时指定。
#   - 如果指定 TARGET，必须同时提供 TARGET_DEPENDENCIES，否则报错。
#   - 未指定 PUBLIC 或 PRIVATE 时，默认使用 PRIVATE 链接。
#   - 如果未指定 TARGET，则不执行任何链接操作，仅查找包。
# 返回：
#   - 该宏没有显式返回值。
#   - 成功时，查找并（可选）链接指定的包和依赖；失败时，根据 REQUIRED 设置报错或警告。

# 使用示例：
# 示例 1：基本用法，仅查找包，不指定版本或链接
# find_multiple_packages(
#     PACKAGES oatpp oatpp-swagger oatpp-sqlite
#     PATHS ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/oatpp/lib/win-x64
# )
# 说明：
#   - 用途：仅查找指定的包，不执行任何链接操作。
#   - 场景：适用于需要单独检查包可用性而不立即链接的情况。
#   - 输出：查找 oatpp、oatpp-swagger 和 oatpp-sqlite，若未找到则发出警告。
# 示例 2：使用统一版本和统一 EXACT
# find_multiple_packages(
#     PACKAGES oatpp oatpp-swagger oatpp-sqlite
#     VERSION 1.3.0 EXACT REQUIRED
#     PATHS 
#         ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/oatpp/lib/win-x64
#         ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/oatpp/lib/win-x86
# )
# 说明：
#   - 用途：查找指定版本的包，要求精确匹配，并在多个路径中搜索。
#   - 场景：确保使用特定版本的依赖，例如修复版本兼容性问题。
#   - 输出：查找 oatpp 1.3.0 等，若未找到则报错。
# 示例 3：使用分别指定的版本和精确匹配设置
# find_multiple_packages(
#     PACKAGES oatpp oatpp-swagger oatpp-sqlite
#     VERSIONS "1.3.0" "1.3.0" "1.2.0"
#     EXACTS "on" "off" "on"
#     REQUIRED
#     PATHS ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/oatpp/lib/win-x64
# )
# 说明：
#   - 用途：分别为每个包指定版本和是否精确匹配
#   - 场景：对不同包有不同的版本要求，有的需要精确匹配，有的可以兼容匹配
#   - 输出：查找 oatpp 1.3.0（精确版本）、oatpp-swagger 1.3.0、oatpp-sqlite 1.2.0（精确版本）
# 示例 4：查找包并以 PUBLIC 方式链接用户指定的依赖
# add_executable(my_app src/main.cpp)
# find_multiple_packages(
#     PACKAGES oatpp oatpp-swagger oatpp-sqlite
#     VERSION 1.3.0 EXACT REQUIRED
#     PATHS ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/oatpp/lib/win-x64
#     TARGET ${PROJECT_NAME} PUBLIC
#     TARGET_DEPENDENCIES 
#         oatpp::oatpp oatpp::oatpp-swagger
#         oatpp::oatpp-sqlite oatpp::oatpp-test
#         sqlite3
# )
# 说明：
#   - 用途：查找包并将用户指定的依赖目标以 PUBLIC 方式链接到 my_app。
#   - 场景：目标依赖复杂，需要精确控制链接的依赖，例如包含额外的 sqlite3。
#   - 输出：查找包并链接，显示中文提示信息。
if(NOT DEFINED _FIND_MULTIPLE_PACKAGES_CMAKE_)
    set(_FIND_MULTIPLE_PACKAGES_CMAKE_ 1)

    macro(find_multiple_packages)
        # 定义参数类型，用于 cmake_parse_arguments 解析
        set(options EXACT REQUIRED PUBLIC PRIVATE)         # 可选开关参数
        set(oneValueArgs VERSION TARGET)                   # 接受单一值的参数
        set(multiValueArgs PACKAGES PATHS TARGET_DEPENDENCIES VERSIONS EXACTS)  # 接受多个值的参数

        # 解析传入的参数，将结果存储在 FMP_ 前缀的变量中
        cmake_parse_arguments(FMP "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

        # 检查必填参数 PACKAGES 是否提供
        if(NOT FMP_PACKAGES)
            message(FATAL_ERROR "Error: find_multiple_packages: 未指定任何包名！")
        endif()

        # 获取包的数量
        list(LENGTH FMP_PACKAGES packages_count)
        
        # 检查 EXACT 和 EXACTS 的互斥性
        if(FMP_EXACT AND FMP_EXACTS)
            message(FATAL_ERROR "Error: find_multiple_packages: 不能同时指定 EXACT 和 EXACTS！")
        endif()

        # 检查 EXACT 的有效性
        if(FMP_EXACT AND NOT (FMP_VERSION OR FMP_VERSIONS))
            message(WARNING "Warning: find_multiple_packages: 指定了 EXACT 但未提供 VERSION 或 VERSIONS。忽略 EXACT。")
        endif()

        # 检查 EXACTS 的有效性
        if(FMP_EXACTS)
            list(LENGTH FMP_EXACTS exacts_count)
            if(NOT exacts_count EQUAL packages_count)
                message(FATAL_ERROR "Error: find_multiple_packages: EXACTS 的数量(${exacts_count})与 PACKAGES 的数量(${packages_count})不一致！")
            endif()
            
            if(NOT FMP_VERSIONS)
                message(FATAL_ERROR "Error: find_multiple_packages: 使用 EXACTS 时必须同时指定 VERSIONS！")
            endif()
            
            # 验证 EXACTS 中的值是否都是 on 或 off
            foreach(exact_value IN LISTS FMP_EXACTS)
                if(NOT (exact_value STREQUAL "on" OR exact_value STREQUAL "off"))
                    message(FATAL_ERROR "Error: find_multiple_packages: EXACTS 中的值必须是 'on' 或 'off'，发现无效值: '${exact_value}'")
                endif()
            endforeach()
        endif()

        # 检查 VERSIONS 的有效性（如果提供）
        if(FMP_VERSIONS)
            list(LENGTH FMP_VERSIONS versions_count)
            if(NOT versions_count EQUAL packages_count)
                message(FATAL_ERROR "Error: find_multiple_packages: VERSIONS 的数量(${versions_count})与 PACKAGES 的数量(${packages_count})不一致！")
            endif()
        endif()

        # 检查 PUBLIC 和 PRIVATE 的互斥性
        if(FMP_PUBLIC AND FMP_PRIVATE)
            message(FATAL_ERROR "Error: find_multiple_packages: 不能同时指定 PUBLIC 和 PRIVATE！")
        endif()

        # 检查 TARGET 是否与 PUBLIC/PRIVATE 配套
        if((FMP_PUBLIC OR FMP_PRIVATE) AND NOT FMP_TARGET)
            message(FATAL_ERROR "Error: find_multiple_packages: 指定了 PUBLIC 或 PRIVATE 但未提供 TARGET！")
        endif()

        # 检查 TARGET 和 TARGET_DEPENDENCIES 是否同时提供
        if(FMP_TARGET AND NOT FMP_TARGET_DEPENDENCIES)
            message(FATAL_ERROR "Error: find_multiple_packages: 指定了 TARGET 但未提供 TARGET_DEPENDENCIES！")
        endif()

        # 构建 find_package 的基础参数列表（不包括版本号和EXACT）
        set(base_find_args "")
        if(FMP_REQUIRED)
            list(APPEND base_find_args REQUIRED)
        endif()
        if(FMP_PATHS)
            list(APPEND base_find_args PATHS ${FMP_PATHS})
        endif()

        # 遍历 PACKAGES 列表，依次查找每个包
        set(package_index 0)
        foreach(package IN LISTS FMP_PACKAGES)
            # 设置当前包的查找参数
            set(find_args ${base_find_args})
            set(has_version FALSE)
            set(version_str "")
            set(use_exact FALSE)
            
            # 判断使用哪个版本号及是否精确匹配
            if(FMP_VERSIONS)
                list(GET FMP_VERSIONS ${package_index} current_version)
                if(current_version)
                    set(has_version TRUE)
                    set(version_str "${current_version}")
                    
                    # 检查是否需要精确匹配
                    if(FMP_EXACTS)
                        list(GET FMP_EXACTS ${package_index} current_exact)
                        if(current_exact STREQUAL "on")
                            set(use_exact TRUE)
                        endif()
                    elseif(FMP_EXACT)
                        set(use_exact TRUE)
                    endif()
                endif()
            elseif(FMP_VERSION)
                set(has_version TRUE)
                set(version_str "${FMP_VERSION}")
                if(FMP_EXACT)
                    set(use_exact TRUE)
                endif()
            endif()
            
            # 添加 EXACT 参数（如果需要）
            if(use_exact AND has_version)
                list(APPEND find_args EXACT)
            endif()
            
            # 打印查找信息并执行查找
            if(has_version)
                if(use_exact)
                    message(STATUS "Info: find_multiple_packages正在查找包: ${package} ${version_str} (精确版本) 参数: ${find_args}")
                else()
                    message(STATUS "Info: find_multiple_packages正在查找包: ${package} ${version_str} 参数: ${find_args}")
                endif()
                find_package(${package} ${version_str} ${find_args})
            else()
                message(STATUS "Info: find_multiple_packages正在查找包: ${package} 参数: ${find_args}")
                find_package(${package} ${find_args})
            endif()
            
            math(EXPR package_index "${package_index} + 1")
        endforeach()

        # 如果指定了 TARGET，则将 TARGET_DEPENDENCIES 链接到指定目标
        if(FMP_TARGET)
            if(FMP_PUBLIC)
                # 以 PUBLIC 方式链接，依赖对目标的使用者可见
                target_link_libraries(${FMP_TARGET} PUBLIC ${FMP_TARGET_DEPENDENCIES})
                message(STATUS "Info: find_multiple_packages以 PUBLIC 方式将 ${FMP_TARGET_DEPENDENCIES} 链接到 ${FMP_TARGET}")
            elseif(FMP_PRIVATE)
                # 以 PRIVATE 方式链接，依赖对目标的使用者不可见
                target_link_libraries(${FMP_TARGET} PRIVATE ${FMP_TARGET_DEPENDENCIES})
                message(STATUS "Info: find_multiple_packages以 PRIVATE 方式将 ${FMP_TARGET_DEPENDENCIES} 链接到 ${FMP_TARGET}")
            else()
                # 未指定 PUBLIC 或 PRIVATE 时，默认使用 PRIVATE
                target_link_libraries(${FMP_TARGET} PRIVATE ${FMP_TARGET_DEPENDENCIES})
                message(STATUS "Info: find_multiple_packages以 PRIVATE 方式将 ${FMP_TARGET_DEPENDENCIES} 链接到 ${FMP_TARGET}（默认）")
            endif()
        endif()
    endmacro()

endif()