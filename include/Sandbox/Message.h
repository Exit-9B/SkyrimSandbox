#pragma once

#include <cstdint>

namespace Sandbox
{
	struct Message
	{
		enum MessageType : std::uint32_t
		{
			kShareAPI,
			kEditForm,
		};
	};
}
