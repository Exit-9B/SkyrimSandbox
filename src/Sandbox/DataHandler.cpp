#include "Sandbox/DataHandler.h"

#include "util/enum_to_c_str.h"

namespace Sandbox
{
	auto DataHandler::GetSingleton() -> DataHandler*
	{
		static DataHandler singleton{};
		return std::addressof(singleton);
	}

	auto DataHandler::GetEditorID(RE::TESForm* a_form) -> const char*
	{
		if (!a_form) {
			return "NONE";
		}

		auto id = a_form->GetFormEditorID();
		if (::strlen(id)) {
#ifndef NDEBUG
			if (_editorIDs.find(a_form) != _editorIDs.end()) {
				util::report_and_fail(fmt::format(
					"Editor ID already loaded for {}", util::enum_to_c_str(a_form->GetFormType())));
			}
#endif
			return id;
		}

		auto it = _editorIDs.find(a_form);
		if (it != _editorIDs.end()) {
			return it->second.data();
		}

		return "BAD EDITOR ID";
	}

	void DataHandler::SetEditorID(RE::TESForm* a_form, const char* a_str)
	{
		_editorIDs[a_form] = a_str;
	}

	void DataHandler::Install()
	{
		// clang-format off
		EditorIDSetter<RE::BGSTextureSet>::Install(RE::Offset::BGSTextureSet::Vtbl);
		EditorIDSetter<RE::TESClass>::Install(RE::Offset::TESClass::Vtbl);
		EditorIDSetter<RE::TESFaction>::Install(RE::Offset::TESFaction::Vtbl);
		EditorIDSetter<RE::TESSound>::Install(RE::Offset::TESSound::Vtbl);
		EditorIDSetter<RE::BGSAcousticSpace>::Install(RE::Offset::BGSAcousticSpace::Vtbl);
		EditorIDSetter<RE::EffectSetting>::Install(RE::Offset::EffectSetting::Vtbl);
		EditorIDSetter<RE::TESLandTexture>::Install(RE::Offset::TESLandTexture::Vtbl);
		EditorIDSetter<RE::EnchantmentItem>::Install(RE::Offset::EnchantmentItem::Vtbl);
		EditorIDSetter<RE::SpellItem>::Install(RE::Offset::SpellItem::Vtbl);
		EditorIDSetter<RE::ScrollItem>::Install(RE::Offset::ScrollItem::Vtbl);
		EditorIDSetter<RE::TESObjectACTI>::Install(RE::Offset::TESObjectACTI::Vtbl);
		EditorIDSetter<RE::BGSTalkingActivator>::Install(RE::Offset::BGSTalkingActivator::Vtbl);
		EditorIDSetter<RE::TESObjectARMO>::Install(RE::Offset::TESObjectARMO::Vtbl);
		EditorIDSetter<RE::TESObjectBOOK>::Install(RE::Offset::TESObjectBOOK::Vtbl);
		EditorIDSetter<RE::TESObjectCONT>::Install(RE::Offset::TESObjectCONT::Vtbl);
		EditorIDSetter<RE::TESObjectDOOR>::Install(RE::Offset::TESObjectDOOR::Vtbl);
		EditorIDSetter<RE::IngredientItem>::Install(RE::Offset::IngredientItem::Vtbl);
		EditorIDSetter<RE::TESObjectLIGH>::Install(RE::Offset::TESObjectLIGH::Vtbl);
		EditorIDSetter<RE::TESObjectMISC>::Install(RE::Offset::TESObjectMISC::Vtbl);
		EditorIDSetter<RE::TESObjectSTAT>::Install(RE::Offset::TESObjectSTAT::Vtbl);
		EditorIDSetter<RE::BGSMovableStatic>::Install(RE::Offset::BGSMovableStatic::Vtbl_TESForm);
		EditorIDSetter<RE::TESGrass>::Install(RE::Offset::TESGrass::Vtbl);
		EditorIDSetter<RE::TESObjectTREE>::Install(RE::Offset::TESObjectTREE::Vtbl);
		EditorIDSetter<RE::TESFlora>::Install(RE::Offset::TESFlora::Vtbl);
		EditorIDSetter<RE::TESFurniture>::Install(RE::Offset::TESFurniture::Vtbl);
		EditorIDSetter<RE::TESObjectWEAP>::Install(RE::Offset::TESObjectWEAP::Vtbl);
		EditorIDSetter<RE::TESAmmo>::Install(RE::Offset::TESAmmo::Vtbl);
		EditorIDSetter<RE::TESNPC>::Install(RE::Offset::TESNPC::Vtbl);
		EditorIDSetter<RE::TESLevCharacter>::Install(RE::Offset::TESLevCharacter::Vtbl);
		EditorIDSetter<RE::TESKey>::Install(RE::Offset::TESKey::Vtbl);
		EditorIDSetter<RE::AlchemyItem>::Install(RE::Offset::AlchemyItem::Vtbl);
		EditorIDSetter<RE::BGSIdleMarker>::Install(RE::Offset::BGSIdleMarker::Vtbl);
		EditorIDSetter<RE::BGSConstructibleObject>::Install(RE::Offset::BGSConstructibleObject::Vtbl);
		EditorIDSetter<RE::BGSProjectile>::Install(RE::Offset::BGSProjectile::Vtbl);
		EditorIDSetter<RE::BGSHazard>::Install(RE::Offset::BGSHazard::Vtbl);
		EditorIDSetter<RE::TESSoulGem>::Install(RE::Offset::TESSoulGem::Vtbl);
		EditorIDSetter<RE::TESLevItem>::Install(RE::Offset::TESLevItem::Vtbl);
		EditorIDSetter<RE::TESWeather>::Install(RE::Offset::TESWeather::Vtbl);
		EditorIDSetter<RE::TESClimate>::Install(RE::Offset::TESClimate::Vtbl);
		EditorIDSetter<RE::BGSShaderParticleGeometryData>::Install(RE::Offset::BGSShaderParticleGeometryData::Vtbl);
		EditorIDSetter<RE::BGSReferenceEffect>::Install(RE::Offset::BGSReferenceEffect::Vtbl);
		EditorIDSetter<RE::TESRegion>::Install(RE::Offset::TESRegion::Vtbl);
		EditorIDSetter<RE::TESPackage>::Install(RE::Offset::TESPackage::Vtbl);
		EditorIDSetter<RE::TESCombatStyle>::Install(RE::Offset::TESCombatStyle::Vtbl);
		EditorIDSetter<RE::TESLoadScreen>::Install(RE::Offset::TESLoadScreen::Vtbl);
		EditorIDSetter<RE::TESLevSpell>::Install(RE::Offset::TESLevSpell::Vtbl);
		EditorIDSetter<RE::TESWaterForm>::Install(RE::Offset::TESWaterForm::Vtbl);
		EditorIDSetter<RE::TESEffectShader>::Install(RE::Offset::TESEffectShader::Vtbl);
		EditorIDSetter<RE::BGSExplosion>::Install(RE::Offset::BGSExplosion::Vtbl);
		EditorIDSetter<RE::BGSDebris>::Install(RE::Offset::BGSDebris::Vtbl);
		EditorIDSetter<RE::TESImageSpace>::Install(RE::Offset::TESImageSpace::Vtbl);
		EditorIDSetter<RE::BGSListForm>::Install(RE::Offset::BGSListForm::Vtbl);
		EditorIDSetter<RE::BGSPerk>::Install(RE::Offset::BGSPerk::Vtbl);
		EditorIDSetter<RE::BGSBodyPartData>::Install(RE::Offset::BGSBodyPartData::Vtbl);
		EditorIDSetter<RE::BGSAddonNode>::Install(RE::Offset::BGSAddonNode::Vtbl);
		EditorIDSetter<RE::BGSCameraShot>::Install(RE::Offset::BGSCameraShot::Vtbl);
		EditorIDSetter<RE::BGSMaterialType>::Install(RE::Offset::BGSMaterialType::Vtbl);
		EditorIDSetter<RE::BGSImpactData>::Install(RE::Offset::BGSImpactData::Vtbl);
		EditorIDSetter<RE::BGSImpactDataSet>::Install(RE::Offset::BGSImpactDataSet::Vtbl);
		EditorIDSetter<RE::TESObjectARMA>::Install(RE::Offset::TESObjectARMA::Vtbl);
		EditorIDSetter<RE::BGSEncounterZone>::Install(RE::Offset::BGSEncounterZone::Vtbl);
		EditorIDSetter<RE::BGSLocation>::Install(RE::Offset::BGSLocation::Vtbl);
		EditorIDSetter<RE::BGSMessage>::Install(RE::Offset::BGSMessage::Vtbl);
		EditorIDSetter<RE::BGSLightingTemplate>::Install(RE::Offset::BGSLightingTemplate::Vtbl);
		EditorIDSetter<RE::BGSFootstep>::Install(RE::Offset::BGSFootstep::Vtbl);
		EditorIDSetter<RE::BGSFootstepSet>::Install(RE::Offset::BGSFootstepSet::Vtbl);
		EditorIDSetter<RE::BGSMusicTrackFormWrapper>::Install(RE::Offset::BGSMusicTrackFormWrapper::Vtbl);
		EditorIDSetter<RE::TESWordOfPower>::Install(RE::Offset::TESWordOfPower::Vtbl);
		EditorIDSetter<RE::TESShout>::Install(RE::Offset::TESShout::Vtbl);
		EditorIDSetter<RE::BGSEquipSlot>::Install(RE::Offset::BGSEquipSlot::Vtbl);
		EditorIDSetter<RE::BGSRelationship>::Install(RE::Offset::BGSRelationship::Vtbl);
		EditorIDSetter<RE::BGSAssociationType>::Install(RE::Offset::BGSAssociationType::Vtbl);
		EditorIDSetter<RE::BGSOutfit>::Install(RE::Offset::BGSOutfit::Vtbl);
		EditorIDSetter<RE::BGSArtObject>::Install(RE::Offset::BGSArtObject::Vtbl);
		EditorIDSetter<RE::BGSMaterialObject>::Install(RE::Offset::BGSMaterialObject::Vtbl);
		EditorIDSetter<RE::BGSMovementType>::Install(RE::Offset::BGSMovementType::Vtbl);
		EditorIDSetter<RE::BGSSoundDescriptorForm>::Install(RE::Offset::BGSSoundDescriptorForm::Vtbl);
		EditorIDSetter<RE::BGSDualCastData>::Install(RE::Offset::BGSDualCastData::Vtbl);
		EditorIDSetter<RE::BGSSoundCategory>::Install(RE::Offset::BGSSoundCategory::Vtbl);
		EditorIDSetter<RE::BGSSoundOutput>::Install(RE::Offset::BGSSoundOutput::Vtbl);
		EditorIDSetter<RE::BGSCollisionLayer>::Install(RE::Offset::BGSCollisionLayer::Vtbl);
		EditorIDSetter<RE::BGSColorForm>::Install(RE::Offset::BGSColorForm::Vtbl);
		EditorIDSetter<RE::BGSReverbParameters>::Install(RE::Offset::BGSReverbParameters::Vtbl);
		EditorIDSetter<RE::BGSVolumetricLighting>::Install(RE::Offset::BGSVolumetricLighting::Vtbl);
		// clang-format on
	}
}
