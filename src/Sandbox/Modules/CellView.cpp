#include "Sandbox/Modules/CellView.h"

#include "Sandbox/DataHandler.h"

namespace Sandbox::Modules
{
	auto CellView::GetSingleton() -> CellView*
	{
		static CellView singleton{};
		return std::addressof(singleton);
	}

	void CellView::ShowGUI()
	{
		if (ImGui::Begin("Cell View")) {

			if (ImGui::BeginTable("##layout", 2, ImGuiTableFlags_NoSavedSettings)) {

				ImGui::TableNextColumn();
				CellList();

				ImGui::TableNextColumn();
				ObjectList();

				ImGui::EndTable();
			}
		}

		ImGui::End();
	}

	void CellView::CellList()
	{
		auto dataHandler = RE::TESDataHandler::GetSingleton();

		ImGui::Text("World Space");
		auto worldSpacePreview =
			_selectedWorldSpace
			? _selectedWorldSpace->GetFormEditorID()
			: "Interiors";

		if (ImGui::BeginCombo("##worldSpace", worldSpacePreview)) {

			if (ImGui::Selectable("Interiors", _selectedWorldSpace == nullptr)) {
				_selectedWorldSpace = nullptr;
			}

			if (dataHandler && !dataHandler->loadingFiles) {
				auto& worldSpaceArray = dataHandler->GetFormArray<RE::TESWorldSpace>();

				for (auto& worldSpace : worldSpaceArray) {

					if (ImGui::Selectable(
						worldSpace->GetFormEditorID(),
						_selectedWorldSpace == worldSpace)) {

						_selectedWorldSpace = worldSpace;
					}
				}
			}
			// TODO: World Spaces
			ImGui::EndCombo();
		}

		ImGui::BeginChild("Cell List");
		if (ImGui::BeginTable(
			"##cellList",
			4,
			ImGuiTableFlags_Resizable |
			ImGuiTableFlags_NoSavedSettings |
			ImGuiTableFlags_Borders)) {

			ImGui::TableSetupColumn("EditorID");
			ImGui::TableSetupColumn("FormID");
			ImGui::TableSetupColumn("Name");
			// TODO: Loaded
			// TODO: Coords
			ImGui::TableSetupColumn("Location");
			// TODO: Owner
			ImGui::TableHeadersRow();

			if (dataHandler && !dataHandler->loadingFiles) {
				if (!_selectedWorldSpace) {
					auto& cellArray = dataHandler->interiorCells;

					for (auto& cell : cellArray) {
						CellRow(cell);
					}
				}
				else {
					auto& cellMap = _selectedWorldSpace->cellMap;

					for (auto& [cellId, cell] : cellMap) {
						CellRow(cell);
					}
				}
			}

			ImGui::EndTable();
		}
		ImGui::EndChild();
	}

	void CellView::ObjectList()
	{
		ImGui::Text(_selectedCell ? _selectedCell->GetFormEditorID() : "No Cell Selected");

		_objectFilter.Draw();

		ImGui::BeginChild("Object List");
		if (ImGui::BeginTable("##objectList", 2, ImGuiTableFlags_NoSavedSettings)) {
			ImGui::TableSetupColumn("Editor ID");
			ImGui::TableSetupColumn("Form ID");
			ImGui::TableHeadersRow();
			// TODO: Type
			// TODO: Ownership
			// TODO: Lock Level
			// TODO: Loc Ref Type
			// TODO: Persist Location
			// TODO: Initially Disabled
			// TODO: LeveledItem
			if (_selectedCell) {
				auto idHandler = DataHandler::GetSingleton();
				for (auto& refr : _selectedCell->references) {
					ImGui::TableNextRow();
					auto editorId = idHandler->GetEditorID(refr->GetBaseObject());

					if (!_objectFilter.PassFilter(editorId)) {
						continue;
					}

					ImGui::TableNextColumn();
					if (ImGui::Selectable(
						editorId,
						_selectedRef == refr,
						ImGuiSelectableFlags_SpanAllColumns)) {

						_selectedRef = refr;
					}

					ImGui::TableNextColumn();
					ImGui::Text(fmt::format("{:08X}"sv, refr->GetFormID()).data());
				}
			}
			ImGui::EndTable();
		}
		ImGui::EndChild();
	}

	void CellView::CellRow(RE::TESObjectCELL* a_cell)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		if (ImGui::Selectable(
			a_cell->GetFormEditorID(),
			a_cell == _selectedCell,
			ImGuiSelectableFlags_SpanAllColumns |
			ImGuiSelectableFlags_AllowDoubleClick)) {

			_selectedCell = a_cell;

			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
				SKSE::GetTaskInterface()->AddTask(
					[a_cell]
					{
						if (auto playerCharacter = RE::PlayerCharacter::GetSingleton())
							playerCharacter->CenterOnCell(a_cell);
					});
			}
		}

		ImGui::TableNextColumn();
		ImGui::Text(fmt::format("{:08X}"sv, a_cell->GetFormID()).data());

		ImGui::TableNextColumn();
		ImGui::Text(a_cell->GetName());

		// Loaded
		// Coords

		ImGui::TableNextColumn();
		auto extraLocation = a_cell->extraList.GetByType<RE::ExtraLocation>();
		auto location = extraLocation ? extraLocation->location : nullptr;
		ImGui::Text(DataHandler::GetSingleton()->GetEditorID(location));

		// Owner
	}
}
