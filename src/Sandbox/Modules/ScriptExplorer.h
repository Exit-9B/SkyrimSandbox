#pragma once

#include "Sandbox/IModule.h"

namespace Sandbox::Modules
{
	class ScriptExplorer final : public IModule
	{
	public:
		~ScriptExplorer() override = default;
		ScriptExplorer(const ScriptExplorer&) = delete;
		ScriptExplorer(ScriptExplorer&&) = delete;
		ScriptExplorer& operator=(const ScriptExplorer&) = delete;
		ScriptExplorer& operator=(ScriptExplorer&&) = delete;

		static auto GetSingleton() -> ScriptExplorer*;

		void ShowGUI() override;

	private:
		ScriptExplorer() = default;

		RE::VMHandle _selectedHandle = static_cast<RE::VMHandle>(-1);
	};
}
