#include "Sandbox/API/Messaging.h"

#include "Sandbox/API/Impl.h"
#include "Sandbox/Message.h"

namespace Sandbox::API
{
	namespace Messaging
	{
		void ShareAPI()
		{
			static auto api = MakeAPI();

			SKSE::GetMessagingInterface()->Dispatch(
				Message::kShareAPI,
				std::addressof(api),
				sizeof(FunctionInterface),
				nullptr);
		}
	}
}
