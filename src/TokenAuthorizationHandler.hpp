#pragma once
#include "./controller/ControllerDefines.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)

class TokenAuthorizationObject : public AuthorizationObject {
public:
	TokenAuthorizationObject(String pUserId) : userId(move(pUserId)) {}
	String userId;
};

class TokenAuthorizationHandler : public BearerAuthorizationHandler {

public:
	TokenAuthorizationHandler() : BearerAuthorizationHandler("my-realm") {}

	shared_ptr<AuthorizationObject> authorize(const String& token) override {
		printf("authorize token %s", token.getValue("").c_str());
		if (token == "4e99e8c12de7e01535248d2bac85e732") {
			return make_shared<TokenAuthorizationObject>("uid-admin");
		}
		return nullptr;
	}

	shared_ptr<AuthorizationObject> handleAuthorization(const String& header) override
	{

		OATPP_LOGD("TokenAuthorizationHandler", "handleAuthorization token '%s'", header.getValue("666").c_str());
		int a = header->size();
		if (header && header->size() > 6 && oatpp::utils::String::compare(header->data(), 6, "Token ", 6) == 0) {

			String token = String(header->c_str() + 6, header->size() - 6);

			auto authResult = authorize(token);
			if (authResult) {
				return authResult;
			}

			// OATPP_ASSERT_HTTP(false, Status::CODE_401, "Unauthorized");
			OATPP_ASSERT_HTTP(false, Status::CODE_401, "Unauthorized");
		}

		OATPP_ASSERT_HTTP(false, Status::CODE_401, "The authorization is required. Login");
	}
};
#include OATPP_CODEGEN_END(ApiController)
