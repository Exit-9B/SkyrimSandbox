#include "Sandbox/Modules/Editors/Factory.h"

#include "Sandbox/Modules/Editors/Magic/MagicEffectEditor.h"
#include "Sandbox/Modules/Editors/Miscellaneous/GlobalEditor.h"

#define USE_EDITOR(a_editor)                                                           \
	case a_editor::FORMTYPE:                                                           \
		return std::make_unique<a_editor>(static_cast<a_editor::TargetType*>(a_form))

namespace Sandbox::Modules::Editors
{
	auto Factory::MakeEditor(RE::TESForm* a_form) -> std::unique_ptr<FormEditor::IEditor>
	{
		switch (a_form->GetFormType()) {
			//USE_EDITOR(KeywordEditor);
			//USE_EDITOR(LocationRefTypeEditor);
			//USE_EDITOR(ActionEditor);
			//USE_EDITOR(TextureSetEditor);
			USE_EDITOR(GlobalEditor);
			//USE_EDITOR(ClassEditor);
			//USE_EDITOR(FactionEditor);
			//USE_EDITOR(HeadPartEditor);
			//USE_EDITOR(RaceEditor);
			//USE_EDITOR(SoundMarkerEditor);
			//USE_EDITOR(AcousticSpaceEditor);
			USE_EDITOR(MagicEffectEditor);
			//USE_EDITOR(LandTextureEditor);
			//USE_EDITOR(EnchantmentEditor);
			//USE_EDITOR(SpellEditor);
			//USE_EDITOR(ScrollEditor);
			//USE_EDITOR(ActivatorEditor);
			//USE_EDITOR(TalkingActivatorEditor);
			//USE_EDITOR(ArmorEditor);
			//USE_EDITOR(BookEditor);
			//USE_EDITOR(ContainerEditor);
			//USE_EDITOR(DoorEditor);
			//USE_EDITOR(IngredientEditor);
			//USE_EDITOR(LightEditor);
			//USE_EDITOR(MiscItemEditor);
			//USE_EDITOR(StaticEditor);
			//USE_EDITOR(StaticCollectionEditor);
			//USE_EDITOR(MovableStaticEditor);
			//USE_EDITOR(GrassEditor);
			//USE_EDITOR(TreeEditor);
			//USE_EDITOR(FloraEditor);
			//USE_EDITOR(FurnitureEditor);
			//USE_EDITOR(WeaponEditor);
			//USE_EDITOR(AmmoEditor);
			//USE_EDITOR(ActorEditor);
			//USE_EDITOR(LeveledCharacterEditor);
			//USE_EDITOR(KeyEditor);
			//USE_EDITOR(PotionEditor);
			//USE_EDITOR(IdleMarkerEditor);
			//USE_EDITOR(ConstructibleObjectEditor);
			//USE_EDITOR(ProjectileEditor);
			//USE_EDITOR(HazardEditor);
			//USE_EDITOR(SoulGemEditor);
			//USE_EDITOR(LeveledItemEditor);
			//USE_EDITOR(WeatherEditor);
			//USE_EDITOR(ClimateEditor);
			//USE_EDITOR(ShaderParticleEditor);
			//USE_EDITOR(VisualEffectEditor);
			//USE_EDITOR(QuestEditor);
			//USE_EDITOR(PackageEditor);
			//USE_EDITOR(CombatStyleEditor);
			//USE_EDITOR(LoadScreenEditor);
			//USE_EDITOR(LeveledSpellEditor);
			//USE_EDITOR(AnimObjectEditor);
			//USE_EDITOR(WaterTypeEditor);
			//USE_EDITOR(EffectShaderEditor);
			//USE_EDITOR(ExplosionEditor);
			//USE_EDITOR(DebrisEditor);
			//USE_EDITOR(ImagespaceEditor);
			//USE_EDITOR(ImagespaceModifierEditor);
			//USE_EDITOR(FormListEditor);
			//USE_EDITOR(PerkEditor);
			//USE_EDITOR(BodyPartDataEditor);
			//USE_EDITOR(AddOnNodeEditor);
			//USE_EDITOR(CameraShotEditor);
			//USE_EDITOR(VoiceTypeEditor);
			//USE_EDITOR(MaterialTypeEditor);
			//USE_EDITOR(ImpactDataEditor);
			//USE_EDITOR(ImpactDataSetEditor);
			//USE_EDITOR(ArmatureEditor);
			//USE_EDITOR(EncounterZoneEditor);
			//USE_EDITOR(LocationEditor);
			//USE_EDITOR(MessageEditor);
			//USE_EDITOR(LightingTemplateEditor);
			//USE_EDITOR(MusicTypeEditor);
			//USE_EDITOR(FootstepEditor);
			//USE_EDITOR(FootstepSetEditor);
			//USE_EDITOR(StoryManagerEventNodeEditor);
			//USE_EDITOR(MusicTrackEditor);
			//USE_EDITOR(WordOfPowerEditor);
			//USE_EDITOR(ShoutEditor);
			//USE_EDITOR(EquipSlotEditor);
			//USE_EDITOR(RelationshipEditor);
			//USE_EDITOR(AssociationTypeEditor);
			//USE_EDITOR(OutfitEditor);
			//USE_EDITOR(ArtObjectEditor);
			//USE_EDITOR(MaterialObjectEditor);
			//USE_EDITOR(MovementTypeEditor);
			//USE_EDITOR(SoundDescriptorEditor);
			//USE_EDITOR(DualCastDataEditor);
			//USE_EDITOR(SoundCategoryEditor);
			//USE_EDITOR(SoundOutputModelEditor);
			//USE_EDITOR(CollisionLayerEditor);
			//USE_EDITOR(ColorFormEditor);
			//USE_EDITOR(ReverbParametersEditor);
			//USE_EDITOR(LensFlareEditor);
			//USE_EDITOR(VolumetricLightingEditor);
		default:
			return nullptr;
		}
	}
}
