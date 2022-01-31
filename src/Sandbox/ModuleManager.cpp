#include "Sandbox/ModuleManager.h"

#include "Sandbox/Message.h"

namespace Sandbox
{
	auto ModuleManager::GetSingleton() -> ModuleManager*
	{
		static ModuleManager singleton{};
		return std::addressof(singleton);
	}

	void ModuleManager::Register(IModule* a_module)
	{
		_modules.push_back(a_module);
	}

	void ModuleManager::VisitModules(std::function<void(IModule*)> a_visitor)
	{
		for (auto& mod : _modules) {
			a_visitor(mod);
		}
	}

	void ModuleManager::AddFormEditor(RE::FormType a_formType, std::string_view a_name)
	{
		_availableEditors.insert({ a_formType, std::string{ a_name } });
		_selectedEditors[a_formType] = a_name;
	}

	void ModuleManager::EditForm(RE::TESForm* a_form)
	{
		auto it = _selectedEditors.find(a_form->GetFormType());

		if (it != _selectedEditors.end()) {

			auto receiver = it->second.data();

			SKSE::GetMessagingInterface()->Dispatch(
				Message::kEditForm,
				std::addressof(a_form),
				sizeof(RE::TESForm*),
				receiver);
		}

		// TODO: Display an error when no editor is available
	}
}
