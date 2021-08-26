/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Copyright (c) 2021 Audiokinetic Inc.
*******************************************************************************/

#ifndef Mach1DecodePluginFX_H
#define Mach1DecodePluginFX_H

#include "Mach1DecodePluginFXParams.h"
#include "Mach1DecodePluginFXAttachmentParams.h"

#include <AK/SoundEngine/Common/IAkMixerPlugin.h>

class Mach1DecodePluginFX
    : public AK::IAkMixerEffectPlugin
{
public:
    Mach1DecodePluginFX();
    ~Mach1DecodePluginFX();

    /// Plug-in initialization.
    /// Prepares the plug-in for data processing, allocates memory and sets up the initial conditions.
    AKRESULT Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkMixerPluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat) override;

    /// Release the resources upon termination of the plug-in.
    AKRESULT Term(AK::IAkPluginMemAlloc* in_pAllocator) override;

    /// The reset action should perform any actions required to reinitialize the
    /// state of the plug-in to its original state (e.g. after Init() or on effect bypass).
    AKRESULT Reset() override;

    /// Plug-in information query mechanism used when the sound engine requires
    /// information about the plug-in to determine its behavior.
    AKRESULT GetPluginInfo(AkPluginInfo& out_rPluginInfo) override;

    /// This function is called whenever a new input is connected to the underlying mixing bus.
    void OnInputConnected(AK::IAkMixerInputContext* in_pInput) override;

    /// This function is called whenever a new input is disconnected to the underlying mixing bus.
    void OnInputDisconnected(AK::IAkMixerInputContext* in_pInput) override;

    /// This function is called whenever an input (voice or bus) needs to be mixed.
    /// During an audio frame, ConsumeInput() will be called for each input that need to be mixed.
    void ConsumeInput(AK::IAkMixerInputContext* in_pInputContext, AkRamp in_baseVolume, AkRamp in_emitListVolume, AkAudioBuffer* io_pInputBuffer, AkAudioBuffer* io_pMixBuffer) override;

    /// This function is called once every audio frame, when all inputs have been mixed in
    /// with ConsumeInput(). It is the time when the plugin may perform final DSP/bookkeeping.
    /// After the bus buffer io_pMixBuffer has been pushed to the bus downstream
    /// (or the output device), it is cleared out for the next frame.
    void OnMixDone(AkAudioBuffer* io_pMixBuffer) override;

    /// This function is called once every audio frame, after all insert effects
    /// on the bus have been processed, which occur after the post mix pass of OnMixDone().
    /// After the bus buffer io_pMixBuffer has been pushed to the bus downstream
    /// (or the output device), it is cleared out for the next frame.
    void OnEffectsProcessed(AkAudioBuffer* io_pMixBuffer) override;

    /// This function is called once every audio frame, after all insert effects
    /// on the bus have been processed, and after metering has been processed
    /// (if applicable), which occur after OnEffectsProcessed().
    /// After the bus buffer io_pMixBuffer has been pushed to the bus downstream
    /// (or the output device), it is cleared out for the next frame.
    /// Mixer plugins may use this hook for processing the signal after it has been metered.
    void OnFrameEnd(AkAudioBuffer* io_pMixBuffer, AK::IAkMetering* in_pMetering) override;

private:
    Mach1DecodePluginFXParams* m_pParams;
    AK::IAkPluginMemAlloc* m_pAllocator;
    AK::IAkMixerPluginContext* m_pContext;
};

#endif // Mach1DecodePluginFX_H
