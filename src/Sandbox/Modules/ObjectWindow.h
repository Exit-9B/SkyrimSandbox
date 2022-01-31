#pragma once

#include "Sandbox/IModule.h"

namespace Sandbox::Modules
{
	class ObjectWindow : public IModule
	{
	public:
		~ObjectWindow() override = default;
		ObjectWindow(const ObjectWindow&) = delete;
		ObjectWindow(ObjectWindow&&) = delete;
		ObjectWindow& operator=(const ObjectWindow&) = delete;
		ObjectWindow& operator=(ObjectWindow&&) = delete;

		void ShowGUI() override;

		static auto GetSingleton() -> ObjectWindow*;

	private:
		ObjectWindow() = default;

		void Filters();
		void Forms();
		void SetupColumns(RE::FormType a_formType);

		void Row(
			RE::FormType a_formType,
			RE::TESForm* a_form,
			const ImGuiTextFilter* a_filter,
			RE::TESFile* a_fileFilter);

		ImGuiTextFilter _filter;
		RE::TESFile* _fileFilter = nullptr;
		RE::FormType _formType = RE::FormType::None;
	};
}
