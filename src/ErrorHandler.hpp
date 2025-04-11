#pragma once
#include "RootDefines.hpp"
#include "dto/StatusDto.hpp"

/**
 * @brief 错误处理器类, 用于处理 Web 请求中的错误情况。
 * @details 当发生错误时，该处理器可以自定义返回的响应格式，以满足客户端需求。
 */
class ErrorHandler : public WebErrorHandler {

private:
	// 用于对象序列化的 ObjectMapper 组件
	std::shared_ptr<ObjectMapper> m_objectMapper;

public:
	/** 构造函数 ErrorHandler **/
	explicit ErrorHandler(const shared_ptr<ObjectMapper>& objectMapper);

	/**
	 * @brief 处理错误
	 * @details 根据传入的错误状态、消息及头信息，构造并返回相应的 OutgoingResponse 对象。
	 * @param status 错误状态信息
	 * @param message 错误详细信息
	 * @param headers HTTP 头信息
	 * @return 处理后的 OutgoingResponse 响应对象
	 */
	shared_ptr<OutgoingResponse> handleError(const Status& status, const String& message, const Headers& headers) override;

};