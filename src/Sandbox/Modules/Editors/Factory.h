#pragma once

#include "Sandbox/Modules/FormEditor.h"

namespace Sandbox::Modules::Editors
{
	namespace Factory
	{
		auto MakeEditor(RE::TESForm* a_form) -> std::unique_ptr<FormEditor::IEditor>;
	}
}
