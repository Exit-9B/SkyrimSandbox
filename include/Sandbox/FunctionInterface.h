#pragma once

#include "Sandbox/IModule.h"

#include <cstdint>

namespace Sandbox
{
	/* Sandbox Module API
	 */
	struct FunctionInterface
	{
		/* Registers a module with Sandbox.
		 *
		 * \param[in] a_module  The module implementation.
		 */
		void (*Register)(IModule* a_module);

		/* Adds a plugin as a handler for a given form type.
		 *
		 * \param[in] a_formType  The form type to handle
		 * \param[in] a_name      The name of the plugin
		 */
		void (*AddFormEditor)(std::int32_t a_formType, const char* a_name);

		/* Request an editor to be opened for the specified form.
		 *
		 * \param[in] a_form  A pointer to the TESForm to edit
		 */
		void (*EditForm)(void* a_form);

		/* Get a form's Editor ID, even if the game would normally discard it.
		 *
		 * \param[in] a_form  A pointer to the TESForm to query
		 * \returns           The form's Editor ID
		 */
		const char* (*GetFormEditorID)(void* a_form);
	};
}
