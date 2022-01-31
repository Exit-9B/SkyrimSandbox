#pragma once

#include "Sandbox/IModule.h"

namespace Sandbox
{
	class ModuleManager
	{
	public:
		static auto GetSingleton() -> ModuleManager*;

		void Register(IModule* a_module);
		void VisitModules(std::function<void(IModule*)> a_visitor);

		void AddFormEditor(RE::FormType a_formType, std::string_view a_name);
		void EditForm(RE::TESForm* a_form);

	private:
		std::vector<IModule*> _modules;
		std::unordered_multimap<RE::FormType, std::string> _availableEditors;
		std::unordered_map<RE::FormType, std::string> _selectedEditors;
	};
}
