#include "Sandbox/Modules/FormEditor.h"

#include "Sandbox/Modules/Editors/Factory.h"

namespace Sandbox::Modules
{
	auto FormEditor::GetSingleton() -> FormEditor*
	{
		static FormEditor singleton{};
		return std::addressof(singleton);
	}

	void FormEditor::ShowGUI()
	{
		if (_currentEditor) {
			_currentEditor->ShowGUI();
		}
	}

	void FormEditor::OpenEditor(RE::TESForm* a_form)
	{
		// TODO: Make it possible to edit multiple forms
		_currentEditor = Editors::Factory::MakeEditor(a_form);
	}
}
