#include "Sandbox/Modules/Editors/Magic/MagicEffectEditor.h"

#include "ImGuiExtensions/ImGuiExtensions.h"
#include "Sandbox/DataHandler.h"
#include "util/enum_to_c_str.h"

#include <imgui_stdlib.h>

namespace Sandbox::Modules::Editors
{
	MagicEffectEditor::MagicEffectEditor(RE::EffectSetting* a_form) : EditorBase(a_form)
	{
		_name = a_form->GetFullName();
		_keywords = std::vector<RE::BGSKeyword*>(
			a_form->keywords,
			a_form->keywords + a_form->numKeywords);
		_menuDispObject = a_form->menuDispObject;

		_data = a_form->data;

		for (auto& soundPair : a_form->effectSounds) {
			_effectSounds[static_cast<std::size_t>(soundPair.id)] = soundPair;
		}

		_magicItemDescription = a_form->magicItemDescription;
	}

	void MagicEffectEditor::ShowGUI()
	{
		if (!_open)
			return;

		if (ImGui::Begin(util::enum_to_c_str(FORMTYPE), &_open)) {

			if (ImGui::BeginTable("##effectLayout", 2, ImGuiTableFlags_NoSavedSettings)) {

				ImGui::TableSetupColumn("##col1", ImGuiTableColumnFlags_WidthStretch, 1.0f);
				ImGui::TableSetupColumn("##col2", ImGuiTableColumnFlags_WidthStretch, 2.0f);

				ImGui::TableNextColumn();
				EffectOptions("##effectOptions");
				NumericalData("##numericalData");
				Flags("##flags");
				Keywords("##keywords");
				CounterEffects("##counterEffects");

				ImGui::TableNextColumn();
				TargetConditions("##targetConditions");

				if (ImGui::BeginTable("##details", 2, ImGuiTableFlags_NoSavedSettings)) {

					ImGui::TableNextColumn();
					MenuDisplayObject("##menuDisplayObject");
					VisualEffects("##visualEffects");
					DualCasting("##dualCasting");
					Spellmaking("##spellmaking");
					ScriptEffectAIData("##scriptEffectAIData");
					EquipAbility("##equipAbility");

					if (ImGui::Button("OK")) {
						Apply();
						_open = false;
					}
					ImGui::SameLine();
					if (ImGui::Button("Cancel")) {
						_open = false;
					}

					ImGui::TableNextColumn();
					Sounds("##sounds");
					ImGui::Text("Magic item description");
					ImGui::InputTextMultiline("##magicItemDescription", &_magicItemDescription);
					PapyrusScripts("##papyrusScripts");

					ImGui::EndTable();
				}

				ImGui::EndTable();
			}
		}
		ImGui::End();
	}

	void MagicEffectEditor::Apply()
	{
		_form->fullName = _name;
		// TODO: Keywords
		_form->data = _data;

		// TODO: Fix sound assignment
		for (auto& soundPair : _form->effectSounds) {
			soundPair.sound = _effectSounds[static_cast<std::size_t>(soundPair.id)].sound;
		}

		_form->magicItemDescription = _magicItemDescription;
	}

	void MagicEffectEditor::EffectOptions(const char* a_label)
	{
		if (ImGuiExtensions::BeginProperties(a_label)) {
			ImGuiExtensions::PropertiesLabel("ID");
			ImGui::LabelText("##id", DataHandler::GetSingleton()->GetEditorID(_form));

			ImGuiExtensions::PropertiesLabel("Name");
			ImGui::InputText("##name", &_name);

			ImGuiExtensions::PropertiesLabel("Effect Archetype");
			EffectArchetype("##effectArchetype");

			ImGuiExtensions::PropertiesLabel("Casting Type");
			CastingType("##castingType");

			ImGuiExtensions::PropertiesLabel("Delivery");
			Delivery("##delivery");

			ImGuiExtensions::PropertiesLabel("Magic Skill");
			MagicSkill("##magicSkill");

			ImGuiExtensions::PropertiesLabel("Minimum Skill Level");
			ImGui::InputInt("##minimumSkill", &_data.minimumSkill, 0);

			// TODO: Assoc. Item 1
			ImGuiExtensions::PropertiesLabel("Assoc. Item 1");
			if (ImGui::BeginCombo("##assocItem1", "NONE")) {
				ImGui::EndCombo();
			}

			ImGuiExtensions::PropertiesLabel("Assoc. Item 2");
			ImGui::BeginDisabled();
			if (ImGui::BeginCombo("##assocItem1", "")) {
				ImGui::EndCombo();
			}
			ImGui::EndDisabled();

			ImGuiExtensions::PropertiesLabel("2nd AV Weight");
			ImGui::BeginDisabled();
			ImGui::InputFloat("##secondAVWeight", &_data.secondAVWeight, 0.0f, 0.0f, "%.6f");
			ImGui::EndDisabled();

			ImGuiExtensions::PropertiesLabel("Resist Value");
			ResistValue("##resistValue");

			ImGuiExtensions::PropertiesLabel("Perk to Apply");
			PerkToApply("##perkToApply");

			ImGuiExtensions::EndProperties();
		}
	}

	void MagicEffectEditor::NumericalData(const char* a_label)
	{
		if (ImGui::BeginTable(a_label, 2, ImGuiTableFlags_NoSavedSettings)) {

			ImGui::TableNextColumn();
			if (ImGuiExtensions::BeginProperties("##taper")) {
				ImGuiExtensions::PropertiesLabel("Taper Duration");
				ImGui::InputFloat("##taperDuration", &_data.taperDuration, 0.0f, 0.0f, "%.2f");

				ImGuiExtensions::PropertiesLabel("Taper Weight");
				ImGui::InputFloat("##taperWeight", &_data.taperWeight, 0.0f, 0.0f, "%.2f");

				ImGuiExtensions::PropertiesLabel("Taper Curve");
				ImGui::InputFloat("##taperCurve", &_data.taperCurve, 0.0f, 0.0f, "%.2f");

				ImGuiExtensions::EndProperties();
			}

			ImGui::TableNextColumn();
			if (ImGuiExtensions::BeginProperties("##cost")) {

				ImGuiExtensions::PropertiesLabel("Base Cost");
				ImGui::InputFloat("##baseCost", &_data.taperDuration, 0.0f, 0.0f, "%.4f");

				ImGuiExtensions::PropertiesLabel("Skill Usage Mult");
				ImGui::InputFloat("##skillUsageMult", &_data.taperWeight, 0.0f, 0.0f, "%.4f");

				ImGuiExtensions::EndProperties();
			}

			ImGui::EndTable();
		}
	}

	void MagicEffectEditor::Flags(const char* a_label)
	{
		ImGui::Text("Flags");
		if (ImGui::BeginChild(a_label, ImVec2(0, 132), true)) {

			if (ImGui::BeginTable("##flagsTable", 3, ImGuiTableFlags_NoSavedSettings)) {

				auto flagsPtr = reinterpret_cast<std::uint32_t*>(&_data.flags);

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"Hostile",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kHostile));

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"No Recast",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kNoRecast));

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"No Magnitude",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kNoMagnitude));

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"Detrimental",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kDetrimental));

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"No Hit Effect",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kNoHitEffect));

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"No Area",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kNoArea));

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"Recover",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kRecover));

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"No Death Dispel",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kNoDeathDispel));

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"Painless",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kPainless));

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"FX Persist",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kFXPersist));

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"No Duration",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kNoDuration));

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"Gory Visuals",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kGoryVisuals));

				ImGui::BeginDisabled();
				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"Snap to Navmesh",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kSnapToNavMesh));
				ImGui::EndDisabled();

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"No Hit Event",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kNoHitEvent));

				ImGui::TableNextColumn();
				ImGui::CheckboxFlags(
					"Hide in UI",
					flagsPtr,
					static_cast<std::uint32_t>(EffectFlag::kHideInUI));

				ImGui::EndTable();
			}
		}

		ImGui::EndChild();
	}

	void MagicEffectEditor::Keywords(const char*)
	{
		ImGui::Text("Keywords");
		ImGui::SameLine();
		ImGui::CheckboxFlags(
			"Dispel Effects with these Keywords:",
			reinterpret_cast<std::uint32_t*>(&_data.flags),
			static_cast<std::uint32_t>(EffectFlag::kDispelWithKeywords));

		if (ImGui::BeginTable(
			"##keywords",
			1,
			ImGuiTableFlags_Borders |
			ImGuiTableFlags_NoSavedSettings)) {

			ImGui::TableSetupColumn("Editor ID");
			ImGui::TableHeadersRow();

			std::uint32_t selected = UINT_MAX;
			std::uint32_t i = 0;
			for (std::size_t size = _keywords.size(); i < size; i++) {
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Selectable(_keywords[i]->GetFormEditorID(), selected == i);
			}
			for (; i < 3; i++) {
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Dummy(ImVec2(0, ImGui::GetTextLineHeight()));
			}
			// TODO: Edit Keywords

			ImGui::EndTable();
		}
	}

	void MagicEffectEditor::CounterEffects(const char*)
	{
		// TODO: Counter Effects
	}

	void MagicEffectEditor::TargetConditions(const char* a_label)
	{
		ImGui::Text("Target Conditions");
		if (ImGui::BeginTable(
			a_label,
			5,
			ImGuiTableFlags_Resizable |
			ImGuiTableFlags_NoSavedSettings |
			ImGuiTableFlags_Borders |
			ImGuiTableFlags_SizingStretchProp)) {

			ImGui::TableSetupColumn("Target", ImGuiTableColumnFlags_None, 1.0f);
			ImGui::TableSetupColumn("Function Name", ImGuiTableColumnFlags_None, 4.0f);
			ImGui::TableSetupColumn("Function Info", ImGuiTableColumnFlags_None, 3.0f);
			ImGui::TableSetupColumn("Comp", ImGuiTableColumnFlags_None, 1.5f);
			ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_None, 2.0f);
			ImGui::TableHeadersRow();

			// TODO: Target Conditions
			for (std::uint32_t i = 0; i < 4; i++) {
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Dummy(ImVec2(0, ImGui::GetTextLineHeight()));
			}

			ImGui::EndTable();
		}
	}

	void MagicEffectEditor::MenuDisplayObject(const char* a_label)
	{
		if (ImGuiExtensions::BeginProperties(a_label)) {
			ImGuiExtensions::PropertiesForm("Menu Display Object", _menuDispObject);
			ImGuiExtensions::EndProperties();
		}
	}

	void MagicEffectEditor::VisualEffects(const char* a_label)
	{
		ImGui::Text("Visual Effects");
		if (ImGui::BeginChild(a_label, ImVec2(0, 246), true)) {

			if (ImGuiExtensions::BeginProperties("##visualsProps")) {

				ImGuiExtensions::PropertiesForm("Casting Art", _data.castingArt);
				ImGuiExtensions::PropertiesForm("Casting Light", _data.light);
				ImGuiExtensions::PropertiesForm("Hit Effect Art", _data.hitEffectArt);
				ImGuiExtensions::PropertiesForm("Hit Shader", _data.hitVisuals);
				ImGuiExtensions::PropertiesForm("Enchant Art", _data.enchantEffectArt);
				ImGuiExtensions::PropertiesForm("Enchant Shader", _data.enchantVisuals);
				ImGuiExtensions::PropertiesForm("Projectile", _data.projectileBase);
				ImGuiExtensions::PropertiesForm("Impact Data Set", _data.impactDataSet);
				ImGuiExtensions::PropertiesForm("Explosion", _data.explosion);
				ImGuiExtensions::PropertiesForm("Image Space Mod", _data.imageSpaceMod);

				ImGui::EndTable();
			}
		}

		ImGui::EndChild();
	}

	void MagicEffectEditor::DualCasting(const char* a_label)
	{
		ImGui::Text("Dual Casting");
		if (ImGui::BeginChild(a_label, ImVec2(0, 66), true)) {

			if (ImGuiExtensions::BeginProperties("##dualCastingProps")) {

				// TODO: Fix Dual Casting Art
				if (_data.dualCastData) {
					ImGuiExtensions::PropertiesForm("Art", _data.dualCastData->data.pHitEffectArt);
				}
				else {
					ImGuiExtensions::PropertiesLabel("Art");
					ImGui::BeginDisabled();
					ImGui::BeginCombo("##art", "");
					ImGui::EndDisabled();
				}

				ImGuiExtensions::PropertiesLabel("Scale");
				ImGui::InputFloat("##scale", &_data.dualCastScale);

				ImGuiExtensions::EndProperties();
			}
		}

		ImGui::EndChild();
	}

	void MagicEffectEditor::Spellmaking(const char* a_label)
	{
		ImGui::Text("Spellmaking");
		if (ImGui::BeginChild(a_label, ImVec2(0, 90), true)) {
			ImGui::Text("Power Affects");
			ImGui::SameLine();
			ImGui::CheckboxFlags(
				"Magnitude",
				reinterpret_cast<std::uint32_t*>(&_data.flags),
				static_cast<std::uint32_t>(EffectFlag::kPowerAffectsMagnitude));
			ImGui::SameLine();
			ImGui::CheckboxFlags(
				"Duration",
				reinterpret_cast<std::uint32_t*>(&_data.flags),
				static_cast<std::uint32_t>(EffectFlag::kPowerAffectsDuration));

			if (ImGuiExtensions::BeginProperties("##spellmakingProps")) {
				ImGuiExtensions::PropertiesLabel("Area");
				ImGui::InputInt("##area", &_data.spellmakingArea, 0);

				ImGuiExtensions::PropertiesLabel("Casting Time");
				ImGui::InputFloat("##castingTime", &_data.spellmakingChargeTime);
				ImGuiExtensions::EndProperties();
			}
		}

		ImGui::EndChild();
	}

	void MagicEffectEditor::ScriptEffectAIData(const char* a_label)
	{
		ImGui::Text("Script Effect AI Data");
		if (ImGui::BeginChild(a_label, ImVec2(0, 45), true)) {
			if (ImGui::BeginTable("##aiLayout", 2, ImGuiTableFlags_NoSavedSettings)) {

				ImGui::TableNextColumn();
				if (ImGuiExtensions::BeginProperties("##scoreColumn")) {

					ImGuiExtensions::PropertiesLabel("Score");
					ImGui::InputFloat("##score", &_data.aiScore);
					ImGuiExtensions::EndProperties();
				}

				ImGui::TableNextColumn();
				if (ImGuiExtensions::BeginProperties("##delayTimeColumn")) {

					ImGuiExtensions::PropertiesLabel("Delay Time");
					ImGui::InputFloat("##delayTime", &_data.aiDelayTimer);
					ImGuiExtensions::EndProperties();
				}

				ImGui::EndTable();
			}
		}

		ImGui::EndChild();
	}

	void MagicEffectEditor::EquipAbility(const char* a_label)
	{
		if (ImGuiExtensions::BeginProperties(a_label)) {

			ImGuiExtensions::PropertiesForm("Equip Ability", _data.equipAbility);
			ImGuiExtensions::EndProperties();
		}
	}

	void MagicEffectEditor::Sounds(const char* a_label)
	{
		ImGui::Text("Sounds");
		if (ImGui::BeginChild(a_label, ImVec2(0, 178), true)) {

			if (ImGuiExtensions::BeginProperties("##visualsProps")) {

				ImGuiExtensions::PropertiesForm("Draw/Sheathe", _effectSounds[0].sound);
				ImGuiExtensions::PropertiesForm("Charge", _effectSounds[1].sound);
				ImGuiExtensions::PropertiesForm("Ready", _effectSounds[2].sound);
				ImGuiExtensions::PropertiesForm("Release", _effectSounds[3].sound);
				ImGuiExtensions::PropertiesForm("Cast Loop (Conc.)", _effectSounds[4].sound);
				ImGuiExtensions::PropertiesForm("On Hit", _effectSounds[5].sound);

				ImGuiExtensions::PropertiesLabel("Casting Sound Level");
				if (ImGui::BeginCombo(
					"##castingSoundLevel",
					util::enum_to_c_str(_data.castingSoundLevel))) {

					ImGuiExtensions::SelectableEnum(
						_data.castingSoundLevel,
						{
							RE::SOUND_LEVEL::kLoud,
							RE::SOUND_LEVEL::kNormal,
							RE::SOUND_LEVEL::kQuiet,
							RE::SOUND_LEVEL::kSilent,
							RE::SOUND_LEVEL::kVeryLoud,
						});
					ImGui::EndCombo();
				}

				ImGui::EndTable();
			}
		}

		ImGui::EndChild();
	}

	void MagicEffectEditor::PapyrusScripts(const char*)
	{
		// TODO: Papyrus Scripts
	}

	void MagicEffectEditor::EffectArchetype(const char* a_label)
	{
		if (ImGui::BeginCombo(a_label, util::enum_to_c_str(_data.archetype))) {

			using Archetype = RE::EffectSetting::Archetype;

			ImGuiExtensions::SelectableEnum(
				_data.archetype,
				{
					Archetype::kAbsorb,
					Archetype::kAccumulateMagnitude,
					Archetype::kBanish,
					Archetype::kBoundWeapon,
					Archetype::kCalm,
					Archetype::kCloak,
					Archetype::kCommandSummoned,
					Archetype::kConcussion,
					Archetype::kCureAddiction,
					Archetype::kCureDisease,
					Archetype::kCureParalysis,
					Archetype::kCurePoison,
					//Archetype::kDarkness,
					Archetype::kDemoralize,
					Archetype::kDetectLife,
					Archetype::kDisarm,
					Archetype::kDisguise,
					Archetype::kDispel,
					Archetype::kDualValueModifier,
					Archetype::kEnhanceWeapon,
					Archetype::kEtherealize,
					Archetype::kFrenzy,
					Archetype::kGrabActor,
					Archetype::kGuide,
					Archetype::kInvisibility,
					Archetype::kLight,
					Archetype::kLock,
					//Archetype::kNightEye,
					Archetype::kOpen,
					Archetype::kParalysis,
					Archetype::kPeakValueModifier,
					Archetype::kRally,
					Archetype::kReanimate,
					Archetype::kScript,
					Archetype::kSlowTime,
					Archetype::kSoulTrap,
					Archetype::kSpawnHazard,
					Archetype::kSpawnScriptedRef,
					Archetype::kStagger,
					Archetype::kSummonCreature,
					Archetype::kTelekinesis,
					Archetype::kTurnUndead,
					Archetype::kValueAndParts,
					Archetype::kValueModifier,
					Archetype::kVampireLord,
					Archetype::kWerewolf,
					Archetype::kWerewolfFeed,
				});

			ImGui::EndCombo();
		}
	}

	void MagicEffectEditor::CastingType(const char* a_label)
	{
		if (ImGui::BeginCombo(a_label, util::enum_to_c_str(_data.castingType))) {

			using CastingType = RE::MagicSystem::CastingType;

			ImGuiExtensions::SelectableEnum(
				_data.castingType,
				{
					CastingType::kConcentration,
					CastingType::kConstantEffect,
					CastingType::kFireAndForget,
					//CastingType::kScroll,
				});

			ImGui::EndCombo();
		}
	}

	void MagicEffectEditor::Delivery(const char* a_label)
	{
		if (ImGui::BeginCombo(a_label, util::enum_to_c_str(_data.delivery))) {

			using Delivery = RE::MagicSystem::Delivery;

			ImGuiExtensions::SelectableEnum(
				_data.delivery,
				{
					Delivery::kSelf,
					Delivery::kTouch,
					Delivery::kAimed,
					Delivery::kTargetActor,
					Delivery::kTargetLocation,
				});

			ImGui::EndCombo();
		}
	}

	void MagicEffectEditor::MagicSkill(const char* a_label)
	{
		if (ImGui::BeginCombo(a_label, util::enum_to_c_str(_data.associatedSkill))) {

			ImGuiExtensions::SelectableEnum(
				_data.associatedSkill,
				{
					RE::ActorValue::kNone,
					RE::ActorValue::kAlteration,
					RE::ActorValue::kConjuration,
					RE::ActorValue::kDestruction,
					RE::ActorValue::kIllusion,
					RE::ActorValue::kRestoration,
				});

			ImGui::EndCombo();
		}
	}

	void MagicEffectEditor::ResistValue(const char* a_label)
	{
		if (ImGui::BeginCombo(a_label, util::enum_to_c_str(_data.resistVariable))) {

			ImGuiExtensions::SelectableEnum(
				_data.resistVariable,
				{
					RE::ActorValue::kNone,
					RE::ActorValue::kDamageResist,
					RE::ActorValue::kResistDisease,
					RE::ActorValue::kResistShock,
					RE::ActorValue::kResistFire,
					RE::ActorValue::kResistFrost,
					RE::ActorValue::kResistMagic,
					RE::ActorValue::kPoisonResist,
				});

			ImGui::EndCombo();
		}
	}

	void MagicEffectEditor::PerkToApply(const char* a_label)
	{
		auto idHandler = DataHandler::GetSingleton();

		auto preview_value = idHandler->GetEditorID(_data.perk);
		if (ImGui::BeginCombo(a_label, preview_value)) {

			ImGuiExtensions::SelectableForm(_data.perk);

			ImGui::EndCombo();
		}
	}
}
