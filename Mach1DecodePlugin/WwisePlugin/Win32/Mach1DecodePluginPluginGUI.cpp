
#include "Mach1DecodePluginPluginGUI.h"

Mach1DecodePluginPluginGUI::Mach1DecodePluginPluginGUI()
{
}

ADD_AUDIOPLUGIN_CLASS_TO_CONTAINER(
    Mach1DecodePlugin,            // Name of the plug-in container for this shared library
    Mach1DecodePluginPluginGUI,   // Authoring plug-in class to add to the plug-in container
    Mach1DecodePluginFX           // Corresponding Sound Engine plug-in class
);
