#include "Sandbox/GUI/InputHandler.h"

#include "Sandbox/GUI/GUIManager.h"

#include <imgui.h>

namespace Sandbox::GUI
{
	auto InputHandler::GetSingleton() -> InputHandler*
	{
		static InputHandler singleton{};
		return std::addressof(singleton);
	}

	void InputHandler::Install()
	{
		auto& trampoline = SKSE::GetTrampoline();

		auto hook = REL::Relocation<std::uintptr_t>{ RE::Offset::MenuControls::Ctor, 0xC3 };
		//auto hook = REL::Relocation<std::uintptr_t>{ RE::Offset::PlayerControls::Ctor, 0x203 };

		if (REL::make_pattern<"E8 ?? ?? ?? ??">().match(hook.address())) {
			_AddEventSink = trampoline.write_call<5>(
				hook.address(),
				AddEventSink);
		}
		else {
			util::report_and_fail("Failed to install input handler"sv);
		}
	}

	auto InputHandler::ProcessEvent(
		const Event* a_event,
		[[maybe_unused]] RE::BSTEventSource<Event>* a_eventSource) -> RE::BSEventNotifyControl
	{
		auto inputEvent = a_event ? *a_event : nullptr;
		auto buttonEvent = inputEvent ? inputEvent->AsButtonEvent() : nullptr;

		if (!CheckGUIVisible(buttonEvent)) {
			return RE::BSEventNotifyControl::kContinue;
		}

		if (!buttonEvent) {
			return RE::BSEventNotifyControl::kStop;
		}

		switch (buttonEvent->GetDevice()) {
		case RE::INPUT_DEVICE::kMouse:
		{
			if (HandleMouseEvent(buttonEvent)) {
				return RE::BSEventNotifyControl::kStop;
			}
		} break;

		case RE::INPUT_DEVICE::kKeyboard:
		{
			if (HandleKeyboardEvent(buttonEvent)) {
				return RE::BSEventNotifyControl::kStop;
			}
		} break;
		}

		return RE::BSEventNotifyControl::kContinue;
	}

	bool InputHandler::CheckGUIVisible(RE::ButtonEvent* a_event)
	{
		constexpr auto toggleKey = RE::BSKeyboardDevice::Keys::kF10;

		if (a_event && a_event->IsDown() && a_event->GetIDCode() == toggleKey) {
			GUIManager::IsVisible = !GUIManager::IsVisible;
		}

		return GUIManager::IsVisible;
	}

	bool InputHandler::HandleMouseEvent(RE::ButtonEvent* a_event)
	{
		if (!a_event || a_event->GetDevice() != RE::INPUT_DEVICE::kMouse)
			return false;

		auto& io = ImGui::GetIO();

		auto idCode = a_event->GetIDCode();

		if (idCode < ImGuiMouseButton_COUNT) {
			io.MouseDown[idCode] = a_event->IsPressed();
		}
		else if (idCode == RE::BSWin32MouseDevice::Keys::kWheelUp) {
			io.MouseWheel += a_event->Value();
		}
		else if (idCode == RE::BSWin32MouseDevice::Keys::kWheelDown) {
			io.MouseWheel -= a_event->Value();
		}

		return true;
	}

	bool InputHandler::HandleKeyboardEvent(RE::ButtonEvent* a_event)
	{
		if (!a_event || a_event->GetDevice() != RE::INPUT_DEVICE::kKeyboard)
			return false;

		auto& io = ImGui::GetIO();

		auto idCode = a_event->GetIDCode();
		bool isPressed = a_event->IsPressed();

		auto vk = ::MapVirtualKeyW(idCode, MAPVK_VSC_TO_VK);

		if (vk < 256) {
			io.KeysDown[vk] = isPressed;
		}

		if (idCode == RE::BSKeyboardDevice::Keys::kLeftControl ||
			idCode == RE::BSKeyboardDevice::Keys::kRightControl) {

			io.KeyCtrl = isPressed;
		}

		if (idCode == RE::BSKeyboardDevice::Keys::kLeftShift ||
			idCode == RE::BSKeyboardDevice::Keys::kRightShift) {

			io.KeyShift = isPressed;
		}

		if (idCode == RE::BSKeyboardDevice::Keys::kLeftAlt ||
			idCode == RE::BSKeyboardDevice::Keys::kRightAlt) {

			io.KeyAlt = isPressed;
		}

		if (a_event->IsDown()) {

			// TODO: Fix Shift key
			WCHAR wszBuff[4]{};

			auto deviceManager = RE::BSInputDeviceManager::GetSingleton();
			auto keyboard = deviceManager ? deviceManager->GetKeyboard() : nullptr;
			auto keyState = keyboard ? keyboard->curState : nullptr;

			int ret = ::ToUnicode(vk, idCode, keyState, wszBuff, 4, 0);

			for (int i = 0; i < ret; i++) {
				io.AddInputCharacterUTF16(wszBuff[i]);
			}
		}

		return io.WantCaptureKeyboard || io.WantTextInput;
	}

	void InputHandler::AddEventSink(
		RE::BSTEventSource<Event>* a_eventSource,
		RE::BSTEventSink<Event>* a_eventSink)
	{
		a_eventSource->AddEventSink(GetSingleton());
		_AddEventSink(a_eventSource, a_eventSink);
	}
}
