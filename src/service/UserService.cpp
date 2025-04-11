#pragma execution_character_set("utf-8")
#include "UserService.hpp"
using namespace oatpp;

Object<UserDto> UserService::login(const Object<UserDto> &dto) const {
    auto dbResult = m_database->getUserById(dto->id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage())
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "未找到用户")

    auto result = dbResult->fetch<Vector<Object<UserDto >>> ();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "未知错误")
    auto value = result[0].get();
    // TODO: 魔法值Token
    value->token = "4e99e8c12de7e01535248d2bac85e732";
    return result[0];
}

Object<UserDto> UserService::createUser(const Object<UserDto> &dto) const {

    auto dbResult = m_database->createUser(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage())

    auto userId = sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getUserById(static_cast<v_int32>(userId));

}

Object<UserDto> UserService::updateUser(const Object<UserDto> &dto) const {
    auto dbResult = m_database->updateUser(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage())
    return getUserById(dto->id);
}

Object<UserDto> UserService::getUserById(const Int32& id, const ResourceHandle<Connection> &connection) const {
    auto dbResult = m_database->getUserById(id, connection);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage())
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "未找到用户")

    auto result = dbResult->fetch<Vector<Object<UserDto >>> ();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "未知错误")

    return result[0];
}

Object<PageDto<Object<UserDto >>> UserService::getAllUsers(const UInt32& offset, const UInt32& limit) const {
    UInt32 countToFetch = limit;

    if(limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getAllUsers(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage())

    auto items = dbResult->fetch<Vector<Object<UserDto >>> ();

    auto page = PageDto<Object<UserDto >>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

Object<StatusDto> UserService::deleteUserById(const Int32& userId) const {
    auto dbResult = m_database->deleteUserById(userId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage())
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "成功删除用户";
    return status;
}
