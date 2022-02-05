#include "Sandbox/Modules/MessageListener.h"

#include "Sandbox/FunctionInterface.h"
#include "Sandbox/Message.h"
#include "Sandbox/Modules/CellView.h"
#include "Sandbox/Modules/FormEditor.h"
#include "Sandbox/Modules/ObjectWindow.h"

namespace Sandbox::Modules
{
	void MessageCallback(SKSE::MessagingInterface::Message* a_msg)
	{
		switch (a_msg->type) {
		case Message::kShareAPI:
		{
			auto api = reinterpret_cast<FunctionInterface*>(a_msg->data);

			api->Register(ObjectWindow::GetSingleton());

			api->Register(FormEditor::GetSingleton());
			for (auto& formType : FormEditor::SupportedFormTypes) {
				api->AddFormEditor(static_cast<std::int32_t>(formType), Plugin::NAME.data());
			}

			api->Register(CellView::GetSingleton());
		} break;

		case Message::kEditForm:
		{
			auto form = *reinterpret_cast<RE::TESForm**>(a_msg->data);
			FormEditor::GetSingleton()->OpenEditor(form);
		} break;
		}
	}
}
