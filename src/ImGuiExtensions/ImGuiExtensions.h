#pragma once

#include <imgui.h>

#include "Sandbox/DataHandler.h"
#include "util/enum_to_c_str.h"

namespace ImGuiExtensions
{
	inline bool BeginProperties(const char* label)
	{
		bool result = ImGui::BeginTable(
			label,
			2,
			ImGuiTableFlags_NoSavedSettings |
			ImGuiTableFlags_SizingFixedFit |
			ImGuiTableFlags_NoPadOuterX);

		ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);

		return result;
	}

	inline void PropertiesLabel(const char* str)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();

		auto posX =
			(ImGui::GetCursorPosX() + ImGui::GetColumnWidth() -
			 ImGui::CalcTextSize(str).x);

		if (posX > ImGui::GetCursorPosX())
			ImGui::SetCursorPosX(posX);

		ImGui::Text(str);

		ImGui::TableNextColumn();
	}

	inline void EndProperties()
	{
		ImGui::EndTable();
	}

	template <typename T>
	inline void SelectableEnum(T& variable, std::initializer_list<T> values)
	{
		ImGui::PushID(std::addressof(variable));

		for (auto& value : values) {
			if (ImGui::Selectable(util::enum_to_c_str(value), variable == value)) {
				variable = value;
			}
		}

		ImGui::PopID();
	}

	template <typename T>
	inline void SelectableForm(T*& variable)
	{
		auto idHandler = Sandbox::DataHandler::GetSingleton();
		if (ImGui::Selectable("NONE", variable == nullptr)) {
			variable = nullptr;
		}

		auto& forms = RE::TESDataHandler::GetSingleton()->GetFormArray<T>();
		for (auto& form : forms) {
			if (ImGui::Selectable(idHandler->GetEditorID(form), variable == form)) {
				variable = form;
			}
			if (variable == form) {
				ImGui::SetItemDefaultFocus();
			}
		}
	}

	template <typename T>
	inline void PropertiesForm(const char* label, T*& variable)
	{
		ImGui::PushID(std::addressof(variable));

		PropertiesLabel(label);

		auto idHandler = Sandbox::DataHandler::GetSingleton();
		if (ImGui::BeginCombo("", idHandler->GetEditorID(variable))) {
			ImGui::SetKeyboardFocusHere();
			SelectableForm(variable);
			ImGui::EndCombo();
		}

		ImGui::PopID();
	}
}
