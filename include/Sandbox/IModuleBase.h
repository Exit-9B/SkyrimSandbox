#pragma once

#include <cstdint>

namespace Sandbox
{
	class IModuleBase
	{
	public:
		IModuleBase() : APIVersion(1) { }
		virtual ~IModuleBase() { }
		std::int32_t GetAPIVersion() const { return APIVersion; }

	private:
		const std::int32_t APIVersion;
	};
}
