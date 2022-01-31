#pragma once

namespace util
{
	using ActorValue = RE::ActorValue;
	using Archetype = RE::EffectArchetypes::ArchetypeID;
	using CastingType = RE::MagicSystem::CastingType;
	using Delivery = RE::MagicSystem::Delivery;
	using EffectSettingFlag = RE::EffectSetting::EffectSettingData::Flag;
	using FormType = RE::FormType;
	using SoundLevel = RE::SOUND_LEVEL;

	inline constexpr auto enum_to_c_str(ActorValue a_actorValue) -> const char*;
	inline constexpr auto enum_to_c_str(FormType a_formType) -> const char*;

	inline constexpr auto enum_to_c_str(Archetype a_archetype) -> const char*;
	inline constexpr auto enum_to_c_str(CastingType a_castingType) -> const char*;
	inline constexpr auto enum_to_c_str(Delivery a_delivery) -> const char*;
	inline constexpr auto enum_to_c_str(EffectSettingFlag a_flag) -> const char*;
	inline constexpr auto enum_to_c_str(SoundLevel a_soundLevel) -> const char*;
}

#include "util/enum_to_c_str.inl"
