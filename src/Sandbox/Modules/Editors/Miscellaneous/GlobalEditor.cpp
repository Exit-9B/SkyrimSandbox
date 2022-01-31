#include "Sandbox/Modules/Editors/Miscellaneous/GlobalEditor.h"

#include "util/enum_to_c_str.h"

namespace Sandbox::Modules::Editors
{
	GlobalEditor::GlobalEditor(RE::TESGlobal* a_form) : EditorBase(a_form)
	{
		_type = a_form->type.get();
		_value = a_form->value;
		_constant = a_form->formFlags & RE::TESGlobal::RecordFlags::kConstant;
	}

	void GlobalEditor::ShowGUI()
	{
		if (!_open)
			return;

		if (ImGui::Begin(util::enum_to_c_str(FORMTYPE), &_open)) {
			ImGui::Text(_form->GetFormEditorID());

			ImGui::Text("Variable Type");
			if (ImGui::RadioButton("Short", _form->type == RE::TESGlobal::Type::kShort)) {
				_form->type = RE::TESGlobal::Type::kShort;
			}

			ImGui::SameLine();
			if (ImGui::RadioButton("Long", _form->type == RE::TESGlobal::Type::kLong)) {
				_form->type = RE::TESGlobal::Type::kLong;
			}

			ImGui::SameLine();
			if (ImGui::RadioButton("Float", _form->type == RE::TESGlobal::Type::kFloat)) {
				_form->type = RE::TESGlobal::Type::kFloat;
			}

			ImGui::Text("Value");
			ImGui::SameLine();
			ImGui::InputFloat(
				"##value",
				&_form->value,
				0.0f,
				0.0f,
				"%.6f",
				ImGuiInputTextFlags_EnterReturnsTrue);

			ImGui::CheckboxFlags(
				"Constant",
				&_form->formFlags,
				RE::TESGlobal::RecordFlags::kConstant);

			if (ImGui::Button("OK")) {
				Apply();
				_open = false;
			}

			if (ImGui::Button("Cancel")) {
				_open = false;
			}

		}
		ImGui::End();
	}

	void GlobalEditor::Apply()
	{
		_form->type = _type;
		_form->value = _value;
		if (_constant) {
			_form->formFlags |= RE::TESGlobal::RecordFlags::kConstant;
		}
		else {
			_form->formFlags &= ~RE::TESGlobal::RecordFlags::kConstant;
		}
	}
}
