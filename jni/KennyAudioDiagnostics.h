#pragma once
#include "KennyDiagnostics.h"
#include <array>
namespace KennyAudioDiagnostics {
enum class Code:unsigned {EngineReady,EngineFailed,DirectoryFound,DirectoryMissing,ManifestLoaded,ManifestFailed,PackSelected,FileLoaded,FileMissing,DecodeFailed,Received,Suppressed,Unmapped,Submitted,QueueFailed,PlaybackStarted,PlaybackFailed,CallbackObserved,Count};
inline constexpr const char* Names[]={"AUDIO_ENGINE_INITIALIZED","AUDIO_ENGINE_FAILED","MEDIA_DIRECTORY_FOUND","MEDIA_DIRECTORY_MISSING","CHARACTER_MANIFEST_LOADED","CHARACTER_MANIFEST_FAILED","VOICE_PACK_SELECTED","VOICE_FILE_LOADED","VOICE_FILE_MISSING","VOICE_DECODE_FAILED","VOICE_EVENT_RECEIVED","VOICE_EVENT_SUPPRESSED","VOICE_EVENT_UNMAPPED","VOICE_SUBMITTED","AUDIO_QUEUE_FAILED","PLAYBACK_STARTED","PLAYBACK_FAILED","AUDIO_CALLBACK_OBSERVED"};
enum class Result:unsigned {Idle,Queued,EngineUnavailable,SoundDisabled,VoiceDisabled,ControlDisabled,UiVolumeZero,VoiceVolumeZero,WrongTheme,WrongCharacter,WrongPack,MissingRecording,DecodeFailed,Cooldown,QueueFull,InvalidTime};
inline const char* Reason(Result r){switch(r){case Result::Queued:return "accepted_into_queue";case Result::EngineUnavailable:return "audio_engine_unavailable";case Result::SoundDisabled:return "disabled_sounds";case Result::VoiceDisabled:return "disabled_character_voice";case Result::ControlDisabled:return "disabled_control_feedback";case Result::UiVolumeZero:return "zero_ui_volume";case Result::VoiceVolumeZero:return "zero_character_volume";case Result::WrongTheme:return "wrong_selected_theme";case Result::WrongCharacter:return "wrong_character";case Result::WrongPack:return "wrong_or_missing_voice_pack";case Result::MissingRecording:return "missing_recording";case Result::DecodeFailed:return "recording_decode_failed";case Result::Cooldown:return "cooldown";case Result::QueueFull:return "audio_queue_full";case Result::InvalidTime:return "invalid_event_time";default:return "not_tested";}}
inline const char* Status(Result r){switch(r){case Result::Queued:return "Voice queued. Speaker playback is not yet verified.";case Result::EngineUnavailable:return "Audio engine unavailable; see engine diagnostic/error.";case Result::SoundDisabled:return "UI sounds are disabled.";case Result::VoiceDisabled:return "Character voice is disabled.";case Result::ControlDisabled:return "Control voice feedback is disabled.";case Result::UiVolumeZero:return "UI sound volume is zero.";case Result::VoiceVolumeZero:return "Character voice volume is zero.";case Result::WrongTheme:return "Select Anime before testing a character voice.";case Result::WrongCharacter:return "Selected character is not installed.";case Result::WrongPack:return "Selected voice pack is missing; install/select the supplied pack.";case Result::MissingRecording:return "Selected event has no installed recording.";case Result::DecodeFailed:return "Selected recording could not be decoded.";case Result::Cooldown:return "Suppressed by speech cooldown; no new voice was queued.";case Result::QueueFull:return "Audio queue rejected the recording.";case Result::InvalidTime:return "Invalid event clock; recording not queued.";default:return "Press Test Voice to check the selected recording.";}}
// This logger runs only on load/user-interaction/render-owner failure edges.
// Never call it from the OpenSL callback. No private absolute paths are logged.
struct Budget {double window=0;unsigned entries=0;};
inline void Log(Code code,const char* reason="none",int error=0,const char* event="none"){
    static thread_local Budget budget;timespec t{};clock_gettime(CLOCK_MONOTONIC,&t);double now=t.tv_sec+t.tv_nsec*1e-9;
    if(now-budget.window>=30 || now<budget.window){budget.window=now;budget.entries=0;}
    if(budget.entries>=96)return;++budget.entries;
    const bool failure=code==Code::EngineFailed||code==Code::ManifestFailed||code==Code::DecodeFailed||code==Code::PlaybackFailed||code==Code::QueueFailed;
    const bool ok=!failure&&code!=Code::Suppressed&&code!=Code::Unmapped&&code!=Code::DirectoryMissing&&code!=Code::FileMissing;
    KennyDiagnostics::Event(40,failure?KennyDiagnostics::Severity::Error:ok?KennyDiagnostics::Severity::Info:KennyDiagnostics::Severity::Warning,error,ok,"%s reason=%s event=%s",Names[unsigned(code)],reason,event);
}
// Callback-safe transport counters/mailbox: no I/O, locks or allocation.
struct Transport {
    std::atomic<unsigned> callbackError{0},pending{0};
    std::atomic<bool> firstCallback{false},native{false};
    std::atomic<uint64_t> buffersSubmitted{0},callbacks{0},recordingsStarted{0};
    void Callback(unsigned error=0){callbacks.fetch_add(1,std::memory_order_relaxed);if(error){callbackError.store(error,std::memory_order_release);pending.fetch_or(2,std::memory_order_release);}else if(!firstCallback.exchange(true,std::memory_order_acq_rel))pending.fetch_or(1,std::memory_order_release);}
    unsigned Drain(){return pending.exchange(0,std::memory_order_acq_rel);}
};
} // namespace KennyAudioDiagnostics
