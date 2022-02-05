#include "Sandbox/Modules/ScriptExplorer.h"

#include "Sandbox/DataHandler.h"

namespace Sandbox::Modules
{
	auto ScriptExplorer::GetSingleton() -> ScriptExplorer*
	{
		static ScriptExplorer singleton{};
		return std::addressof(singleton);
	}

	void ScriptExplorer::ShowGUI()
	{
		if (ImGui::Begin("Script Explorer")) {

			ImGui::Text("Attached scripts");

			if (ImGui::BeginTable(
				"##scripts",
				2,
				ImGuiTableFlags_NoSavedSettings |
				ImGuiTableFlags_Borders)) {

				ImGui::TableSetupColumn("Script Name");
				ImGui::TableSetupColumn("Object");
				ImGui::TableHeadersRow();

				if (auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton()) {

					auto idHandler = DataHandler::GetSingleton();

					auto guard = RE::BSSpinLockGuard{ vm->attachedScriptsLock };
					for (auto& [handle, attachedScriptArray] : vm->attachedScripts) {

						for (auto& script : attachedScriptArray) {

							ImGui::TableNextRow();

							auto form = static_cast<RE::TESForm*>(script->Resolve(0));
							auto alias = static_cast<RE::BGSBaseAlias*>(
								script->Resolve(RE::BGSBaseAlias::VMTYPEID));
							[[maybe_unused]] auto effect = static_cast<RE::ActiveEffect*>(
								script->Resolve(RE::ActiveEffect::VMTYPEID));
							auto scriptName = script->GetTypeInfo()->GetName();

							ImGui::TableNextColumn();

							if (ImGui::Selectable(
								scriptName,
								_selectedHandle == handle,
								ImGuiSelectableFlags_SpanAllColumns)) {

								_selectedHandle = handle;
							}

							ImGui::TableNextColumn();

							if (form) {
								if (auto refr = form->As<RE::TESObjectREFR>()) {
									auto baseID = idHandler->GetEditorID(refr->GetBaseObject());
									ImGui::Text("Reference: %s", baseID);
								}
								else {
									auto objectID = idHandler->GetEditorID(form);
									ImGui::Text(objectID);
								}
							}
							else if (alias) {
								auto aliasName = alias->aliasName.data();
								auto questID = idHandler->GetEditorID(alias->owningQuest);
								ImGui::Text("Alias: %s (Quest: %s)", aliasName, questID);
							}
						}
					}
				}
				ImGui::EndTable();
			}
		}

		ImGui::End();
	}
}
