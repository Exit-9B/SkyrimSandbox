#include "Sandbox/API/Impl.h"

#include "Sandbox/DataHandler.h"
#include "Sandbox/ModuleManager.h"

namespace Sandbox::API
{
	void Impl::Register(IModule* a_module)
	{
		ModuleManager::GetSingleton()->Register(a_module);
	}

	void Impl::AddFormEditor(std::int32_t a_formType, const char* a_name)
	{
		ModuleManager::GetSingleton()->AddFormEditor(
			static_cast<RE::FormType>(a_formType),
			a_name);
	}

	void Impl::EditForm(void* a_form)
	{
		ModuleManager::GetSingleton()->EditForm(
			reinterpret_cast<RE::TESForm*>(a_form));
	}

	auto Impl::GetFormEditorID(void* a_form) -> const char*
	{
		return DataHandler::GetSingleton()->GetEditorID(static_cast<RE::TESForm*>(a_form));
	}
}
