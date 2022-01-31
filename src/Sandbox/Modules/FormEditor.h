#pragma once

#include "Sandbox/IModule.h"

namespace Sandbox::Modules
{
	class FormEditor : public IModule
	{
	public:
		class IEditor
		{
		public:
			virtual ~IEditor() = default;
			virtual void ShowGUI() = 0;
		};

		template <typename T>
		class EditorBase : public IEditor
		{
		public:
			using TargetType = T;
			inline static constexpr auto FORMTYPE = T::FORMTYPE;

		protected:
			EditorBase(T* a_form) : _form(a_form) {}

			T* const _form;
			bool _open = true;
		};

		~FormEditor() override = default;
		FormEditor(const FormEditor&) = delete;
		FormEditor(FormEditor&&) = delete;
		FormEditor& operator=(const FormEditor&) = delete;
		FormEditor& operator=(FormEditor&&) = delete;

		static auto GetSingleton() -> FormEditor*;

		void ShowGUI() override;

		void OpenEditor(RE::TESForm* a_form);

		inline static const std::vector<RE::FormType> SupportedFormTypes = {
			//RE::FormType::Keyword,
			//RE::FormType::LocationRefType,
			//RE::FormType::Action,
			//RE::FormType::TextureSet,
			RE::FormType::Global,
			//RE::FormType::Class,
			//RE::FormType::Faction,
			//RE::FormType::HeadPart,
			//RE::FormType::Race,
			//RE::FormType::Sound,
			//RE::FormType::AcousticSpace,
			RE::FormType::MagicEffect,
			//RE::FormType::LandTexture,
			//RE::FormType::Enchantment,
			//RE::FormType::Spell,
			//RE::FormType::Scroll,
			//RE::FormType::Activator,
			//RE::FormType::TalkingActivator,
			//RE::FormType::Armor,
			//RE::FormType::Book,
			//RE::FormType::Container,
			//RE::FormType::Door,
			//RE::FormType::Ingredient,
			//RE::FormType::Light,
			//RE::FormType::Misc,
			//RE::FormType::Static,
			//RE::FormType::StaticCollection,
			//RE::FormType::MovableStatic,
			//RE::FormType::Grass,
			//RE::FormType::Tree,
			//RE::FormType::Flora,
			//RE::FormType::Furniture,
			//RE::FormType::Weapon,
			//RE::FormType::Ammo,
			//RE::FormType::NPC,
			//RE::FormType::LeveledNPC,
			//RE::FormType::KeyMaster,
			//RE::FormType::AlchemyItem,
			//RE::FormType::IdleMarker,
			//RE::FormType::ConstructibleObject,
			//RE::FormType::Projectile,
			//RE::FormType::Hazard,
			//RE::FormType::SoulGem,
			//RE::FormType::LeveledItem,
			//RE::FormType::Weather,
			//RE::FormType::Climate,
			//RE::FormType::ShaderParticleGeometryData,
			//RE::FormType::ReferenceEffect,
			//RE::FormType::Quest,
			//RE::FormType::Package,
			//RE::FormType::CombatStyle,
			//RE::FormType::LoadScreen,
			//RE::FormType::LeveledSpell,
			//RE::FormType::AnimatedObject,
			//RE::FormType::Water,
			//RE::FormType::EffectShader,
			//RE::FormType::Explosion,
			//RE::FormType::Debris,
			//RE::FormType::ImageSpace,
			//RE::FormType::ImageAdapter,
			//RE::FormType::FormList,
			//RE::FormType::Perk,
			//RE::FormType::BodyPartData,
			//RE::FormType::AddonNode,
			//RE::FormType::CameraShot,
			//RE::FormType::VoiceType,
			//RE::FormType::MaterialType,
			//RE::FormType::Impact,
			//RE::FormType::ImpactDataSet,
			//RE::FormType::Armature,
			//RE::FormType::EncounterZone,
			//RE::FormType::Location,
			//RE::FormType::Message,
			//RE::FormType::LightingMaster,
			//RE::FormType::MusicType,
			//RE::FormType::Footstep,
			//RE::FormType::FootstepSet,
			//RE::FormType::StoryManagerEventNode,
			//RE::FormType::MusicTrack,
			//RE::FormType::WordOfPower,
			//RE::FormType::Shout,
			//RE::FormType::EquipSlot,
			//RE::FormType::Relationship,
			//RE::FormType::AssociationType,
			//RE::FormType::Outfit,
			//RE::FormType::ArtObject,
			//RE::FormType::MaterialObject,
			//RE::FormType::MovementType,
			//RE::FormType::SoundRecord,
			//RE::FormType::DualCastData,
			//RE::FormType::SoundCategory,
			//RE::FormType::SoundOutputModel,
			//RE::FormType::CollisionLayer,
			//RE::FormType::ColorForm,
			//RE::FormType::ReverbParam,
			//RE::FormType::LensFlare,
			//RE::FormType::VolumetricLighting,
		};

	private:
		FormEditor() = default;

		std::unique_ptr<IEditor> _currentEditor = nullptr;
		RE::TESForm* _currentForm = nullptr;
		std::string _name;
		std::string _desc;
	};
}
