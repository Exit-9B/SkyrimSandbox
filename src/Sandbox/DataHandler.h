#pragma once

namespace Sandbox
{
	class DataHandler
	{
	public:
		template<typename T> requires std::is_base_of_v<RE::TESForm, T>
		class EditorIDSetter
		{
		public:
			EditorIDSetter() = delete;

			inline static constexpr std::size_t INDEX = 51;

			inline static void Install(REL::ID a_id)
			{
				REL::Relocation<std::uintptr_t> vtbl{ a_id };
				_SetFormEditorID = vtbl.write_vfunc(INDEX, SetFormEditorID);
			}

			inline static bool SetFormEditorID(RE::TESForm* a_form, const char* a_str)
			{
				DataHandler::GetSingleton()->SetEditorID(a_form, a_str);
				return _SetFormEditorID(a_form, a_str);
			}

			inline static REL::Relocation<decltype(SetFormEditorID)> _SetFormEditorID;
		};

		~DataHandler() = default;
		DataHandler(const DataHandler&) = delete;
		DataHandler(DataHandler&&) = delete;
		DataHandler& operator=(const DataHandler&) = delete;
		DataHandler& operator=(DataHandler&&) = delete;

		static auto GetSingleton() -> DataHandler*;

		auto GetEditorID(RE::TESForm* a_form) -> const char*;
		void SetEditorID(RE::TESForm* a_form, const char* a_str);

		static void Install();

	private:
		DataHandler() = default;

		std::unordered_map<RE::TESForm*, std::string> _editorIDs;
	};
}
