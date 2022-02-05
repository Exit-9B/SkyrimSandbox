#pragma once

#include "Sandbox/IModuleBase.h"

#include <imgui.h>

namespace Sandbox
{
	/* Sandbox Module interface
	 */
	class IModule : public IModuleBase
	{
	public:
		virtual ~IModule() { }

		virtual void ShowGUI() = 0;
	};
}
