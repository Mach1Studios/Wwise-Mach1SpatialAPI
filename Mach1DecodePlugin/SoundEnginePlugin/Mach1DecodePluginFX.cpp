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

#include "Mach1DecodePluginFX.h"
#include "../Mach1DecodePluginConfig.h"

#include <AK/AkWwiseSDKVersion.h>

AK::IAkPlugin* CreateMach1DecodePluginFX(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, Mach1DecodePluginFX());
}

AK::IAkPluginParam* CreateMach1DecodePluginFXParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, Mach1DecodePluginFXParams());
}

AK::IAkPluginParam* CreateMach1DecodePluginFXAttachmentParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, Mach1DecodePluginFXAttachmentParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(Mach1DecodePluginFX, AkPluginTypeMixer, Mach1DecodePluginConfig::CompanyID, Mach1DecodePluginConfig::PluginID)
AK::PluginRegistration Mach1DecodePluginFXAttachmentParamsRegistration(AkPluginTypeEffect, Mach1DecodePluginAttachmentConfig::CompanyID, Mach1DecodePluginAttachmentConfig::PluginID, nullptr, CreateMach1DecodePluginFXAttachmentParams);

Mach1DecodePluginFX::Mach1DecodePluginFX()
    : m_pParams(nullptr)
    , m_pAllocator(nullptr)
    , m_pContext(nullptr)
{
}

Mach1DecodePluginFX::~Mach1DecodePluginFX()
{
}

AKRESULT Mach1DecodePluginFX::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkMixerPluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pParams = (Mach1DecodePluginFXParams*)in_pParams;
    m_pAllocator = in_pAllocator;
    m_pContext = in_pContext;

    return AK_Success;
}

AKRESULT Mach1DecodePluginFX::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT Mach1DecodePluginFX::Reset()
{
    return AK_Success;
}

AKRESULT Mach1DecodePluginFX::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeMixer;
    out_rPluginInfo.bIsInPlace = true;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

void Mach1DecodePluginFX::OnInputConnected(AK::IAkMixerInputContext* in_pInput)
{
    // Handle input connected here
}

void Mach1DecodePluginFX::OnInputDisconnected(AK::IAkMixerInputContext* in_pInput)
{
    // Handle input disconnected here
}

void Mach1DecodePluginFX::ConsumeInput(AK::IAkMixerInputContext* in_pInputContext, AkRamp in_baseVolume, AkRamp in_emitListVolume, AkAudioBuffer* io_pInputBuffer, AkAudioBuffer* io_pMixBuffer)
{
    // Consume input buffer and mix it here
    AkRamp baseVolume = in_baseVolume * in_emitListVolume;

    AkUInt32 uAllocSize = AK::SpeakerVolumes::Matrix::GetRequiredSize(io_pInputBuffer->NumChannels(), io_pMixBuffer->NumChannels());
    AK::SpeakerVolumes::MatrixPtr volumesPrev = (AK::SpeakerVolumes::MatrixPtr)AkAlloca(uAllocSize);
    AK::SpeakerVolumes::MatrixPtr volumesNext = (AK::SpeakerVolumes::MatrixPtr)AkAlloca(uAllocSize);
    in_pInputContext->GetSpatializedVolumes(volumesPrev, volumesNext);

    AK_GET_PLUGIN_SERVICE_MIXER(m_pContext->GlobalContext())->MixNinNChannels(
        io_pInputBuffer,
        io_pMixBuffer,
        baseVolume.fPrev,
        baseVolume.fNext,
        volumesPrev,
        volumesNext);

    io_pMixBuffer->uValidFrames = io_pInputBuffer->uValidFrames;
}

void Mach1DecodePluginFX::OnMixDone(AkAudioBuffer* io_pMixBuffer)
{
    // Execute DSP after all inputs have been mixed here
}

void Mach1DecodePluginFX::OnEffectsProcessed(AkAudioBuffer* io_pMixBuffer)
{
    // Execute DSP after insert effects have been processed here
}

void Mach1DecodePluginFX::OnFrameEnd(AkAudioBuffer* io_pMixBuffer, AK::IAkMetering* in_pMetering)
{
    // Execute DSP after metering has been processed here
}
