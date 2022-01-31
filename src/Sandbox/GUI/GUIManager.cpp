#include "Sandbox/GUI/GUIManager.h"

#include "Sandbox/ModuleManager.h"

#pragma warning(push, 0)
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#pragma warning(pop)

extern IMGUI_IMPL_API LRESULT
	ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Sandbox::GUI
{
	namespace
	{
		BOOL FindTopLevelWindow(HWND hwnd, LPARAM lParam)
		{
			static DWORD target_pid = ::GetCurrentProcessId();

			DWORD pid = 0;
			::GetWindowThreadProcessId(hwnd, &pid);

			if (pid != target_pid || ::GetWindow(hwnd, GW_OWNER) || !::IsWindowVisible(hwnd)) {
				return TRUE;  // continue
			}

			*reinterpret_cast<HWND*>(lParam) = hwnd;
			return FALSE;  // break
		}
	}

	GUIManager::~GUIManager()
	{
		if (!_initialized)
			return;

		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	auto GUIManager::GetSingleton() -> GUIManager*
	{
		static GUIManager singleton{};
		return std::addressof(singleton);
	}

	void GUIManager::Install()
	{
		auto& trampoline = SKSE::GetTrampoline();

		static REL::Relocation<std::uintptr_t> hook{ RE::Offset::Update, 0x9 };

		if (REL::make_pattern<"E8 ?? ?? ?? ??">().match(hook.address())) {
			_Draw = trampoline.write_call<5>(hook.address(), Draw);
		}
		else {
			util::report_and_fail("Failed to install Draw hook"sv);
		}

		SKSE::GetMessagingInterface()->RegisterListener(MessageCallback);
	}

	void GUIManager::MessageCallback(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type) {
		case SKSE::MessagingInterface::kInputLoaded:
		{
			::EnumWindows(FindTopLevelWindow, reinterpret_cast<LPARAM>(&WindowHandle));
			if (!WindowHandle) {
				util::report_and_fail("Failed to find game window"sv);
			}

			LONG_PTR procAddr = reinterpret_cast<LONG_PTR>(&WindowProc);
			_WindowProc = ::SetWindowLongPtr(WindowHandle, GWLP_WNDPROC, procAddr);

			if (!_WindowProc.get()) {
				util::report_and_fail("Failed to set WindowProc function"sv);
			}

			auto renderManager = RE::BSRenderManager::GetSingleton();
			if (!renderManager) {
				util::report_and_fail("BSRenderManager was not initialized"sv);
			}

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			auto& io = ImGui::GetIO();
			io.MouseDrawCursor = true;
			io.WantSetMousePos = true;

			ImGui::StyleColorsDark();

			ImGui_ImplWin32_Init(WindowHandle);
			ImGui_ImplDX11_Init(renderManager->forwarder, renderManager->context);

			_initialized = true;
		} break;
		}
	}

	LRESULT GUIManager::WindowProc(HWND a_hWnd, UINT32 a_msg, WPARAM a_wParam, LPARAM a_lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(a_hWnd, a_msg, a_wParam, a_lParam))
			return TRUE;

		auto& io = ImGui::GetIO();

		if (io.WantCaptureMouse || io.WantCaptureKeyboard)
			return FALSE;

		return _WindowProc(a_hWnd, a_msg, a_wParam, a_lParam);
	}

	void GUIManager::Draw(std::uint32_t a_arg1)
	{
		_Draw(a_arg1);

		if (_initialized && IsVisible) {

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();

			ImGui::NewFrame();

#ifndef NDEBUG
			static bool show_demo_window = true;
			if (show_demo_window) {
				ImGui::ShowDemoWindow(&show_demo_window);
			}
#endif

			ModuleManager::GetSingleton()->VisitModules(
				[](IModule* a_module)
				{
					a_module->ShowGUI();
				});

			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}
	}
}
