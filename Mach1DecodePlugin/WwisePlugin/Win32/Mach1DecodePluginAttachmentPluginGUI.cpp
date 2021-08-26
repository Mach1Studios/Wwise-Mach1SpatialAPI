
#include "Mach1DecodePluginAttachmentPluginGUI.h"

Mach1DecodePluginAttachmentPluginGUI::Mach1DecodePluginAttachmentPluginGUI()
{
}

ADD_AUDIOPLUGIN_CLASS_TO_CONTAINER(
    Mach1DecodePlugin,                    // Name of the plug-in container for this shared library
    Mach1DecodePluginAttachmentPluginGUI, // Authoring plug-in class to add to the plug-in container
    Mach1DecodePluginFXAttachmentParams   // Corresponding Sound Engine plug-in class
);
