#pragma once

#include "../Mach1DecodePluginPlugin.h"

class Mach1DecodePluginPluginGUI final
	: public AK::Wwise::Plugin::PluginMFCWindows<>
	, public AK::Wwise::Plugin::GUIWindows
{
public:
	Mach1DecodePluginPluginGUI();
};
