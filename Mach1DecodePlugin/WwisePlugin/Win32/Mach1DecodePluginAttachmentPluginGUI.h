#pragma once

#include "../Mach1DecodePluginAttachmentPlugin.h"

class Mach1DecodePluginAttachmentPluginGUI final
	: public AK::Wwise::Plugin::PluginMFCWindows<>
	, public AK::Wwise::Plugin::GUIWindows
{
public:
	Mach1DecodePluginAttachmentPluginGUI();
};
