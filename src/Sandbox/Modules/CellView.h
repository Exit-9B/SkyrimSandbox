#pragma once

#include "Sandbox/IModule.h"

namespace Sandbox::Modules
{
	class CellView : public IModule
	{
	public:
		~CellView() override = default;
		CellView(const CellView&) = delete;
		CellView(CellView&&) = delete;
		CellView& operator=(const CellView&) = delete;
		CellView& operator=(CellView&&) = delete;

		void ShowGUI() override;

		static auto GetSingleton() -> CellView*;

	private:
		CellView() = default;

		void CellList();
		void ObjectList();

		void CellRow(RE::TESObjectCELL* a_cell);

		RE::TESWorldSpace* _selectedWorldSpace;
		RE::TESObjectCELL* _selectedCell;
		RE::TESObjectREFRPtr _selectedRef;
		ImGuiTextFilter _objectFilter;
	};
}
