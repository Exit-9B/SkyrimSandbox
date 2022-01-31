#pragma once

namespace Sandbox::GUI
{
	class GUIManager
	{
	public:
		~GUIManager();
		GUIManager(const GUIManager&) = delete;
		GUIManager(GUIManager&&) = delete;
		GUIManager& operator=(const GUIManager&) = delete;
		GUIManager& operator=(GUIManager&&) = delete;

		static auto GetSingleton() -> GUIManager*;
		static void Install();

		inline static bool IsVisible = false;
		inline static HWND WindowHandle = nullptr;
	private:
		GUIManager() = default;

		static void MessageCallback(SKSE::MessagingInterface::Message* a_msg);

		static LRESULT WindowProc(HWND a_hWnd, UINT32 a_msg, WPARAM a_wParam, LPARAM a_lParam);
		static void Draw(std::uint32_t a_arg1);

		inline static bool _initialized = false;

		inline static REL::Relocation<decltype(WindowProc)> _WindowProc;
		inline static REL::Relocation<decltype(Draw)> _Draw;
	};
}
