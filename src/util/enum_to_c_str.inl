#pragma once

#include "util/enum_to_c_str.h"

namespace util
{
	constexpr auto enum_to_c_str(ActorValue a_actorValue) -> const char*
	{
		switch (a_actorValue) {
		case ActorValue::kNone:
			return "NONE";
		case ActorValue::kAggresion:
			return "Aggression";
		case ActorValue::kConfidence:
			return "Confidence";
		case ActorValue::kEnergy:
			return "Energy";
		case ActorValue::kMorality:
			return "Morality";
		case ActorValue::kMood:
			return "Mood";
		case ActorValue::kAssistance:
			return "Assistance";
		case ActorValue::kOneHanded:
			return "One-Handed";
		case ActorValue::kTwoHanded:
			return "Two-Handed";
		case ActorValue::kArchery:
			return "Archery";
		case ActorValue::kBlock:
			return "Block";
		case ActorValue::kSmithing:
			return "Smithing";
		case ActorValue::kHeavyArmor:
			return "Heavy Armor";
		case ActorValue::kLightArmor:
			return "Light Armor";
		case ActorValue::kPickpocket:
			return "Pickpocket";
		case ActorValue::kLockpicking:
			return "Lockpicking";
		case ActorValue::kAlteration:
			return "Alteration";
		case ActorValue::kConjuration:
			return "Conjuration";
		case ActorValue::kDestruction:
			return "Destruction";
		case ActorValue::kIllusion:
			return "Illusion";
		case ActorValue::kRestoration:
			return "Restoration";
		case ActorValue::kEnchanting:
			return "Enchanting";
		case ActorValue::kHealth:
			return "Health";
		case ActorValue::kMagicka:
			return "Magicka";
		case ActorValue::kStamina:
			return "Stamina";
		case ActorValue::kHealRate:
			return "HealRate";
		case ActorValue::kMagickaRate:
			return "MagickaRate";
		case ActorValue::KStaminaRate:
			return "StaminaRate";
		case ActorValue::kSpeedMult:
			return "SpeedMult";
		case ActorValue::kInventoryWeight:
			return "InventoryWeight";
		case ActorValue::kCarryWeight:
			return "CarryWeight";
		case ActorValue::kCriticalChance:
			return "CriticalChance";
		case ActorValue::kMeleeDamage:
			return "MeleeDamage";
		case ActorValue::kUnarmedDamage:
			return "UnarmedDamage";
		case ActorValue::kMass:
			return "Mass";
		case ActorValue::kVoicePoints:
			return "VoicePoints";
		case ActorValue::kVoiceRate:
			return "VoiceRate";
		case ActorValue::kDamageResist:
			return "DamageResist";
		case ActorValue::kPoisonResist:
			return "PoisonResist";
		case ActorValue::kResistFire:
			return "FireResist";
		case ActorValue::kResistShock:
			return "ElectricResist";
		case ActorValue::kResistFrost:
			return "FrostResist";
		case ActorValue::kResistMagic:
			return "MagicResist";
		case ActorValue::kResistDisease:
			return "DiseaseResist";
		case ActorValue::kParalysis:
			return "Paralysis";
		case ActorValue::kInvisibility:
			return "Invisibility";
		case ActorValue::kNightEye:
			return "NightEye";
		default:
			return "UNKNOWN";
		}
	}

	constexpr auto enum_to_c_str(FormType a_formType) -> const char*
	{
		switch (a_formType) {
		case FormType::None:
			return "Form";
		case FormType::Keyword:
			return "Keyword";
		case FormType::LocationRefType:
			return "Location Ref Type";
		case FormType::Action:
			return "Actor Action";
		case FormType::TextureSet:
			return "TextureSet";
		case FormType::Global:
			return "Global";
		case FormType::Class:
			return "Class";
		case FormType::Faction:
			return "Faction";
		case FormType::HeadPart:
			return "HeadPart";
		case FormType::Race:
			return "Race";
		case FormType::Sound:
			return "Sound Marker";
		case FormType::AcousticSpace:
			return "Acoustic Space";
		case FormType::MagicEffect:
			return "Magic Effect";
		case FormType::LandTexture:
			return "LandTexture";
		case FormType::Enchantment:
			return "Enchantment";
		case FormType::Spell:
			return "Spell";
		case FormType::Scroll:
			return "Scroll";
		case FormType::Activator:
			return "Activator";
		case FormType::TalkingActivator:
			return "Talking Activator";
		case FormType::Armor:
			return "Armor";
		case FormType::Book:
			return "Book";
		case FormType::Container:
			return "Container";
		case FormType::Door:
			return "Door";
		case FormType::Ingredient:
			return "Ingredient";
		case FormType::Light:
			return "Light";
		case FormType::Misc:
			return "MiscItem";
		case FormType::Static:
			return "Static";
		case FormType::StaticCollection:
			return "Static Collection";
		case FormType::MovableStatic:
			return "MovableStatic";
		case FormType::Grass:
			return "Grass";
		case FormType::Tree:
			return "Tree";
		case FormType::Flora:
			return "Flora";
		case FormType::Furniture:
			return "Furniture";
		case FormType::Weapon:
			return "Weapon";
		case FormType::Ammo:
			return "Ammo";
		case FormType::NPC:
			return "Actor";
		case FormType::LeveledNPC:
			return "LeveledCharacter";
		case FormType::KeyMaster:
			return "Key";
		case FormType::AlchemyItem:
			return "Potion";
		case FormType::IdleMarker:
			return "IdleMarker";
		case FormType::ConstructibleObject:
			return "Constructible Object";
		case FormType::Projectile:
			return "Projectile";
		case FormType::Hazard:
			return "Hazard";
		case FormType::SoulGem:
			return "Soul Gem";
		case FormType::LeveledItem:
			return "LeveledItem";
		case FormType::Weather:
			return "Weather";
		case FormType::Climate:
			return "Climate";
		case FormType::ShaderParticleGeometryData:
			return "Shader Particle";
		case FormType::ReferenceEffect:
			return "Visual Effect";
		case FormType::Quest:
			return "Quest";
		case FormType::Package:
			return "Package";
		case FormType::CombatStyle:
			return "CombatStyle";
		case FormType::LoadScreen:
			return "LoadScreen";
		case FormType::LeveledSpell:
			return "LeveledSpell";
		case FormType::AnimatedObject:
			return "AnimObject";
		case FormType::Water:
			return "WaterType";
		case FormType::EffectShader:
			return "EffectShader";
		case FormType::Explosion:
			return "Explosion";
		case FormType::Debris:
			return "Debris";
		case FormType::ImageSpace:
			return "Imagespace";
		case FormType::ImageAdapter:
			return "Imagespace Modifier";
		case FormType::FormList:
			return "FormList";
		case FormType::Perk:
			return "Perk";
		case FormType::BodyPartData:
			return "Body Part Data";
		case FormType::AddonNode:
			return "AddOnNode";
		case FormType::CameraShot:
			return "CameraShot";
		case FormType::VoiceType:
			return "VoiceType";
		case FormType::MaterialType:
			return "Material Type";
		case FormType::Impact:
			return "ImpactData";
		case FormType::ImpactDataSet:
			return "ImpactDataSet";
		case FormType::Armature:
			return "ArmorAddon";
		case FormType::EncounterZone:
			return "Encounter Zone";
		case FormType::Location:
			return "Location";
		case FormType::Message:
			return "Message";
		case FormType::LightingMaster:
			return "Lighting Template";
		case FormType::MusicType:
			return "Music Type";
		case FormType::Footstep:
			return "Footstep";
		case FormType::FootstepSet:
			return "Footstep Set";
		case FormType::StoryManagerEventNode:
			return "SM Event Node";
		case FormType::MusicTrack:
			return "Music Track";
		case FormType::WordOfPower:
			return "Word of Power";
		case FormType::Shout:
			return "Shout";
		case FormType::EquipSlot:
			return "EquipSlot";
		case FormType::Relationship:
			return "Relationship";
		case FormType::AssociationType:
			return "Association Type";
		case FormType::Outfit:
			return "Outfit";
		case FormType::ArtObject:
			return "Art Object";
		case FormType::MaterialObject:
			return "Material Object";
		case FormType::MovementType:
			return "Movement Type";
		case FormType::SoundRecord:
			return "Sound Descriptor";
		case FormType::DualCastData:
			return "Dual Cast Data";
		case FormType::SoundCategory:
			return "Sound Category";
		case FormType::SoundOutputModel:
			return "Sound Output Model";
		case FormType::CollisionLayer:
			return "Collision Layer";
		case FormType::ColorForm:
			return "ColorForm";
		case FormType::ReverbParam:
			return "Reverb Parameters";
		case FormType::LensFlare:
			return "LensFlare";
		case FormType::VolumetricLighting:
			return "VolumetricLighting";
		default:
			return "UNKNOWN";
		}
	}

	constexpr auto enum_to_c_str(Archetype a_archetype) -> const char*
	{
		switch (a_archetype) {
		case Archetype::kValueModifier:
			return "Value Modifier";
		case Archetype::kScript:
			return "Script";
		case Archetype::kDispel:
			return "Dispel";
		case Archetype::kCureDisease:
			return "Cure Disease";
		case Archetype::kAbsorb:
			return "Absorb";
		case Archetype::kDualValueModifier:
			return "Dual Value Modifier";
		case Archetype::kCalm:
			return "Calm";
		case Archetype::kDemoralize:
			return "Demoralize";
		case Archetype::kFrenzy:
			return "Frenzy";
		case Archetype::kDisarm:
			return "Disarm";
		case Archetype::kCommandSummoned:
			return "Command Summoned";
		case Archetype::kInvisibility:
			return "Invisibility";
		case Archetype::kLight:
			return "Light";
		case Archetype::kDarkness:
			return "Darkness";
		case Archetype::kNightEye:
			return "Night Eye";
		case Archetype::kLock:
			return "Lock";
		case Archetype::kOpen:
			return "Open";
		case Archetype::kBoundWeapon:
			return "Bound Weapon";
		case Archetype::kSummonCreature:
			return "Summon Creature";
		case Archetype::kDetectLife:
			return "Detect Life";
		case Archetype::kTelekinesis:
			return "Telekinesis";
		case Archetype::kParalysis:
			return "Paralysis";
		case Archetype::kReanimate:
			return "Reanimate";
		case Archetype::kSoulTrap:
			return "Soul Trap";
		case Archetype::kTurnUndead:
			return "Turn Undead";
		case Archetype::kGuide:
			return "Guide";
		case Archetype::kWerewolfFeed:
			return "Werewolf Feed";
		case Archetype::kCureParalysis:
			return "Cure Paralysis";
		case Archetype::kCureAddiction:
			return "Cure Addiction";
		case Archetype::kCurePoison:
			return "Cure Poison";
		case Archetype::kConcussion:
			return "Concussion";
		case Archetype::kValueAndParts:
			return "Value and Parts";
		case Archetype::kAccumulateMagnitude:
			return "Accum. Magnitude";
		case Archetype::kStagger:
			return "Stagger";
		case Archetype::kPeakValueModifier:
			return "Peak Value Modifier";
		case Archetype::kCloak:
			return "Cloak";
		case Archetype::kWerewolf:
			return "Werewolf";
		case Archetype::kSlowTime:
			return "Slow Time";
		case Archetype::kRally:
			return "Rally";
		case Archetype::kEnhanceWeapon:
			return "Enhance Weapon";
		case Archetype::kSpawnHazard:
			return "Spawn Hazard";
		case Archetype::kEtherealize:
			return "Etherealize";
		case Archetype::kBanish:
			return "Banish";
		case Archetype::kSpawnScriptedRef:
			return "Spawn Scripted Ref";
		case Archetype::kDisguise:
			return "Disguise";
		case Archetype::kGrabActor:
			return "Grab Actor";
		case Archetype::kVampireLord:
			return "Vampire Lord";
		default:
			return "UNKNOWN";
		}
	}

	constexpr auto enum_to_c_str(CastingType a_castingType) -> const char*
	{
		switch (a_castingType) {
		case CastingType::kConstantEffect:
			return "Constant";
		case CastingType::kFireAndForget:
			return "Fire and Forget";
		case CastingType::kConcentration:
			return "Concentration";
		case CastingType::kScroll:
			return "Scroll";
		default:
			return "UNKNOWN";
		}
	}

	constexpr auto enum_to_c_str(Delivery a_delivery) -> const char*
	{
		switch (a_delivery) {
		case Delivery::kSelf:
			return "Self";
		case Delivery::kTouch:
			return "Contact";
		case Delivery::kAimed:
			return "Aimed";
		case Delivery::kTargetActor:
			return "Target Actor";
		case Delivery::kTargetLocation:
			return "Target Location";
		default:
			return "UNKNOWN";
		}
	}

	constexpr auto enum_to_c_str(EffectSettingFlag a_flag) -> const char*
	{
		switch (a_flag) {
		case EffectSettingFlag::kNone:
			return "NONE";
		case EffectSettingFlag::kHostile:
			return "Hostile";
		case EffectSettingFlag::kRecover:
			return "Recover";
		case EffectSettingFlag::kDetrimental:
			return "Detrimental";
		case EffectSettingFlag::kSnapToNavMesh:
			return "Snap to Navmesh";
		case EffectSettingFlag::kNoHitEvent:
			return "No Hit Event";
		case EffectSettingFlag::kDispelWithKeywords:
			return "Dispel With Keywords";
		case EffectSettingFlag::kNoDuration:
			return "No Duration";
		case EffectSettingFlag::kNoMagnitude:
			return "No Magnitude";
		case EffectSettingFlag::kNoArea:
			return "No Area";
		case EffectSettingFlag::kFXPersist:
			return "FX Persist";
		case EffectSettingFlag::kGoryVisuals:
			return "Gory Visuals";
		case EffectSettingFlag::kHideInUI:
			return "Hide in UI";
		case EffectSettingFlag::kNoRecast:
			return "No Recast";
		case EffectSettingFlag::kPowerAffectsMagnitude:
			return "Power Affects Magnitude";
		case EffectSettingFlag::kPowerAffectsDuration:
			return "Power Affects Duration";
		case EffectSettingFlag::kPainless:
			return "Painless";
		case EffectSettingFlag::kNoHitEffect:
			return "No Hit Effect";
		case EffectSettingFlag::kNoDeathDispel:
			return "No Death Dispel";
		default:
			return "AGGREGATE";
		}
	}

	constexpr auto enum_to_c_str(SoundLevel a_soundLevel) -> const char*
	{
		switch (a_soundLevel) {
		case SoundLevel::kLoud:
			return "Loud";
		case SoundLevel::kNormal:
			return "Normal";
		case SoundLevel::kSilent:
			return "Silent";
		case SoundLevel::kVeryLoud:
			return "Very Loud";
		case SoundLevel::kQuiet:
			return "Quiet";
		default:
			return "UNKNOWN";
		}
	}
}
