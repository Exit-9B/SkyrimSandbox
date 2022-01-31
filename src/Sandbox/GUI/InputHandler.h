#pragma once

namespace Sandbox::GUI
{
	class InputHandler final : public RE::BSTEventSink<RE::InputEvent*>
	{
	public:
		using Event = RE::InputEvent*;

		~InputHandler() = default;
		InputHandler(const InputHandler&) = delete;
		InputHandler(InputHandler&&) = delete;
		InputHandler& operator=(const InputHandler&) = delete;
		InputHandler& operator=(InputHandler&&) = delete;

		static auto GetSingleton() -> InputHandler*;

		static void Install();

		auto ProcessEvent(const Event* a_event, RE::BSTEventSource<Event>* a_eventSource)
			-> RE::BSEventNotifyControl override;

	private:
		InputHandler() = default;

		bool CheckGUIVisible(RE::ButtonEvent* a_event);
		bool HandleMouseEvent(RE::ButtonEvent* a_event);
		bool HandleKeyboardEvent(RE::ButtonEvent* a_event);

		static void AddEventSink(
			RE::BSTEventSource<Event>* a_eventSource,
			RE::BSTEventSink<Event>* a_eventSink);

		inline static REL::Relocation<decltype(AddEventSink)>
			_AddEventSink;
	};
}
