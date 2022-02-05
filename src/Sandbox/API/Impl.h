#pragma once

#include "Sandbox/FunctionInterface.h"
#include "Sandbox/IModule.h"

namespace Sandbox::API
{
	namespace Impl
	{
		void Register(IModule* a_module);
		void AddFormEditor(RE::FormType a_formType, const char* a_name);
		void EditForm(RE::TESForm* a_form);
		auto GetFormEditorID(RE::TESForm* a_form) -> const char*;
	}

	inline constexpr auto MakeAPI() -> FunctionInterface
	{
		return FunctionInterface{
			.Register = &Impl::Register,
			.AddFormEditor = &Impl::AddFormEditor,
			.EditForm = &Impl::EditForm,
			.GetFormEditorID = &Impl::GetFormEditorID,
		};
	}
}
