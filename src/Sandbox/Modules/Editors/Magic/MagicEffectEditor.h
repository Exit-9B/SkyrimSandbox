#pragma once

#include "Sandbox/Modules/FormEditor.h"

namespace Sandbox::Modules::Editors
{
	class MagicEffectEditor : public FormEditor::EditorBase<RE::EffectSetting>
	{
	public:
		MagicEffectEditor(RE::EffectSetting* a_form);

		void ShowGUI() override;

		void Apply();

		void EffectOptions(const char* a_label);
		void NumericalData(const char* a_label);
		void Flags(const char* a_label);
		void Keywords(const char* a_label);
		void CounterEffects(const char* a_label);

		void TargetConditions(const char* a_label);

		void MenuDisplayObject(const char* a_label);
		void VisualEffects(const char* a_label);
		void DualCasting(const char* a_label);
		void Spellmaking(const char* a_label);
		void ScriptEffectAIData(const char* a_label);
		void EquipAbility(const char* a_label);

		void Sounds(const char* a_label);
		void PapyrusScripts(const char* a_label);

		void EffectArchetype(const char* a_label);
		void CastingType(const char* a_label);
		void Delivery(const char* a_label);
		void MagicSkill(const char* a_label);
		void ResistValue(const char* a_label);
		void PerkToApply(const char* a_label);

	private:
		using EffectFlag = RE::EffectSetting::EffectSettingData::Flag;

		std::string _name;
		std::vector<RE::BGSKeyword*> _keywords;
		RE::TESBoundObject* _menuDispObject;

		RE::EffectSetting::EffectSettingData _data;
		RE::BSSimpleList<RE::EffectSetting*> _counterEffects;
		RE::EffectSetting::SoundPair _effectSounds[6];
		std::string _magicItemDescription;
		RE::TESCondition conditions;
	};
}
