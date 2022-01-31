#include "Sandbox/Modules/ObjectWindow.h"

#include "ImGuiExtensions/ImGuiExtensions.h"
#include "Sandbox/DataHandler.h"
#include "Sandbox/ModuleManager.h"
#include "util/enum_to_c_str.h"

namespace Sandbox::Modules
{
	using RE::FormType;

	void ObjectWindow::ShowGUI()
	{
		if (ImGui::Begin("Object Window")) {

			if (ImGui::BeginTable("##objectWindow", 2, ImGuiTableFlags_NoSavedSettings)) {

				ImGui::TableSetupColumn("##filtersColumn", ImGuiTableColumnFlags_WidthFixed, 200.0f);
				ImGui::TableSetupColumn("##formsColumn", ImGuiTableColumnFlags_WidthStretch);
				ImGui::TableNextRow();

				ImGui::TableNextColumn();
				Filters();

				ImGui::TableNextColumn();
				Forms();

				ImGui::EndTable();
			}

		}
		ImGui::End();
	}

	auto ObjectWindow::GetSingleton() -> ObjectWindow*
	{
		static ObjectWindow singleton{};
		return std::addressof(singleton);
	}

	void ObjectWindow::Filters()
	{
		ImGui::BeginGroup();
		ImGui::Text("Filter");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		_filter.Draw();

		ImGui::Text("File");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(-FLT_MIN);
		if (ImGui::BeginCombo("##files", _fileFilter ? _fileFilter->fileName : "*All")) {

			if (ImGui::Selectable("*All##files", !_fileFilter)) {
				_fileFilter = nullptr;
			}

			auto dataHandler = RE::TESDataHandler::GetSingleton();
			if (dataHandler) {
				for (auto& file : dataHandler->files) {
					if (ImGui::Selectable(file->fileName, file == _fileFilter)) {
						_fileFilter = file;
					}
				}
			}
			ImGui::EndCombo();
		}

		if (ImGui::BeginListBox("##formType", ImVec2(-FLT_MIN, -FLT_MIN))) {

			if (ImGui::TreeNodeEx("Actors", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGuiExtensions::SelectableEnum(
					_formType,
					{
						FormType::NPC,
						FormType::Action,
						FormType::BodyPartData,
						FormType::LeveledNPC,
						FormType::Perk,
						FormType::TalkingActivator,
					});

				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("Audio", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGuiExtensions::SelectableEnum(
					_formType,
					{
						FormType::AcousticSpace,
						FormType::MusicTrack,
						FormType::MusicType,
						FormType::ReverbParam,
						FormType::SoundCategory,
						FormType::SoundRecord,
						FormType::Sound,
						FormType::SoundOutputModel,
					});

				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("Character", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGuiExtensions::SelectableEnum(
					_formType,
					{
						FormType::AssociationType,
						FormType::Class,
						FormType::EquipSlot,
						FormType::Faction,
						FormType::HeadPart,
						FormType::MovementType,
						FormType::Package,
						FormType::Quest,
						FormType::Race,
						FormType::Relationship,
						FormType::StoryManagerEventNode,
						FormType::VoiceType,
					});

				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("Items", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGuiExtensions::SelectableEnum(
					_formType,
					{
						FormType::Ammo,
						FormType::Armor,
						FormType::Armature,
						FormType::Book,
						FormType::ConstructibleObject,
						FormType::Ingredient,
						FormType::KeyMaster,
						FormType::LeveledItem,
						FormType::Misc,
						FormType::Outfit,
						FormType::SoulGem,
						FormType::Weapon,
					});

				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("Magic", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGuiExtensions::SelectableEnum(
					_formType,
					{
						FormType::DualCastData,
						FormType::Enchantment,
						FormType::LeveledSpell,
						FormType::MagicEffect,
						FormType::AlchemyItem,
						FormType::Scroll,
						FormType::Shout,
						FormType::Spell,
						FormType::WordOfPower,
					});

				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("Miscellaneous", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGuiExtensions::SelectableEnum(
					_formType,
					{
						FormType::AnimatedObject,
						FormType::ArtObject,
						FormType::CollisionLayer,
						FormType::ColorForm,
						FormType::CombatStyle,
						FormType::FormList,
						FormType::Global,
						FormType::IdleMarker,
						FormType::Keyword,
						FormType::LandTexture,
						FormType::LoadScreen,
						FormType::MaterialObject,
						FormType::Message,
						FormType::TextureSet,
					});

				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("SpecialEffect", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGuiExtensions::SelectableEnum(
					_formType,
					{
						FormType::AddonNode,
						FormType::CameraShot,
						FormType::Debris,
						FormType::EffectShader,
						FormType::Explosion,
						FormType::Footstep,
						FormType::FootstepSet,
						FormType::Hazard,
						FormType::ImageSpace,
						FormType::ImageAdapter,
						FormType::Impact,
						FormType::ImpactDataSet,
						FormType::LensFlare,
						FormType::MaterialType,
						FormType::Projectile,
						FormType::VolumetricLighting,
					});

				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("WorldData", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGuiExtensions::SelectableEnum(
					_formType,
					{
						FormType::Climate,
						FormType::EncounterZone,
						FormType::LightingMaster,
						FormType::Location,
						FormType::LocationRefType,
						FormType::ShaderParticleGeometryData,
						FormType::ReferenceEffect,
						FormType::Water,
						FormType::Weather,
					});

				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("WorldObjects", ImGuiTreeNodeFlags_DefaultOpen)) {

				ImGuiExtensions::SelectableEnum(
					_formType,
					{
						FormType::Activator,
						FormType::Container,
						FormType::Door,
						FormType::Flora,
						FormType::Furniture,
						FormType::Grass,
						FormType::Light,
						FormType::MovableStatic,
						FormType::Static,
						FormType::StaticCollection,
						FormType::Tree,
					});

				ImGui::TreePop();
			}

			if (ImGui::Selectable("*All", _formType == FormType::None)) {
				_formType = FormType::None;
			}

			ImGui::EndListBox();
		}

		ImGui::EndGroup();
	}

	void ObjectWindow::Forms()
	{
		ImGuiTableFlags tableFlags =
			ImGuiTableFlags_SizingFixedFit |
			ImGuiTableFlags_NoSavedSettings |
			ImGuiTableFlags_Borders;

		if (ImGui::BeginChild("##forms", ImVec2(-FLT_MIN, -FLT_MIN))) {

			if (ImGui::BeginTable("forms", 4, tableFlags)) {

				SetupColumns(_formType);
				ImGui::TableHeadersRow();

				auto dataHandler = RE::TESDataHandler::GetSingleton();
				if (dataHandler && _formType == FormType::None) {
					if (::strlen(_filter.InputBuf) >= 2) {
						auto [formMap, lock] = RE::TESForm::GetAllForms();

						for (auto& [formId, form] : *formMap) {
							Row(_formType, form, &_filter, _fileFilter);
						}
					}
				}
				else if (dataHandler) {

					auto& forms = dataHandler->GetFormArray(_formType);

					for (auto& form : forms) {
						Row(_formType, form, &_filter, _fileFilter);
					}
				}

				ImGui::EndTable();
			}

		}
		ImGui::EndChild();
	}

	void ObjectWindow::SetupColumns(RE::FormType a_formType)
	{
		// TODO: Change columns based on form type
		switch (a_formType) {
		default:
		{
			ImGui::TableSetupColumn("Editor ID##idColumn");
			ImGui::TableSetupColumn("Form Type##formTypeColumn");
			ImGui::TableSetupColumn("Form ID##formIdColumn");
			ImGui::TableSetupColumn("File##fileColumn");
		} break;
#pragma warning(suppress : 4065)
		}
	}

	void ObjectWindow::Row(
		RE::FormType a_formType,
		RE::TESForm* a_form,
		const ImGuiTextFilter* a_filter,
		RE::TESFile* a_fileFilter)
	{
		static_cast<void>(a_formType);
		static RE::TESForm* selected = nullptr;

		auto id = DataHandler::GetSingleton()->GetEditorID(a_form);
		auto formId = fmt::format("{:08X}"sv, a_form->GetFormID());
		auto formType = util::enum_to_c_str(a_form->GetFormType());
		auto files = a_form->sourceFiles.array;
		auto filename = files ? files->front()->GetFilename() : ""sv;

		if (files && a_fileFilter) {
			auto it = std::find(std::begin(*files), std::end(*files), a_fileFilter);
			if (it == std::end(*files)) {
				return;
			}
		}

		if (!a_filter->PassFilter(id)) {
			return;
		}

		ImGui::TableNextRow();
		ImGui::TableNextColumn();

		ImGuiSelectableFlags selectableFlags =
			ImGuiSelectableFlags_SpanAllColumns |
			ImGuiSelectableFlags_AllowDoubleClick;

		if (ImGui::Selectable(id, a_form == selected, selectableFlags)) {

			selected = a_form;

			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
				ModuleManager::GetSingleton()->EditForm(a_form);
			}
		}

		ImGui::TableNextColumn();
		ImGui::Text(formType);
		ImGui::TableNextColumn();
		ImGui::Text(formId.data());
		ImGui::TableNextColumn();
		ImGui::Text(filename.data());
	}
}
