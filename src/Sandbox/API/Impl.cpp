#include "Sandbox/API/Impl.h"

#include "Sandbox/DataHandler.h"
#include "Sandbox/ModuleManager.h"

namespace Sandbox::API
{
	void Impl::Register(IModule* a_module)
	{
		ModuleManager::GetSingleton()->Register(a_module);
	}

	void Impl::AddFormEditor(RE::FormType a_formType, const char* a_name)
	{
		ModuleManager::GetSingleton()->AddFormEditor(a_formType, a_name);
	}

	void Impl::EditForm(RE::TESForm* a_form)
	{
		ModuleManager::GetSingleton()->EditForm(a_form);
	}

	auto Impl::GetFormEditorID(RE::TESForm* a_form) -> const char*
	{
		return DataHandler::GetSingleton()->GetEditorID(a_form);
	}
}
