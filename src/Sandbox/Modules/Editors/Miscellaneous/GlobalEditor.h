#pragma once

#include "Sandbox/Modules/FormEditor.h"

namespace Sandbox::Modules::Editors
{
	class GlobalEditor : public FormEditor::EditorBase<RE::TESGlobal>
	{
	public:
		GlobalEditor(RE::TESGlobal* a_form);

		void ShowGUI() override;

		void Apply();

	private:
		RE::TESGlobal::Type _type;
		float _value;
		bool _constant;
	};
}
