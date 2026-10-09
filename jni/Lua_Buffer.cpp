#pragma once
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdint>
#include <android/log.h>

#define KAUSHIK_NAME "SHADOW"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  "LUA_46", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "LUA_46", __VA_ARGS__)

// ==================== OFFSETLER (4.6 GÜNCEL) ====================
#define LuaLoadBuffer_Offset  0xB51186C
#define LuaPCall_Offset       0xB4ED430
#define LuaLoad_Offset        0xB4ED430
#define ProcessEvent_Offset   0x8be9d08




const char* bypass_script = R"lua(

local function nop() return end
local function nopstr() return "" end
local function nopfalse() return false end
local function noptrue() return true end
local function nopnil() return nil end
local function retFalse() return false end
local function retTrue() return true end

_G.BypassPermissions = {
    SecurityBypass = true,
    AntiCheatBypass = true,
    ReportBypass = true,
    BanBypass = true,
    TelemetryBypass = true,
    NetworkBypass = true,
    MD5Bypass = true,
    SignatureBypass = true,
    DNSBypass = true,
    DeviceBypass = true,
    IPBypass = true,
    MACBypass = true,
    IMEIBypass = true,
    AndroidIDBypass = true,
    AllFeaturesEnabled = true,
    NoReports = true,
    NoBan = true,
    NoDetection = true,
    NoTelemetry = true,
    NoCrashReport = true,
    NoAnalytics = true,
    NoMonitor = true,
    NoTrack = true,
    NoScan = true,
    NoVerify = true,
    NoCheck = true,
    NoValidate = true
}

_G.BlockedIPs = {
    "43.128.0.0/16", "43.129.0.0/16", "43.130.0.0/16", "43.131.0.0/16",
    "43.132.0.0/16", "43.133.0.0/16", "43.134.0.0/16", "43.135.0.0/16",
    "43.136.0.0/16", "43.137.0.0/16", "43.138.0.0/16", "43.139.0.0/16",
    "43.140.0.0/16", "43.141.0.0/16", "43.142.0.0/16", "43.143.0.0/16",
    "43.144.0.0/16", "43.145.0.0/16", "43.146.0.0/16", "43.147.0.0/16",
    "43.148.0.0/16", "43.149.0.0/16", "43.150.0.0/16", "43.151.0.0/16",
    "43.152.0.0/16", "43.153.0.0/16", "43.154.0.0/16", "43.155.0.0/16",
    "43.156.0.0/16", "43.157.0.0/16", "43.158.0.0/16", "43.159.0.0/16",
    "43.160.0.0/16", "43.161.0.0/16", "43.162.0.0/16", "43.163.0.0/16",
    "43.164.0.0/16", "43.165.0.0/16", "43.166.0.0/16", "43.167.0.0/16",
    "43.168.0.0/16", "43.169.0.0/16", "43.170.0.0/16", "43.171.0.0/16",
    "43.172.0.0/16", "43.173.0.0/16", "43.174.0.0/16", "43.175.0.0/16",
    "43.176.0.0/16", "43.177.0.0/16", "43.178.0.0/16", "43.179.0.0/16",
    "43.180.0.0/16", "43.181.0.0/16", "43.182.0.0/16", "43.183.0.0/16",
    "43.184.0.0/16", "43.185.0.0/16", "43.186.0.0/16", "43.187.0.0/16",
    "43.188.0.0/16", "43.189.0.0/16", "43.190.0.0/16", "43.191.0.0/16",
    "43.192.0.0/16", "43.193.0.0/16", "43.194.0.0/16", "43.195.0.0/16",
    "43.196.0.0/16", "43.197.0.0/16", "43.198.0.0/16", "43.199.0.0/16",
    "43.200.0.0/16", "43.201.0.0/16", "43.202.0.0/16", "43.203.0.0/16",
    "43.204.0.0/16", "43.205.0.0/16", "43.206.0.0/16", "43.207.0.0/16",
    "43.208.0.0/16", "43.209.0.0/16", "43.210.0.0/16", "43.211.0.0/16",
    "43.212.0.0/16", "43.213.0.0/16", "43.214.0.0/16", "43.215.0.0/16",
    "43.216.0.0/16", "43.217.0.0/16", "43.218.0.0/16", "43.219.0.0/16",
    "43.220.0.0/16", "43.221.0.0/16", "43.222.0.0/16", "43.223.0.0/16",
    "43.224.0.0/16", "43.225.0.0/16", "43.226.0.0/16", "43.227.0.0/16",
    "43.228.0.0/16", "43.229.0.0/16", "43.230.0.0/16", "43.231.0.0/16",
    "43.232.0.0/16", "43.233.0.0/16", "43.234.0.0/16", "43.235.0.0/16",
    "43.236.0.0/16", "43.237.0.0/16", "43.238.0.0/16", "43.239.0.0/16",
    "43.240.0.0/16", "43.241.0.0/16", "43.242.0.0/16", "43.243.0.0/16",
    "43.244.0.0/16", "43.245.0.0/16", "43.246.0.0/16", "43.247.0.0/16",
    "43.248.0.0/16", "43.249.0.0/16", "43.250.0.0/16", "43.251.0.0/16",
    "43.252.0.0/16", "43.253.0.0/16", "43.254.0.0/16", "43.255.0.0/16",
    "129.204.0.0/16", "129.205.0.0/16", "129.206.0.0/16", "129.207.0.0/16",
    "129.208.0.0/16", "129.209.0.0/16", "129.210.0.0/16", "129.211.0.0/16",
    "129.212.0.0/16", "129.213.0.0/16", "129.214.0.0/16", "129.215.0.0/16",
    "129.216.0.0/16", "129.217.0.0/16", "129.218.0.0/16", "129.219.0.0/16",
    "129.220.0.0/16", "129.221.0.0/16", "129.222.0.0/16", "129.223.0.0/16",
    "129.224.0.0/16", "129.225.0.0/16", "129.226.0.0/16", "129.227.0.0/16",
    "129.228.0.0/16", "129.229.0.0/16", "129.230.0.0/16", "129.231.0.0/16",
    "129.232.0.0/16", "129.233.0.0/16", "129.234.0.0/16", "129.235.0.0/16",
    "129.236.0.0/16", "129.237.0.0/16", "129.238.0.0/16", "129.239.0.0/16",
    "129.240.0.0/16", "129.241.0.0/16", "129.242.0.0/16", "129.243.0.0/16",
    "129.244.0.0/16", "129.245.0.0/16", "129.246.0.0/16", "129.247.0.0/16",
    "129.248.0.0/16", "129.249.0.0/16", "129.250.0.0/16", "129.251.0.0/16",
    "129.252.0.0/16", "129.253.0.0/16", "129.254.0.0/16", "129.255.0.0/16",
    "185.244.0.0/16", "185.245.0.0/16", "185.246.0.0/16", "185.247.0.0/16",
    "185.248.0.0/16", "185.249.0.0/16", "185.250.0.0/16", "185.251.0.0/16",
    "185.252.0.0/16", "185.253.0.0/16", "185.254.0.0/16", "185.255.0.0/16",
    "104.0.0.0/8", "104.1.0.0/8", "104.2.0.0/8", "104.3.0.0/8",
    "104.4.0.0/8", "104.5.0.0/8", "104.6.0.0/8", "104.7.0.0/8",
    "104.8.0.0/8", "104.9.0.0/8", "104.10.0.0/8", "104.11.0.0/8",
    "104.12.0.0/8", "104.13.0.0/8", "104.14.0.0/8", "104.15.0.0/8",
    "104.16.0.0/8", "104.17.0.0/8", "104.18.0.0/8", "104.19.0.0/8",
    "104.20.0.0/8", "104.21.0.0/8", "104.22.0.0/8", "104.23.0.0/8",
    "104.24.0.0/8", "104.25.0.0/8", "104.26.0.0/8", "104.27.0.0/8",
    "104.28.0.0/8", "104.29.0.0/8", "104.30.0.0/8", "104.31.0.0/8"
}

_G.AntiCheatBlock = {
    BlockAllAntiCheat = true,
    BlockTSS = true,
    BlockGokuba = true,
    BlockSwiftHawk = true,
    BlockCoronaLab = true,
    BlockHawkEye = true,
    BlockHiggsBoson = true,
    BlockClientBan = true,
    BlockRealTimeBan = true,
    BlockReportSystem = true,
    BlockTLog = true,
    BlockMD5Check = true,
    BlockSignatureVerify = true,
    BlockDeviceFingerprint = true,
    BlockDNSMonitor = true,
    BlockTelemetry = true,
    BlockAnalytics = true,
    BlockCrashReport = true,
    BlockMemoryScan = true,
    BlockSpeedCheck = true,
    BlockWallCheck = true,
    BlockShootVerify = true,
    BlockModifierException = true,
    BlockSimulateLocation = true,
    BlockPlayerSecurity = true,
    BlockCircleFlow = true,
    BlockMrpcsFlow = true,
    BlockKillFlow = true,
    BlockBehaviorScore = true,
    BlockAFKReport = true,
    BlockAvatarException = true,
    BlockFileCheck = true,
    BlockPakVerify = true,
    BlockIntegrityCheck = true,
    BlockRacingAntiCheat = true,
    BlockClientEntry = true,
    BlockNetworkException = true,
    BlockUnrealNet = true,
    BlockReplay = true,
    BlockScreenshot = true,
    BlockDebugLog = true
}

local function ClientEntryBypass()
    pcall(function()
        if Client then
            Client.SetTssNetworkStatus = nop
            Client.GEMReportEnterLobbyEvent = nop
            Client.TPerforPlatDisconnectReport = nop
            Client.IsConnected = function(NetInterface) return true end
            Client.GetUnrealNetworkStatus = nopstr
            Client.MD5LuaString = function(str) return "BYPASSED_MD5" end
            Client.GetDSVersion = function() return "999.999.999" end
            Client.IsInReplayState = nopfalse
        end
        if NetManager then
            NetManager.ProcRespondMsg = nop
            NetManager.isLogMsgAfterLogin = false
            NetManager.logMsgMap = {}
        end
        if EventSystem then
            local oldPost = EventSystem.postEvent
            EventSystem.postEvent = function(eventType, eventID, ...)
                if eventID and type(eventID) == "string" then
                    local blocked = {"SECURITY", "CHEAT", "BAN", "REPORT", "FLAG", "VIOLATION", "DETECT", "VERIFY", "ANTI", "AC_", "SUSPICIOUS", "ABNORMAL", "MONITOR", "TRACK", "TELEMETRY", "ANALYTICS", "CRASH", "DUMP"}
                    for _, be in ipairs(blocked) do
                        if eventID:find(be) then return end
                    end
                end
                if oldPost then oldPost(eventType, eventID, ...) end
            end
        end
        local logFuncs = {"log", "log_warning", "log_error", "log_shipping_client", "log_format", "log_tree"}
        for _, funcName in ipairs(logFuncs) do
            if _G[funcName] then
                _G[funcName] = function(...)
                    local args = {...}
                    for _, arg in ipairs(args) do
                        if type(arg) == "string" and (arg:find("cheat") or arg:find("security") or arg:find("ban") or arg:find("detect") or arg:find("verify") or arg:find("integrity") or arg:find("report") or arg:find("violation") or arg:find("hack") or arg:find("anti") or arg:find("ac_") or arg:find("suspicious") or arg:find("abnormal") or arg:find("monitor") or arg:find("track")) then return end
                    end
                end
            end
        end
        if LogUtil then
            LogUtil.SetForceLog = nop
            LogUtil.SetLogTreeEnable = nop
            LogUtil.SetWriteLog = nop
        end
        if sandbox then 
            sandbox.LogError = nop
            sandbox.LogWarning = nop 
        end
    end)
end

local function HiggsBosonBypass()
    pcall(function()
        if CHiggsBosonComponent then
            CHiggsBosonComponent.ReceiveBeginPlay = nop
            CHiggsBosonComponent.StaticShowSecurityAlertInDev = nop
            CHiggsBosonComponent.ShowABCD = nop
            CHiggsBosonComponent._ClientShowSecurityAlertWindow = nop
            CHiggsBosonComponent._ReportChatRobot = nop
            CHiggsBosonComponent.SendAntiDataFlow = nop
            CHiggsBosonComponent.SendHitFireBtnFlow = nop
            CHiggsBosonComponent.OnBattleResult = nop
            CHiggsBosonComponent.SendHisarData = nop
            CHiggsBosonComponent.RPC_Client_ShowSecurityAlertWindow = nop
            CHiggsBosonComponent.RPC_Server_TellServerName = nop
            CHiggsBosonComponent.RecordStrategyTimestampInReplay = nop
            CHiggsBosonComponent.SkipAlertServer = nop
            CHiggsBosonComponent.SetClientAlertWindowEnabled = nop
            CHiggsBosonComponent.IsCharacterOwnerWerewolf = nopfalse
            CHiggsBosonComponent.IsCharacterOwnerButcher = nopfalse
            CHiggsBosonComponent._ProcessReportChatRobotQueue = nop
            CHiggsBosonComponent.LuaNotifySecurityAbnormalJump = nop
            CHiggsBosonComponent.bSkipAlertServer = true
            CHiggsBosonComponent.bMHActive = false
            CHiggsBosonComponent.bCallPreReplication = false
        end
        local GameplayData = require("GameLua.GameCore.Data.GameplayData")
        if GameplayData then
            local pc = GameplayData.GetPlayerController()
            if slua.isValid(pc) then
                if pc.HiggsBoson then
                    pc.HiggsBoson.bMHActive = false
                    pc.HiggsBoson.bCallPreReplication = false
                end
                if pc.HiggsBosonComponent then
                    pc.HiggsBosonComponent.bMHActive = false
                    pc.HiggsBosonComponent.bCallPreReplication = false
                end
            end
        end
    end)
end

local function HawkEyeBypass()
    pcall(function()
        if ClientHawkEyePatrolSubsystem then
            ClientHawkEyePatrolSubsystem._OnHawkSync = nop
            ClientHawkEyePatrolSubsystem._OnHawkReportSuccess = nop
            ClientHawkEyePatrolSubsystem._OnRecvInspectorBroadcastCount = nop
            ClientHawkEyePatrolSubsystem.ReportCheat = nop
            ClientHawkEyePatrolSubsystem.RequestImprison = nop
            ClientHawkEyePatrolSubsystem.SendReportTLog = nop
            ClientHawkEyePatrolSubsystem.IsDuringHawkEyePatrol = nopfalse
            ClientHawkEyePatrolSubsystem._CollectBeWatchedPlayerInfo = nop
            ClientHawkEyePatrolSubsystem.HasReported = noptrue
            ClientHawkEyePatrolSubsystem.GetBeWatchedPlayerInfo = nopnil
            ClientHawkEyePatrolSubsystem._OnPlayerKilledOtherPlayer = nop
            ClientHawkEyePatrolSubsystem._StartFrameUIRefreshTimer = nop
            ClientHawkEyePatrolSubsystem.ExitWatching = nop
            ClientHawkEyePatrolSubsystem.WantMatchNextPatrol = nop
            ClientHawkEyePatrolSubsystem._InitHawkEyePatrolSubsystem = function(self)
                self._bHasInitialized = true
                self._bHasReported = true
            end
            ClientHawkEyePatrolSubsystem._StartHideUITimer = nop
            ClientHawkEyePatrolSubsystem._StartShowDistanceUITimer = nop
            ClientHawkEyePatrolSubsystem._StartCloseBattleEndedTipsTimer = nop
            ClientHawkEyePatrolSubsystem._StartBattleTimeUsageTimer = nop
            ClientHawkEyePatrolSubsystem._StartQuitVoiceRoomTimer = nop
            ClientHawkEyePatrolSubsystem._StartExitGameTimer = nop
            ClientHawkEyePatrolSubsystem._CloseExitGameTimer = nop
            ClientHawkEyePatrolSubsystem._CreateOvertimerTimerForNextPatrol = nop
            ClientHawkEyePatrolSubsystem.ClearNextPatrolOvertimeTimer = nop
            ClientHawkEyePatrolSubsystem.ReturnLobbyAndOpenH5 = nop
            ClientHawkEyePatrolSubsystem.ForceNeverCloseBattleEndedTips = nop
            ClientHawkEyePatrolSubsystem.CheckShowReportedTips = nopfalse
            ClientHawkEyePatrolSubsystem.TryShowReportedTips = nop
            ClientHawkEyePatrolSubsystem.ShowWatchEndedTips = nop
            ClientHawkEyePatrolSubsystem.HasShownWatchEndedTips = noptrue
            ClientHawkEyePatrolSubsystem.OnShowWatchEndedTips = nop
            ClientHawkEyePatrolSubsystem.OnClickLowerLeftExitWatching = nop
            ClientHawkEyePatrolSubsystem.OnClickBottomRightOpenReportWindow = nop
            ClientHawkEyePatrolSubsystem._MarkHasReported = nop
            ClientHawkEyePatrolSubsystem.GetForbidNextPatrolRemainingTimeInSeconds = function() return 0 end
            ClientHawkEyePatrolSubsystem.GetUsedDailyTimeInSeconds = function() return 0 end
            ClientHawkEyePatrolSubsystem.GetInspectorBroadcastCount = function() return -1 end
            ClientHawkEyePatrolSubsystem.GetMaxInspectorBroadcastCount = function() return 0 end
            ClientHawkEyePatrolSubsystem.CanInspectorBroadcast = nopfalse
            ClientHawkEyePatrolSubsystem.IsCharacterLocationShouldDraw = nopfalse
            ClientHawkEyePatrolSubsystem.InitHawkEyePatrolSubsystem = nop
            ClientHawkEyePatrolSubsystem._PostConstruct = function(self)
                self._bHasInitialized = true
                self._bHasReported = true
                self.nInspectorBroadcastCount = -1
            end
            ClientHawkEyePatrolSubsystem.OnRelease = nop
            ClientHawkEyePatrolSubsystem._bHasInitialized = true
            ClientHawkEyePatrolSubsystem._bHasReported = true
            ClientHawkEyePatrolSubsystem._bHasShownWatchEndedTips = true
            ClientHawkEyePatrolSubsystem.bShowBeReportedTips = true
            ClientHawkEyePatrolSubsystem.nInspectorBroadcastCount = -1
        end
        if DSHawkEyePatrolSubsystem then
            DSHawkEyePatrolSubsystem.OnInit = nop
            DSHawkEyePatrolSubsystem.ReportCheat = nop
            DSHawkEyePatrolSubsystem.RequestImprison = nop
        end
    end)
end

local function BanLogicBypass()
    pcall(function()
        if ClientBanLogic then
            ClientBanLogic.ReqBanInfo = nop
            ClientBanLogic.OnVoiceSwitchNotify = nop
            ClientBanLogic.OnVoiceBanNotify = nop
            ClientBanLogic.OnRealTimeVoiceBanNotify = nop
            ClientBanLogic.OnVoiceBanSuccess = nop
            ClientBanLogic.TryOpenVoice = function()
                EventSystem:postEvent(EVENTTYPE_INGAME_BAN, EVENTID_INGAME_BAN_FORBID_VOICE, false)
            end
            ClientBanLogic.IsVoiceReportEnable = nopfalse
            ClientBanLogic.OnSyncMicSuspicious = nop
            ClientBanLogic.OnSyncMicPreFilter = nop
            ClientBanLogic.OnSyncBanInfo = nop
            ClientBanLogic.OnNotifyWarningTips = nop
            ClientBanLogic.VoiceBanEndTime = 0
            ClientBanLogic.bEnableVoiceReport = false
            ClientBanLogic.SuspiciousFlag = 0
            ClientBanLogic.Reason = ""
            ClientBanLogic.IsTranslated = false
        end
        if RealTimeBan then
            RealTimeBan.Init = function() return end
            RealTimeBan.OnPlayerWithRealTimeBan = nop
            RealTimeBan.OnSyncPlayerInfo = nop
            RealTimeBan.HandleEnterGameModeFightingState = nop
            RealTimeBan.ShowAlias = nop
            RealTimeBan.SetOnRankInspectorUID = nop
            RealTimeBan.IsUIDOnRankInspector = nopfalse
            RealTimeBan.GetUIDInspectorRank = function() return -1 end
            RealTimeBan.SetInspectorBroadcastCountUID = nop
            RealTimeBan.GetUIDInspectorBroadcastCount = function() return -1 end
            RealTimeBan.GetTipsIDOffset = function() return 0 end
            RealTimeBan.GetTipsIDOffsetWithUID = function() return 0 end
            RealTimeBan.GetTipsIDOffsetInspector = function() return 0 end
            RealTimeBan.GMShowAlias = nop
            RealTimeBan.tOnRankInspectorUIDSet = {}
            RealTimeBan.tInspectorRankUIDSet = {}
            RealTimeBan.tInspectorBroadcastCountUIDSet = {}
            RealTimeBan.MaxAliasLevel = -1
            RealTimeBan.CurrentAlias = nil
            RealTimeBan.CurrentName = nil
            RealTimeBan.is_onrank_inspector = false
            RealTimeBan.inspector_rank = -1
            RealTimeBan.bHasOldAlias = false
            RealTimeBan.ShowTipsAliasConfig = {}
            RealTimeBan.DelayTime = {}
            RealTimeBan.OldShowTipsAlias = 0
        end
        if BanSystem then
            BanSystem.CheckBan = retFalse
            BanSystem.IsBanned = retFalse
            BanSystem.GetBanReason = function() return "" end
            BanSystem.GetBanTime = function() return 0 end
        end
    end)
end

local function ReportSystemBypass()
    pcall(function()
        if ClientReportPlayerSubsystem then
            ClientReportPlayerSubsystem.OnInit = nop
            ClientReportPlayerSubsystem._OnPlayerKilledOtherPlayer = nop
            ClientReportPlayerSubsystem._RecordFatalDamager = nop
            ClientReportPlayerSubsystem._RecordMurdererFromDeathReplayData = nop
            ClientReportPlayerSubsystem._OnSyncFatalDamage = nop
            ClientReportPlayerSubsystem._SyncBattleResult = nop
            ClientReportPlayerSubsystem._OnBattleResult = nop
            ClientReportPlayerSubsystem._OnShowQuickReportMutualExclusiveUI = nop
            ClientReportPlayerSubsystem._OnHideQuickReportMutualExclusiveUI = nop
            ClientReportPlayerSubsystem._StartCheckGameModeTypeTimer = nop
            ClientReportPlayerSubsystem._CheckGameModeType = nop
            ClientReportPlayerSubsystem._StartCheckCurrentNotInTeamHistoricalTeammateTimer = nop
            ClientReportPlayerSubsystem._CheckCurrentNotInTeamHistoricalTeammate = nop
            ClientReportPlayerSubsystem._RecordTeammatePlayerInfo = nop
            ClientReportPlayerSubsystem._IsHealthStatusKilled = nopfalse
            ClientReportPlayerSubsystem.GetFatalDamagerMap = function() return {} end
            ClientReportPlayerSubsystem.GetFatalDamagerMapSize = function() return 0 end
            ClientReportPlayerSubsystem.GetName2InfoMap = function() return {} end
            ClientReportPlayerSubsystem.GetCachedTeammateName2InfoMap = function() return {} end
            ClientReportPlayerSubsystem.GetTeammateName2InfoMapDuringBattle = function() return {} end
            ClientReportPlayerSubsystem.GetCurrentNotInTeamHistoricalTeammateMap = function() return {} end
            ClientReportPlayerSubsystem.GetInTeamIndexFromHistoricalTeammateInfo = function() return -1 end
            ClientReportPlayerSubsystem.IsGameModeTypeTeamDeathMatch = nopfalse
            ClientReportPlayerSubsystem.GetGameModeType = function() return -1 end
            ClientReportPlayerSubsystem.GetMainModeID = function() return -1 end
            ClientReportPlayerSubsystem.GetSubModeID = function() return -1 end
            ClientReportPlayerSubsystem.EnableRecordFatalDamage = nop
            ClientReportPlayerSubsystem._tKnockDownerMap = {}
            ClientReportPlayerSubsystem._tMurdererMap = {}
            ClientReportPlayerSubsystem._ds2history = {}
            ClientReportPlayerSubsystem._tMapCurrentNotInTeamHistoricalTeammate = {}
            ClientReportPlayerSubsystem._tTeammateName2InfoMap = {}
            ClientReportPlayerSubsystem._bEnableRecordFatalDamage = false
            ClientReportPlayerSubsystem._bIsGameModeTypeTeamDeathMatch = false
            ClientReportPlayerSubsystem._nGameModeType = -1
            ClientReportPlayerSubsystem._nMainModeID = -1
            ClientReportPlayerSubsystem._nSubModeID = -1
            ClientReportPlayerSubsystem._nCheckTDMGameModeTypeTimer = nil
            ClientReportPlayerSubsystem._nCurrentNotInTeamHistoricalTeammateTimer = nil
        end
        if DSReportPlayerSubsystem then
            DSReportPlayerSubsystem.OnInit = nop
            DSReportPlayerSubsystem._OnNearDeathOrRescued = nop
            DSReportPlayerSubsystem._OnPlayerSettlementStart = nop
            DSReportPlayerSubsystem._OnTeammateDamage = nop
            DSReportPlayerSubsystem._OnCharacterDied = nop
            DSReportPlayerSubsystem._OnPlayerReconnect = nop
            DSReportPlayerSubsystem._RecordFatalDamager = nop
            DSReportPlayerSubsystem._RecordTeammateMurderer = nop
            DSReportPlayerSubsystem._AddMLKillerUIDToBattleResult = nop
            DSReportPlayerSubsystem._AddFatalDamagerMapToBattleResult = nop
            DSReportPlayerSubsystem._AddKnockDownerToBattleResult = nop
            DSReportPlayerSubsystem._AddKillerToBattleResult = nop
            DSReportPlayerSubsystem._AddTeammateMurderToBattleResult = nop
            DSReportPlayerSubsystem._SaveHistoricalTeammateInfo = nop
            DSReportPlayerSubsystem._SyncFatalDamagerMap = nop
            DSReportPlayerSubsystem._AddGameModeTypeToBattleResult = nop
            DSReportPlayerSubsystem._UpdateMLAIUID = nop
            DSReportPlayerSubsystem._AddEnemyMapToBattleResult = nop
            DSReportPlayerSubsystem._OnNoNetStartUpDoor = nop
            DSReportPlayerSubsystem._AssignTeammateInTeamIndex = nop
            DSReportPlayerSubsystem._FindCacheByUID = function(self, nUID, bAddIfNotExists)
                if bAddIfNotExists then return {} end
                return nil
            end
            DSReportPlayerSubsystem._GetFatalDamagerMap = function() return {} end
            DSReportPlayerSubsystem._IsBattleResultTableValid = nopfalse
            DSReportPlayerSubsystem._IsHealthStatusKilled = nopfalse
            DSReportPlayerSubsystem._tUID2InfoMap = {}
            DSReportPlayerSubsystem.nNoStartUpDoorNum = 0
        end
        if ui_complaint then
            ui_complaint.SubmitReportData = function(self) self:CloseWindow(false) return end
            ui_complaint._OnClickReport = function(self) return end
            ui_complaint._AddCommonTypesOfPlayerForReport = function(self) return end
            ui_complaint.AddPlayerForReport = function(self, ...) return end
            ui_complaint.GetSelectedReasonAsArray = function(self) return {} end
            ui_complaint.GetSelectedSubReasonAsArray = function(self) return {} end
            ui_complaint.BlockPlayerChat = function(self) return end
            ui_complaint.IsBlockChatCheck = function(self) return false end
            ui_complaint.CheckBoxBlack = function(self, bCheckState) return end
            ui_complaint.UpdateMatchBlackList = function(self) return end
            ui_complaint._SelectedReasonSet = {}
            ui_complaint._SelectedSubReasonSet = {}
            ui_complaint._SelectedCheatSubReasonSet = {}
            ui_complaint._tPlayerName2InfoMap = {}
            ui_complaint._tPlayerNamesArray = {}
        end
        if LogicComplaint then
            LogicComplaint.Submit = function(...) return end
        end
    end)
end

local function TLogBypass()
    pcall(function()
        if tlog_report_utils then
            tlog_report_utils.ReportTLogEvent = nop
            tlog_report_utils.IsCanReportLobbyEvent = nopfalse
            tlog_report_utils.IsBusinessReport = nopfalse
            tlog_report_utils.SetMarketStayUpdateEnable = nop
            tlog_report_utils.GetMarketStayUpdateEnable = nopfalse
            tlog_report_utils.SetBusinessReportEnable = nop
            tlog_report_utils.SendTLogReportImmediate = nop
            tlog_report_utils.SetTlogBeginType = nop
            tlog_report_utils.SetTlogEndType = nop
            _G.SendTLogReportImmediate = nop
        end
        if ToolReportUtil then
            ToolReportUtil.GetReportSwitch = nopfalse
            ToolReportUtil.GetPackageInfo = nopnil
            ToolReportUtil.ReParseError = function(error, reportType) return error or "" end
            ToolReportUtil.IsReleaseVersion = noptrue
            ToolReportUtil.IsWhite = nopfalse
            ToolReportUtil.IsXPcallOpenInBattle = nopfalse
            ToolReportUtil.IsClientToolOpen = nopfalse
            MyOpenID = false
            MyUID = false
            VersionInfo = nil
        end
        if DSSecurityTLogSubsystem then
            DSSecurityTLogSubsystem.OnInit = nop
            DSSecurityTLogSubsystem._OnReportServerJumpFlow = nop
            DSSecurityTLogSubsystem._OnDevAlert = nop
            DSSecurityTLogSubsystem._InitWhenEditor = nop
            DSSecurityTLogSubsystem._nInitGameSafeCallbacksTimer = nil
        end
        if _G.TLog then
            _G.TLog.Info = nop
            _G.TLog.Warning = nop
            _G.TLog.Error = nop
            _G.TLog.Debug = nop
            _G.TLog.Report = nop
            _G.TLog.Send = nop
            _G.TLog.Flush = nop
        end
    end)
end

local function MD5Bypass()
    pcall(function()
        local console = import("KismetSystemLibrary")
        if console then
            console.ExecuteConsoleCommand(nil, "pak.DisablePakSignatureCheck 1")
            console.ExecuteConsoleCommand(nil, "pakchunk.EnableSignatureCheck 0")
            console.ExecuteConsoleCommand(nil, "s.VerifyPak 0")
            console.ExecuteConsoleCommand(nil, "sig.Check 0")
            console.ExecuteConsoleCommand(nil, "security.DisableChecks 1")
            console.ExecuteConsoleCommand(nil, "CheatManager.EnableCheat 1")
            console.ExecuteConsoleCommand(nil, "Net.BlockAllAntiCheat 1")
            console.ExecuteConsoleCommand(nil, "AntiCheat.DisableAll 1")
            console.ExecuteConsoleCommand(nil, "t.MaxFPS 165")
        end
        local CMode = import("CreativeModeBlueprintLibrary")
        if CMode then
            CMode.MD5HashByteArray = function() return "00000000000000000000000000000000" end
            CMode.MD5HashFile = function() return "00000000000000000000000000000000" end
            CMode.GetContentDiffData = function() return true, "BYPASSED" end
            CMode.VerifyFileIntegrity = retTrue
        end
        if _G.MD5Hash then _G.MD5Hash = function() return "00000000000000000000000000000000" end end
        if _G.CRC32 then _G.CRC32 = function() return 0 end end
        if _G.SHA1 then _G.SHA1 = function() return "BYPASS" end end
        if _G.FileHashChecker then
            _G.FileHashChecker.CheckFileMD5 = retTrue
            _G.FileHashChecker.VerifyAll = retTrue
            _G.FileHashChecker.GetHash = function() return "BYPASS" end
        end
        if _G.STExtraBlueprintFunctionLibrary then
            _G.STExtraBlueprintFunctionLibrary.CheckMD5 = retTrue
            _G.STExtraBlueprintFunctionLibrary.GetMD5 = function() return "BYPASS" end
            _G.STExtraBlueprintFunctionLibrary.VerifyFile = retTrue
        end
    end)
end

local function DNSDeviceBypass()
    pcall(function()
        local DeviceID = import("DeviceID")
        if DeviceID then
            DeviceID.GetDeviceID = function() return "BYPASSED_DEVICE" end
            DeviceID.GetAndroidID = function() return "BYPASSED_ANDROID_ID" end
            DeviceID.GetIMEI = function() return "BYPASSED_IMEI" end
            DeviceID.GetMACAddress = function() return "BYPASSED_MAC" end
            DeviceID.GetUniqueDeviceID = function() return "BYPASSED_UNIQUE" end
            DeviceID.GetDeviceName = function() return "BYPASSED_DEVICE_NAME" end
            DeviceID.GetDeviceModel = function() return "BYPASSED_MODEL" end
            DeviceID.GetDeviceBrand = function() return "BYPASSED_BRAND" end
            DeviceID.GetDeviceManufacturer = function() return "BYPASSED_MANUFACTURER" end
            DeviceID.GetDeviceBoard = function() return "BYPASSED_BOARD" end
            DeviceID.GetDeviceBootloader = function() return "BYPASSED_BOOTLOADER" end
            DeviceID.GetDeviceHardware = function() return "BYPASSED_HARDWARE" end
            DeviceID.GetDeviceHost = function() return "BYPASSED_HOST" end
            DeviceID.GetDeviceFingerprint = function() return "BYPASSED_FINGERPRINT" end
            DeviceID.GetDeviceSerial = function() return "BYPASSED_SERIAL" end
        end
        local DNS = import("DNS")
        if DNS then
            DNS.Resolve = function() return "127.0.0.1" end
            DNS.GetHostName = function() return "BYPASSED_HOST" end
            DNS.GetIPAddress = function() return "0.0.0.0" end
        end
        local Network = import("Network")
        if Network then
            Network.GetIPAddress = function() return "0.0.0.0" end
            Network.GetMACAddress = function() return "BYPASSED_MAC" end
            Network.GetSSID = function() return "BYPASSED_SSID" end
            Network.GetBSSID = function() return "BYPASSED_BSSID" end
        end
    end)
end

local function GokubaBypass()
    pcall(function()
        local Gokuba = package.loaded["GameLua.Mod.BaseMod.Client.Security.Gokuba"]
        if Gokuba then
            Gokuba.ForwardFeature = function() return {0,0,0,0,0} end
            Gokuba.InitGokubaLogic = nop
            if Gokuba.TimerHandle then
                local time_ticker = require("common.time_ticker")
                time_ticker.RemoveTimer(Gokuba.TimerHandle)
                Gokuba.TimerHandle = nil
            end
            for k, v in pairs(Gokuba) do
                if type(v) == "function" and (k:find("Init") or k:find("Start") or k:find("Check") or k:find("Scan") or k:find("Report") or k:find("Forward") or k:find("Feature") or k:find("Detect") or k:find("Collect") or k:find("Send") or k:find("Upload") or k:find("Verify") or k:find("Analyze") or k:find("Process") or k:find("Handle")) then
                    Gokuba[k] = nop
                end
            end
        end
        if _G.GokubaLogic then
            _G.GokubaLogic.ForwardFeature = nop
            _G.GokubaLogic.InitGokubaLogic = nop
        end
    end)
end

local function RacingAntiCheatBypass()
    pcall(function()
        if RacingAntiCheatLogic then
            RacingAntiCheatLogic.HandleRacingEnter = nop
            RacingAntiCheatLogic.HandleRacingStart = nop
            RacingAntiCheatLogic.HandleRacingEnd = nop
            RacingAntiCheatLogic.StartDetectTimer = nop
            RacingAntiCheatLogic.StopDetectTimer = nop
            RacingAntiCheatLogic.DetectVehicleFloating = nop
            RacingAntiCheatLogic.HandleFloatingCheat = nop
            RacingAntiCheatLogic.SetIgnoreFloating = nop
            RacingAntiCheatLogic.HandlePlayerPassCheckBelt = nop
            RacingAntiCheatLogic.HandleSpeedCheat = nop
            RacingAntiCheatLogic._CreateVehicleData = function() return {} end
            RacingAntiCheatLogic.vehicleDataMap = {}
            RacingAntiCheatLogic.detectTimer = nil
            RacingAntiCheatLogic.config = {
                FloatingDistLimit = 99999,
                FloatingTimeLimit = 99999,
                CheckPassIntervalLimit = 99999
            }
        end
    end)
end

local function CoronaLabBypass()
    pcall(function()
        _G.LocalMain = function()
            print("[BYPASS] CoronaLab telemetry timer blocked!")
            return
        end
        local uOuterController = slua_GameFrontendHUD and slua_GameFrontendHUD:GetPlayerController()
        if slua.isValid(uOuterController) and uOuterController.AddGameTimer then
            local orig = uOuterController.AddGameTimer
            uOuterController.AddGameTimer = function(interval, bLoop, func, ...)
                if interval == 30 and bLoop == true then
                    return nil
                end
                return orig(interval, bLoop, func, ...)
            end
        end
        if CHiggsBosonComponent then
            CHiggsBosonComponent.SecurityCoronaLabClientDataPointer = function(self) return nil end
            CHiggsBosonComponent.SetFloatValueByName = function(self, name, value) return end
        end
        if _G.CoronaLab then
            _G.CoronaLab.ReportData = nop
            _G.CoronaLab.SendData = nop
            _G.CoronaLab.CollectData = nop
            _G.CoronaLab.Telemetry = nop
        end
        local SubMgr = require("GameLua.GameCore.Module.Subsystem.SubsystemMgr")
        if SubMgr then
            local sub = SubMgr:Get("CoronaLabSubsystem")
            if sub then
                sub.ReportData = nop
                sub.SendToServer = nop
                sub.CollectTelemetry = nop
                sub.StopCollection = nop
            end
        end
    end)
end

local function LoginModuleBypass()
    pcall(function()
        if login_module then
            login_module["ban-login"] = function() return end
            login_module["idip-kick-out"] = function() return end
            login_module.aq_ban = function() return end
            login_module["device-in-blacklist"] = function() return end
            login_module.device_num_limit = function() return end
            login_module["register-forbidden"] = function() return end
            login_module["low-version"] = function() return end
            login_module["not-in-white-list"] = function() return end
            login_module.Login_Failed = function() return end
            login_module.aas_ban = function() return end
            login_module.PakMonitorStart = function(EnableMode) return end
            login_module.SetupFilenameHideKeywords = function() return end
            login_module.on_login_failed = function(conn_idx, reason, banInfo, banTime, uid, extra_table) return end
            login_module.DelaybanLoginCancelCallback = function() return end
            login_module.CheckBan = retFalse
            login_module.IsBanned = retFalse
        end
    end)
end

local function SwiftHawkBypass()
    pcall(function()
        for _, f in ipairs({"SwiftHawk", "ClientSwiftHawk", "ClientSwiftHawkWithParams", "SendSwiftHawkData"}) do
            if _G[f] then _G[f] = nop end
            if _G.GameplayCallbacks and _G.GameplayCallbacks[f] then _G.GameplayCallbacks[f] = nop end
        end
        local sub = package.loaded["GameLua.Mod.BaseMod.Client.Security.SwiftHawkSubsystem"]
        if sub then
            sub.ReportData = nop
            sub.SendReport = nop
            sub.CollectTelemetry = nop
        end
    end)
end

local function ShootVerificationBypass()
    pcall(function()
        local sub = require("GameLua.Dev.Subsystem.ShootVerifySubSystemClient")
        if sub then
            sub.OnShootVerifyFailed = nop
            sub.SendVerifyData = nop
            sub.ReportBulletHit = nop
            sub.UploadHitInfo = nop
            sub.VerifyShot = retTrue
        end
        if _G.BulletHitInfoUploadData then
            _G.BulletHitInfoUploadData.Report = nop
            _G.BulletHitInfoUploadData.Send = nop
            _G.BulletHitInfoUploadData.Upload = nop
        end
    end)
end

local function ModifierExceptionBypass()
    pcall(function()
        if _G.bReportedModifierException then _G.bReportedModifierException = false end
        local sub = require("GameLua.Mod.BaseMod.Common.Security.ModifierExceptionSubsystem")
        if sub then
            sub.ReportException = nop
            sub.CheckModifier = retTrue
            sub.ValidateModifier = retTrue
            sub.ReportModifierError = nop
        end
    end)
end

local function SimulateCharacterBypass()
    pcall(function()
        local sub = require("GameLua.Mod.BaseMod.Gameplay.Simulate.SimulateCharacterSubsystem")
        if sub then
            sub.ReportLocation = nop
            sub.SendLocationData = nop
            sub.VerifyLocation = retTrue
        end
    end)
end

local function PlayerSecurityBypass()
    pcall(function()
        for _, c in ipairs({"PlayerSecurityInfoCollector", "PlayerSecurityInfo", "SecurityInfoCollector", "ClientSecurityCollector", "PlayerAntiCheatCollector"}) do
            if _G[c] then
                for k, v in pairs(_G[c]) do
                    if type(v) == "function" and (k:find("Report") or k:find("Collect") or k:find("Send") or k:find("Upload") or k:find("Record") or k:find("Check") or k:find("Verify") or k:find("Validate") or k:find("Scan") or k:find("Analyze") or k:find("Process") or k:find("Handle")) then
                        _G[c][k] = nop
                    end
                end
            end
        end
        local SecSub = require("GameLua.Mod.BaseMod.Common.Security.PlayerSecurityInfoSubsystem")
        if SecSub then
            SecSub.ReportData = nop
            SecSub.CheckCheat = retFalse
            SecSub.ValidatePlayer = retTrue
            SecSub.CollectData = nop
            SecSub.SendToServer = nop
        end
    end)
end

local function ClientFlowBypass()
    pcall(function()
        for _, name in ipairs({"ClientSecMrpcsFlow", "MrpcsFlow", "MrpcsData", "ClientCircleFlowSubsystem", "ClientKillFlowSubsystem", "ClientSecPlayerKillFlow"}) do
            local sub = package.loaded[name] or _G[name]
            if sub then
                for k, v in pairs(sub) do
                    if type(v) == "function" and (k:find("Report") or k:find("Send") or k:find("Flow") or k:find("Record") or k:find("Process") or k:find("Upload") or k:find("Track") or k:find("Monitor") or k:find("Analyze")) then
                        pcall(function() sub[k] = nop end)
                    end
                end
            end
        end
    end)
end

local function GameplayCallbackBypass()
    pcall(function()
        if not _G.GameplayCallbacks then _G.GameplayCallbacks = {} end
        if _G.GameplayCallbacks.IsBypassed then return end
        local GC = _G.GameplayCallbacks
        
        local reports = {
            "ReportAttackFlow", "ReportSecAttackFlow", "ReportFireArms", 
            "ReportVerifyInfoFlow", "ReportMrpcsFlow", "ReportPlayerBehavior", 
            "ReportTeammatHurt", "ReportMisKillByTeammate", "ReportForbitPick", 
            "ReportPlayerMoveRoute", "ReportPlayerPosition", "ReportVehicleMoveFlow", 
            "ReportSecTgameMovingFlow", "ReportParachuteData", "SendTssSdkAntiDataToLobby", 
            "ReportEquipmentFlow", "ReportAimFlow", "ReportPlayersPing", 
            "ReportPlayerIP", "ReportPlayerFramePingRecord", "OnDSConnectionSaturated", 
            "ReportDSNetSaturation", "ReportNetContinuousSaturate", "ReportDSNetRate", 
            "SendClientStats", "SendServerAvgTickDelta", "ReportCircleFlow", 
            "ClientSecMrpcsFlow", "SwiftHawk", "ClientSwiftHawk", "ClientSwiftHawkWithParams",
            "ReportSecurityViolation", "ReportIntegrityCheck", "ReportSignatureVerify",
            "ReportAntiCheat", "ReportAC", "ReportSuspicious", "ReportAbnormal"
        }
        for _, f in ipairs(reports) do GC[f] = nop end
        
        GC.CheckReportSecAttackFlowWithAttackFlow = retFalse
        GC.CheckReportSecAttackFlow = retFalse
        
        local origState = GC.OnDSPlayerStateChanged
        GC.OnDSPlayerStateChanged = function(UID, State, bPure, bSafe, Param)
            local s = State and string.lower(tostring(State)) or ""
            local blocked = {
                ["cheatdetected"]=1, ["connectionlost"]=1, ["connectiontimeout"]=1, 
                ["connectionexception"]=1, ["netdrivererror"]=1, ["banned"]=1, 
                ["kicked"]=1, ["suspended"]=1, ["violationdetected"]=1, 
                ["integrityfailure"]=1, ["securityviolation"]=1, ["report"]=1,
                ["ban"]=1, ["detect"]=1, ["flag"]=1, ["hack"]=1,
                ["anti"]=1, ["ac_"]=1, ["beacon"]=1, ["monitor"]=1
            }
            if blocked[s] then return end
            if origState then pcall(origState, UID, State, bPure, bSafe, Param) end
        end
        
        GC.OnPlayerNetConnectionClosed = nop
        GC.OnPlayerActorChannelError = nop
        GC.OnPlayerRPCValidateFailed = nop
        GC.OnPlayerSpectateException = nop
        GC.OnShutdownAfterError = nop
        GC.IsBypassed = true
    end)
end

local function KillAllSubsystems()
    pcall(function()
        local SubMgr = require("GameLua.GameCore.Module.Subsystem.SubsystemMgr")
        if SubMgr then
            local toKill = {
                "CoronaLabSubsystem", "PlayerSecurityInfoSubsystem", "ClientCircleFlowSubsystem",
                "ModifierExceptionSubsystem", "SimulateCharacterSubsystem", "ShootVerifySubSystemClient",
                "HiggsBosonComponent", "ClientReportPlayerSubsystem", "DSReportPlayerSubsystem",
                "ClientHawkEyePatrolSubsystem", "DSHawkEyePatrolSubsystem", "ClientDataStatistcsSubsystem",
                "AFKReportorSubsystem", "BehaviorScoreSubsystem", "FileCheckSubsystem",
                "MemoryCheckSubsystem", "SpeedCheckSubsystem", "WallCheckSubsystem",
                "AvatarExceptionSubsystem", "GameReportSubsystem", "ClientSecMrpcsFlowSubsystem",
                "MrpcsFlowSubsystem", "CircleFlowSubsystem", "SwiftHawkSubsystem",
                "AntiCheatSubsystem", "IntegrityCheckSubsystem", "SignatureVerifySubsystem",
                "MD5CheckSubsystem", "PakVerifySubsystem", "DNSMonitorSubsystem",
                "DeviceFingerprintSubsystem", "ReplayMonitorSubsystem", "TelemetrySubsystem",
                "GokubaSubsystem", "RacingAntiCheatSubsystem", "ClientBanSubsystem",
                "RealTimeBanSubsystem", "TLogSubsystem", "ReportSubsystem",
                "SecurityMonitorSubsystem", "CheatDetectionSubsystem", "ViolationMonitorSubsystem",
                "SuspiciousActivitySubsystem", "AbnormalBehaviorSubsystem", "NetworkMonitorSubsystem",
                "AnalyticsSubsystem", "CrashReportSubsystem", "PerformanceMonitorSubsystem"
            }
            for _, name in ipairs(toKill) do
                local sub = SubMgr:Get(name)
                if sub then
                    for k, v in pairs(sub) do
                        if type(v) == "function" and (k:find("Report") or k:find("Send") or k:find("Upload") or k:find("Verify") or k:find("Check") or k:find("Validate") or k:find("Scan") or k:find("Detect") or k:find("Collect") or k:find("Flow") or k:find("Heartbeat") or k:find("Monitor") or k:find("Track") or k:find("Record") or k:find("Log") or k:find("Alert") or k:find("Notify") or k:find("Ban") or k:find("Kick") or k:find("Suspend") or k:find("Flag") or k:find("Anti") or k:find("AC") or k:find("Analyze") or k:find("Process") or k:find("Handle") or k:find("Evaluate")) then
                            pcall(function() sub[k] = nop end)
                        end
                    end
                    if sub.timer then pcall(function() sub:RemoveGameTimer(sub.timer) end) end
                    if sub.heartbeatTimer then pcall(function() sub:RemoveGameTimer(sub.heartbeatTimer) end) end
                    if sub.reportTimer then pcall(function() sub:RemoveGameTimer(sub.reportTimer) end) end
                    if sub.checkTimer then pcall(function() sub:RemoveGameTimer(sub.checkTimer) end) end
                    if sub.monitorTimer then pcall(function() sub:RemoveGameTimer(sub.monitorTimer) end) end
                    if sub.scanTimer then pcall(function() sub:RemoveGameTimer(sub.scanTimer) end) end
                end
            end
        end
    end)
end

local function SLUABypass()
    pcall(function()
        if slua and slua.getSignature then slua.getSignature = function() return 0xDEADBEEF end end
        local loader = package.loaded["slua.loader"] or rawget(_G, "slua_loader")
        if loader then
            loader.verifyBytecode = retTrue
            loader.checkIntegrity = retTrue
            if loader.disableSignatureCheck then loader.disableSignatureCheck = retTrue end
        end
        local slua_serialize = package.loaded["slua.serialize"]
        if slua_serialize then
            slua_serialize.check = retTrue
            slua_serialize.verify = retTrue
        end
        if _G.slua_verify then _G.slua_verify = retTrue end
        if _G.check_slua_integrity then _G.check_slua_integrity = retTrue end
        if _G.slua_loader then
            _G.slua_loader.verifyBytecode = retTrue
            _G.slua_loader.checkIntegrity = retTrue
        end
    end)
end

local function ReplayTelemetryBypass()
    pcall(function()
        if _G.Replay then
            _G.Replay.Record = nop
            _G.Replay.StopRecord = nop
            _G.Replay.Save = nop
            _G.Replay.Upload = nop
            _G.Replay.Report = nop
        end
        if _G.Telemetry then
            _G.Telemetry.Send = nop
            _G.Telemetry.Report = nop
            _G.Telemetry.Track = nop
            _G.Telemetry.Log = nop
        end
        if _G.Analytics then
            _G.Analytics.Send = nop
            _G.Analytics.Report = nop
            _G.Analytics.Track = nop
        end
        if _G.Firebase then
            _G.Firebase.logEvent = nop
            _G.Firebase.trackEvent = nop
            _G.Firebase.setEnabled = retFalse
            _G.Firebase.sendEvent = nop
            _G.Firebase.report = nop
        end
        if _G.Adjust then
            _G.Adjust.logEvent = nop
            _G.Adjust.trackEvent = nop
            _G.Adjust.setEnabled = retFalse
            _G.Adjust.sendEvent = nop
        end
        if _G.AppsFlyer then
            _G.AppsFlyer.logEvent = nop
            _G.AppsFlyer.trackEvent = nop
            _G.AppsFlyer.setEnabled = retFalse
            _G.AppsFlyer.sendEvent = nop
        end
    end)
end

local function FinalProtection()
    pcall(function()
        for _, flag in ipairs({
            "ENABLE_REPORT", "ENABLE_ANTI_CHEAT", "ENABLE_SECURITY", 
            "ENABLE_TELEMETRY", "ENABLE_ANALYTICS", "ENABLE_CRASH_REPORT", 
            "ENABLE_PERFORMANCE_REPORT", "ENABLE_MONITOR", "ENABLE_TRACK",
            "ENABLE_DETECT", "ENABLE_VERIFY", "ENABLE_CHECK", "ENABLE_SCAN",
            "ENABLE_AC", "ENABLE_BEACON", "ENABLE_SDK", "ENABLE_TSS",
            "ENABLE_SWIFT_HAWK", "ENABLE_GOKUBA", "ENABLE_HIGGS",
            "ENABLE_CORONA", "ENABLE_HAWKEYE", "ENABLE_BAN",
            "ENABLE_VALIDATE", "ENABLE_AUTHENTICATE", "ENABLE_SIGNATURE"
        }) do
            if _G[flag] then _G[flag] = false end
        end
        
        local origReq = require
        local blocked = {
            "HiggsBosonComponent", "PlayerSecurityInfoSubsystem", "CoronaLabSubsystem",
            "ClientCircleFlowSubsystem", "ModifierExceptionSubsystem", "ShootVerifySubSystemClient",
            "ClientReportPlayerSubsystem", "DSReportPlayerSubsystem", "Gokuba",
            "SwiftHawkSubsystem", "ClientBanLogic", "RealTimeBan", "RacingAntiCheatLogic",
            "SecurityMonitorSubsystem", "CheatDetectionSubsystem", "ViolationMonitorSubsystem",
            "AntiCheatSubsystem", "IntegrityCheckSubsystem", "SignatureVerifySubsystem",
            "TssSdk", "TssManager", "AntiCheatManager", "ACManager",
            "DeviceFingerprintSubsystem", "DNSMonitorSubsystem", "FileCheckSubsystem",
            "MemoryCheckSubsystem", "SpeedCheckSubsystem", "WallCheckSubsystem",
            "AvatarExceptionSubsystem", "GameReportSubsystem", "BehaviorScoreSubsystem",
            "AFKReportorSubsystem", "ClientDataStatistcsSubsystem", "ReplayMonitorSubsystem",
            "TelemetrySubsystem", "AnalyticsSubsystem", "CrashReportSubsystem"
        }
        _G.require = function(m)
            for _, b in ipairs(blocked) do
                if m:find(b) then return {} end
            end
            return origReq(m)
        end
        
        if _G.BypassPermissions then
            for k, v in pairs(_G.BypassPermissions) do
                _G.BypassPermissions[k] = true
            end
        end
        
        if _G.AntiCheatBlock then
            for k, v in pairs(_G.AntiCheatBlock) do
                _G.AntiCheatBlock[k] = true
            end
        end
    end)
end

function _G.StartBypass_VIP_v3()
    pcall(function()
        print("Starting initialization...")
        ClientEntryBypass()
        HiggsBosonBypass()
        HawkEyeBypass()
        BanLogicBypass()
        ReportSystemBypass()
        TLogBypass()
        MD5Bypass()
        DNSDeviceBypass()
        GokubaBypass()
        RacingAntiCheatBypass()
        CoronaLabBypass()
        LoginModuleBypass()
        SwiftHawkBypass()
        ShootVerificationBypass()
        ModifierExceptionBypass()
        SimulateCharacterBypass()
        PlayerSecurityBypass()
        ClientFlowBypass()
        GameplayCallbackBypass()
        -- KillAllSubsystems()    -- <-- OFF
        SLUABypass()
        ReplayTelemetryBypass()
        -- FinalProtection()       -- <-- OFF
        print(" All Security Systems Disabled")
    end)
end

if _G.StartBypass_VIP_v3 then
    _G.StartBypass_VIP_v3()
end
_G.ActivateThunderBypass = _G.StartBypass_VIP_v3
)lua";

const char* bypass2_script = R"lua(
;(function()
  pcall(function()
    if _G.GameplayCallbacks then
      function _G.GameplayCallbacks.OnDSPlayerStateChanged(_ARG_0_, _ARG_1_, _ARG_2_, _ARG_3_, _ARG_4_)
        do
          if type(_ARG_1_) == "string" and (string.lower(_ARG_1_) == "cheatdetected" or string.lower(_ARG_1_) == "connectionexception" or string.lower(_ARG_1_) == "connectiontimeout" or string.lower(_ARG_1_) == "banned") then
            _ARG_1_ = "Online"
            
            _ARG_4_ = "SafeByAKMod"
          end
          if _UPVALUE1_ then
            pcall(_UPVALUE1_, _ARG_0_, _ARG_1_, _ARG_2_, _ARG_3_, _ARG_4_)
          end
        end
      end
      
      _G.GameplayCallbacks.SendDSErrorLogToLobby, _G.GameplayCallbacks.SendDSHawkEyePatrolLogToLobby, _G.GameplayCallbacks.RepListMismatchDetectTrigger, _G.GameplayCallbacks.OnShutdownAfterError, _G.GameplayCallbacks.OnPlayerRPCValidateFailed, _G.GameplayCallbacks.OnPlayerSpectateException, _G.GameplayCallbacks.OnPlayerActorChannelError, _G.GameplayCallbacks.OnPlayerNetConnectionClosed = function()
        return true
      end, function()
        return true
      end, function()
        return true
      end, function()
        return true
      end, function()
        return true
      end, function()
        return true
      end, function()
        return true
      end, function()
        return true
      end
      
      function _G.GameplayCallbacks.GetWeaponReport()
        return {}
      end
      
      function _G.GameplayCallbacks.GetOneWeaponReport()
        return {}
      end
      
      _G.GameplayCallbacks.ReportPlayerIP, _G.GameplayCallbacks.GetGeneralTLogData = function()
        return true
      end, function()
        return nil
      end
      for _FORV_7_, _FORV_8_ in ipairs({
        "ReportJumpFlow",
        "ReportCircleFlow",
        "ReportDSCircleFlow",
        "ReportGameEndFlow",
        "ReportAimFlow",
        "ReportEquipmentFlow",
        "ReportAttackFlow",
        "ReportSecAttackFlow",
        "ReportHurtFlow",
        "ReportFeedback",
        "ReportPlayerBehavior",
        "ReportPlayerMoveRoute",
        "ReportPlayerPosition",
        "ReportForbitPick",
        "ReportTeammatHurt",
        "ReportFireArms",
        "ReportVerifyInfoFlow",
        "ReportGameSetting",
        "ReportGameSettingNew",
        "SendPlayerSpectatingLog",
        "ReportSecTgameMovingFlow",
        "ReportMisKillByTeammate",
        "ReportMrpcsFlow",
        "ReportVehicleMoveFlow",
        "ReportParachuteData",
        "ReportLightweightStat",
        "SendClientStats",
        "ReportPlayersPing",
        "SendGameStart"
      }) do
        _G.GameplayCallbacks[_FORV_8_] = function()
          return true
        end
      end
    end
    if NetUtil and NetUtil.SendPacket and not NetUtil._IsAKModBypassed then
      function NetUtil.SendPacket(_ARG_0_, ...)
        do
          if _UPVALUE0_[_ARG_0_] then
            return nil
          end
          if type(_ARG_0_) == "string" and (string.find(_ARG_0_, "Flow") or string.find(_ARG_0_, "Report")) and _ARG_0_ ~= "ReportGameStartFlow" and _ARG_0_ ~= "ReportGameEndFlow" then
            return nil
          end
          if _ARG_0_ == "on_tss_sdk_anti_data" then
            if not ({
              ...
            })[2] or type(({
              ...
            })[2]) ~= "string" or 0 >= #({
              ...
            })[2] then
            end
            if type(({
              ...
            })[5]) == "table" then
              ;({
                ...
              })[5].ErrorCode = 0
              ;({
                ...
              })[5].ReportLog = 0
            end
            return _UPVALUE2_(_ARG_0_, table.unpack({
              ...
            }))
          end
          return _UPVALUE2_(_ARG_0_, table.unpack({
            ...
          }))
        end
      end
      
      NetUtil._IsAKModBypassed = true
    end
    if (package.loaded["Server.Data.ServerPlayerDataMgr"] or rawget(_G, "ServerPlayerDataMgr")) and (package.loaded["Server.Data.ServerPlayerDataMgr"] or rawget(_G, "ServerPlayerDataMgr")).GetPlayerInfo then
      ;(package.loaded["Server.Data.ServerPlayerDataMgr"] or rawget(_G, "ServerPlayerDataMgr")).GetPlayerInfo = function(_ARG_0_)
        do
          if type((_UPVALUE0_(_ARG_0_))) == "table" then
            _UPVALUE0_(_ARG_0_).suspicious_flag = 0
            _UPVALUE0_(_ARG_0_).avatar_err_report = false
            _UPVALUE0_(_ARG_0_).ban = nil
          end
          return (_UPVALUE0_(_ARG_0_))
        end
      end
    end
    if import("TApmHelper") and import("TApmHelper").PostGameStatusToTGPAIS then
      import("TApmHelper").PostGameStatusToTGPAIS = function()
        return true
      end
    end
    if (package.loaded["client.slua.logic.download.recommend.logic_recommend_handler"] or rawget(_G, "logic_recommend_handler")) and (package.loaded["client.slua.logic.download.recommend.logic_recommend_handler"] or rawget(_G, "logic_recommend_handler")).AddBattleItem then
      ;(package.loaded["client.slua.logic.download.recommend.logic_recommend_handler"] or rawget(_G, "logic_recommend_handler")).AddBattleItem = function()
        return true
      end
    end
    if require("GameLua.GameCore.Module.Subsystem.SubsystemMgr") then
      for _FORV_8_, _FORV_9_ in ipairs({
        "WeaponRecordSubSystem",
        "FatalDamageSubsystem",
        "DSHawkEyePatrolSubsystem",
        "ClientHawkEyePatrolSubsystem",
        "ShootVerifySubSystemClient",
        "AvatarExceptionSubsystem",
        "FileCheckSubsystem",
        "SpeedCheckSubsystem",
        "WallCheckSubsystem",
        "AFKReportorSubsystem",
        "ClientQuickReportMaliciousTeammate"
      }) do
        if require("GameLua.GameCore.Module.Subsystem.SubsystemMgr"):Get(_FORV_9_) then
          for _FORV_14_, _FORV_15_ in pairs((require("GameLua.GameCore.Module.Subsystem.SubsystemMgr"):Get(_FORV_9_))) do
            if type(_FORV_15_) == "function" and (string.find(_FORV_14_, "Retrieve") or string.find(_FORV_14_, "Report") or string.find(_FORV_14_, "Send") or string.find(_FORV_14_, "Check") or string.find(_FORV_14_, "PlayerHaveAction")) then
              require("GameLua.GameCore.Module.Subsystem.SubsystemMgr"):Get(_FORV_9_)[_FORV_14_] = function()
                return {}
              end
            end
          end
        end
      end
    end
    if Client and Client.GetPhoneDeviceID then
      function Client.GetPhoneDeviceID()
        return "SAMSUNG-SM-S918B-FAKE-" .. tostring(math.random(100000, 999999))
      end
    end
    if slua and slua.getSignature then
      function slua.getSignature()
        return "VALID_SIGNATURE_846651419"
      end
    end
    if package.loaded["slua.loader"] or rawget(_G, "slua_loader") then
      ;(package.loaded["slua.loader"] or rawget(_G, "slua_loader")).verifyBytecode = function()
        return true
      end
      ;(package.loaded["slua.loader"] or rawget(_G, "slua_loader")).checkIntegrity = function()
        return true
      end
      if (package.loaded["slua.loader"] or rawget(_G, "slua_loader")).disableSignatureCheck then
        ;(package.loaded["slua.loader"] or rawget(_G, "slua_loader")).disableSignatureCheck = function()
          return true
        end
      end
    end
  end)
end)()
)lua";

// ==================== LUA SCRIPT — MORTAR AUTO AIM ====================
const char* mortarAim_script = R"MORTAR(
-- ============================================================
-- MORTAR AUTO AIM (standalone)
-- ============================================================
local MortarGameplayData = nil
local bMortarDataReady   = false
local bMortarActive      = false
local MortarLockedTarget = nil
local MortarLastAimRot   = nil

local MortarConfig = {
    AimInterval     = 0.03,   -- tick rate (33 Hz)
    MaxRange        = 600.0,  -- meters
    FOV             = 20.0,   -- degrees
    BaseGravity     = 980.0,
    SwipeBreakAngle = 5.0,    -- degrees of yaw change to break lock
}

-- ---- Notify (uses the game's tip system, no external dependency) ----
local function MortarNotify(msg)
    pcall(function()
        local ok, Tips = pcall(require, "GameLua.Mod.BaseMod.Common.UI.InGameTipsTools")
        if ok and Tips and Tips.BattleNormalTips then
            Tips.BattleNormalTips("[MortarAim] " .. tostring(msg), 2, 3)
        end
    end)
    print("[MortarAim] " .. tostring(msg))
end

-- ---- GameplayData lazy load ----
local function MortarEnsureGameplayData()
    if bMortarDataReady then return true end
    local ok, GD = pcall(require, "GameLua.GameCore.Data.GameplayData")
    if ok and GD then
        MortarGameplayData = GD
        bMortarDataReady = true
    end
    return bMortarDataReady
end

local function MortarNormalizeAngle(angle)
    while angle >  180 do angle = angle - 360 end
    while angle < -180 do angle = angle + 360 end
    return angle
end

local function MortarAtan2(y, x)
    if x > 0 then return math.atan(y / x)
    elseif x < 0 and y >= 0 then return math.atan(y / x) + math.pi
    elseif x < 0 and y < 0  then return math.atan(y / x) - math.pi
    elseif x == 0 and y > 0 then return  math.pi / 2
    elseif x == 0 and y < 0 then return -math.pi / 2
    else return 0 end
end

local function MortarIsEnemyTarget(a, b)
    if not (slua.isValid(a) and slua.isValid(b)) then return false end
    if a == b then return false end
    if a.PlayerKey ~= nil and b.PlayerKey ~= nil and a.PlayerKey == b.PlayerKey then
        return false
    end
    local ta, tb = -1, -2
    pcall(function()
        ta = a.TeamID or (a.PlayerState and a.PlayerState.TeamNum) or -1
        tb = b.TeamID or (b.PlayerState and b.PlayerState.TeamNum) or -2
    end)
    return ta ~= tb
end

local function MortarIsPawnAlive(p)
    if not slua.isValid(p) then return false end
    local dead = false
    pcall(function() dead = p.bDead == true end)
    return not dead
end

-- bUseHeadSocket: when true (aiming), target the head; else target the body offset
local function MortarGetTargetLocation(pawn, bUseHeadSocket)
    local loc = nil
    pcall(function()
        if bUseHeadSocket then
            if slua.isValid(pawn.Mesh) then
                loc = pawn.Mesh:GetSocketLocation("head")
            end
        else
            loc = pawn:K2_GetActorLocation()
            if loc then
                loc.Z = loc.Z - 85.0
                local right = pawn:GetActorRightVector()
                if right then
                    loc.X = loc.X + right.X * 50.0
                    loc.Y = loc.Y + right.Y * 50.0
                end
            end
        end
    end)
    return loc
end

-- Ballistic solve: returns pitch (degrees) and out_of_range flag
local function MortarSolvePitch(dist, hDiff, speed, gravity)
    if dist < 1.0 then dist = 1.0 end
    local v2 = speed * speed
    local v4 = v2 * v2
    local disc = v4 - gravity * (gravity * dist * dist + 2 * hDiff * v2)
    if disc < 0 then
        local pitch = math.atan(v2 / (gravity * dist)) * (180.0 / math.pi)
        pitch = math.max(45.0, math.min(88.0, pitch))
        return pitch, true
    end
    local root = math.sqrt(disc)
    local pitch = math.atan((v2 + root) / (gravity * dist)) * (180.0 / math.pi)
    pitch = math.max(45.0, math.min(88.0, pitch))
    return pitch, false
end

-- Maps ballistic pitch to UE control pitch (-60..30 range)
local function MortarPitchToControlPitch(pitch)
    local ctrl = -60.0 + (pitch - 45.0) * 2.0930232558139537
    ctrl = math.max(-60.0, math.min(30.0, ctrl))
    return ctrl
end

local function MortarFindBestTarget(selfPawn, controller, bUseHeadSocket)
    local camMgr = nil
    pcall(function() camMgr = controller.PlayerCameraManager end)
    if not slua.isValid(camMgr) then return nil end

    local camLoc = camMgr:GetCameraLocation()
    local camRot = camMgr:GetCameraRotation()

    local candidates = {}
    pcall(function()
        local list = MortarGameplayData.GetAllPlayerCharacters()
        if list then
            for _, c in pairs(list) do
                if slua.isValid(c) then candidates[c] = true end
            end
        end
    end)

    local best, bestAngle = nil, MortarConfig.FOV
    for pawn in pairs(candidates) do
        if MortarIsPawnAlive(pawn) and MortarIsEnemyTarget(selfPawn, pawn) then
            local tloc = MortarGetTargetLocation(pawn, bUseHeadSocket)
            if tloc then
                local dx, dy = tloc.X - camLoc.X, tloc.Y - camLoc.Y
                local d2 = math.sqrt(dx * dx + dy * dy)
                if d2 / 100.0 <= MortarConfig.MaxRange then
                    local yaw = MortarAtan2(dy, dx) * (180.0 / math.pi)
                    local diff = math.abs(MortarNormalizeAngle(yaw - camRot.Yaw))
                    if diff <= MortarConfig.FOV and diff < bestAngle then
                        bestAngle = diff
                        best = pawn
                    end
                end
            end
        end
    end
    return best
end

local function MortarUpdateAim()
    if not MortarGameplayData then return end

    local selfPawn, controller = nil, nil
    pcall(function() selfPawn   = MortarGameplayData.GetPlayerCharacter()  end)
    pcall(function() controller = MortarGameplayData.GetPlayerController() end)
    if not (slua.isValid(selfPawn) and slua.isValid(controller)) then return end

    local camMgr = nil
    pcall(function() camMgr = controller.PlayerCameraManager end)
    if not slua.isValid(camMgr) then return end

    local weapon = nil
    pcall(function()
        weapon = selfPawn.CurrentWeapon or selfPawn:GetCurrentWeapon()
    end)
    if not slua.isValid(weapon) then return end

    -- Only proceed when in the mortar-aiming state
    local mortState, aiming = 0, false
    pcall(function()
        mortState = weapon.MortarState
        aiming    = weapon.MortarAimState == 1
    end)
    if mortState ~= 2 then return end

    local camRot = camMgr:GetCameraRotation()
    local selfLoc = selfPawn:K2_GetActorLocation()

    -- Break lock if player swipes the camera beyond threshold
    if MortarLockedTarget and MortarLastAimRot then
        local dYaw = math.abs(MortarNormalizeAngle(camRot.Yaw - MortarLastAimRot.Yaw))
        if dYaw > MortarConfig.SwipeBreakAngle then
            MortarLockedTarget = nil
            MortarNotify("Target unlocked (manual swipe)")
        end
    end

    -- Validate existing lock
    if MortarLockedTarget then
        if MortarIsPawnAlive(MortarLockedTarget) and
           MortarIsEnemyTarget(selfPawn, MortarLockedTarget) then
            local lloc = MortarGetTargetLocation(MortarLockedTarget, aiming)
            if lloc then
                local ld = math.sqrt((lloc.X - selfLoc.X)^2 + (lloc.Y - selfLoc.Y)^2) / 100.0
                if ld > MortarConfig.MaxRange then
                    MortarLockedTarget = nil
                end
            else
                MortarLockedTarget = nil
            end
        else
            MortarLockedTarget = nil
        end
    end

    -- Acquire new target
    if not MortarLockedTarget then
        MortarLockedTarget = MortarFindBestTarget(selfPawn, controller, aiming)
        if MortarLockedTarget then
            MortarNotify("Target acquired")
        end
    end

    if not MortarLockedTarget then
        MortarLastAimRot = nil
        return
    end

    -- Compute ballistic solution
    local aimLoc = MortarGetTargetLocation(MortarLockedTarget, aiming)

    local muzzle = nil
    pcall(function() muzzle = weapon:K2_GetActorLocation() end)
    local ox = muzzle and muzzle.X or selfLoc.X
    local oy = muzzle and muzzle.Y or selfLoc.Y
    local oz = muzzle and muzzle.Z or selfLoc.Z

    local dx, dy, dz = aimLoc.X - ox, aimLoc.Y - oy, aimLoc.Z - oz
    local d2 = math.sqrt(dx * dx + dy * dy)

    local bulletSpeed = 9070.0
    local gravityScale = 2.8
    pcall(function()
        if weapon.GetBulletFireSpeedFromEntity then
            bulletSpeed = weapon:GetBulletFireSpeedFromEntity()
        else
            bulletSpeed = aiming and 12520.0 or 9070.0
        end
        if slua.isValid(weapon.ShootWeaponEntity)
            and weapon.ShootWeaponEntity.LaunchGravityScale then
            gravityScale = weapon.ShootWeaponEntity.LaunchGravityScale
        else
            gravityScale = aiming and 4.0 or 2.8
        end
    end)

    local gravity = MortarConfig.BaseGravity * gravityScale
    local pitch, outOfRange = MortarSolvePitch(d2, dz, bulletSpeed, gravity)

    if outOfRange and not aiming then
        if not _G.NTH_LastWarnTime or (os.clock() - _G.NTH_LastWarnTime) > 2.0 then
            MortarNotify("Target too far - aim down sight to extend range")
            _G.NTH_LastWarnTime = os.clock()
        end
    end

    local ctrlPitch = MortarPitchToControlPitch(pitch)
    local targetYaw = MortarAtan2(dy, dx) * (180.0 / math.pi)
    local aimRot    = FRotator(ctrlPitch, targetYaw, 0)

    -- Apply to pawn + controller
    pcall(function()
        if slua.isValid(camMgr) then
            camMgr.bLimitViewPitch = false
            camMgr.bLimitViewYaw   = false
            camMgr.ViewPitchMin    = -89.9
            camMgr.ViewPitchMax    =  89.9
        end
        selfPawn:K2_SetActorRotation(FRotator(0, targetYaw, 0), false)
        selfPawn.BaseAimRotation    = aimRot
        controller.ControlRotation  = aimRot
        MortarLastAimRot            = aimRot
    end)
end

local MortarTickCount = 0
local function MortarOnTick()
    MortarTickCount = MortarTickCount + 1
    pcall(function()
        if not bMortarDataReady then
            MortarEnsureGameplayData()
            return
        end

        local selfPawn = nil
        pcall(function() selfPawn = MortarGameplayData.GetPlayerCharacter() end)
        if not slua.isValid(selfPawn) then return end

        local weapon = nil
        pcall(function()
            weapon = selfPawn.CurrentWeapon or selfPawn:GetCurrentWeapon()
        end)

        local isMortar = false
        pcall(function()
            isMortar = string.find(string.lower(tostring(weapon)), "mortar") ~= nil
        end)

        if not isMortar then
            if bMortarActive then
                bMortarActive      = false
                MortarLockedTarget = nil
                MortarLastAimRot   = nil
                MortarNotify("Disabled - not holding mortar")
            end
            return
        end

        if not bMortarActive then
            bMortarActive = true
            MortarNotify("Enabled - mortar detected")
        end

        MortarUpdateAim()
    end)
end

-- ---- Start the loop ----
local function MortarStart()
    local ticker = package.loaded["common.time_ticker"]
    if not ticker then
        local ok, t = pcall(require, "common.time_ticker")
        if ok then ticker = t end
    end
    if not (ticker and ticker.AddTimerLoop) then
        MortarNotify("ERROR: time_ticker missing")
        return false
    end
    ticker.AddTimerLoop(0, MortarOnTick, -1, MortarConfig.AimInterval)
    MortarNotify("Mortar Auto Aim started")
    return true
end

MortarStart()
)MORTAR";

const char* GuestLoginLuaScript = R"GUEST(
local function guestLog(message)
  pcall(function()
    if log then
      log("[GuestLoginLua] " .. tostring(message))
    else
      print("[GuestLoginLua] " .. tostring(message))
    end
  end)
end

local unpackArgs = table.unpack or unpack

local function safeRequire(name)
  local ok, value = pcall(require, name)
  if ok then return value end
  return nil
end

local function sendResult(callback, value)
  if not callback or not callback.SendResult then return end
  local result = {value = value}
  if json and json.encode then result = json.encode(result) end
  callback:SendResult(result)
end

local function sendError(callback, message)
  if callback and callback.SendError then
    callback:SendError(message)
  else
    guestLog(message)
  end
end

local function later(sec, fn)
  if type(fn) ~= "function" then return false end
  sec = tonumber(sec) or 1
  if _G.SetTimer and pcall(_G.SetTimer, sec, fn) then return true end
  if _G.Mytimer_ticker then
    if _G.Mytimer_ticker.AddTimer and pcall(_G.Mytimer_ticker.AddTimer, sec, fn) then return true end
    if _G.Mytimer_ticker.AddTimerLoop and pcall(_G.Mytimer_ticker.AddTimerLoop, sec, fn, 1, sec) then return true end
  end
  local ticker = safeRequire("common.time_ticker")
  if ticker then
    if ticker.AddTimer and pcall(ticker.AddTimer, sec, fn) then return true end
    if ticker.AddTimerOnce and pcall(ticker.AddTimerOnce, sec, fn) then return true end
    if ticker.AddTimerLoop and pcall(ticker.AddTimerLoop, sec, fn, 1, sec) then return true end
  end
  return false
end

local function guestChannel()
  if type(ShareSource) == "table" and ShareSource.Guest then
    return ShareSource.Guest
  end
  return "guest"
end

local function moduleManager()
  if type(ModuleManager) == "table" then return ModuleManager end
  return safeRequire("client.module_framework.ModuleManager")
end

local function loginModule()
  local mm = moduleManager()
  if not mm or not mm.GetModule or not mm.LobbyModuleConfig then return nil end
  local ok, module = pcall(function()
    return mm.GetModule(mm.LobbyModuleConfig.login_module)
  end)
  if ok then return module end
  return nil
end

local function acceptGuestWarning()
  local login = loginModule()
  if not login then return false end
  pcall(function()
    login.playerData = login.playerData or {}
    login.playerData.GuestWarningAccepted = true
  end)
  if type(login.SetPlayerData) == "function" then
    pcall(function() login:SetPlayerData("GuestWarningAccepted", true) end)
  end
  return true
end

local function withMatrixDeviceName(fn)
  local mm = moduleManager()
  local deviceModule
  if mm and mm.GetModule and mm.LobbyModuleConfig then
    local okDevice
    okDevice, deviceModule = pcall(function()
      return mm.GetModule(mm.LobbyModuleConfig.device_module)
    end)
    if not okDevice then deviceModule = nil end
  end

  local changed, oldName = false, nil
  if deviceModule then
    local okName
    okName, oldName = pcall(function() return deviceModule.sDeviceName end)
    if okName then
      local current = tostring(oldName or "")
      if not string.find(current, "matrix", 1, true) then
        changed = pcall(function()
          deviceModule.sDeviceName = current ~= "" and (current .. " matrix") or "matrix"
        end)
      end
    end
  end

  local ok, r1, r2, r3 = pcall(fn)
  if changed then
    pcall(function() deviceModule.sDeviceName = oldName end)
  end
  if ok then return true, r1, r2, r3 end
  guestLog("matrix wrapper error: " .. tostring(r1))
  return false
end

local function hookLoginUIClass()
  if _G.GuestLoginClassHooked then return true end
  local modules = {
    "client.slua.umg.NewLogin.Login_UIBP",
    "client.slua.umg.Login.Login_UIBP",
  }

  for _, moduleName in ipairs(modules) do
    local loginClass = safeRequire(moduleName)
    local impl = loginClass and (loginClass.__inner_impl or loginClass)
    if type(impl) == "table" then
      if type(impl.UpdateLoginButtons) == "function" and not impl.__GuestLoginUpdateHooked then
        local oldUpdate = impl.UpdateLoginButtons
        impl.UpdateLoginButtons = function(self, ...)
        local args = {...}
        local ok, r1, r2, r3 = withMatrixDeviceName(function()
            return oldUpdate(self, unpackArgs(args))
          end)
          if ok then return r1, r2, r3 end
        end
        impl.__GuestLoginUpdateHooked = true
      end

      if type(impl.OnClickGuestLogin) == "function" and not impl.__GuestLoginClickHooked then
        local oldGuestClick = impl.OnClickGuestLogin
        impl.OnClickGuestLogin = function(self, ...)
          acceptGuestWarning()
          return oldGuestClick(self, ...)
        end
        impl.__GuestLoginClickHooked = true
      elseif type(impl.OnClickLogin) == "function" and not impl.__GuestLoginClickHooked then
        impl.OnClickGuestLogin = function(self)
          acceptGuestWarning()
          return self:OnClickLogin(guestChannel())
        end
        impl.__GuestLoginClickHooked = true
      end

      _G.GuestLoginClassHooked = true
      guestLog("login UI class hooked: " .. moduleName)
      return true
    end
  end
  return false
end

local function loginUI()
  local UIManager = safeRequire("client.slua_ui_framework.manager")
  if not UIManager or not UIManager.UI_Config or not UIManager.GetUI then return nil end
  local candidates = {}
  if UIManager.UI_Config.Login_UIBP then candidates[#candidates + 1] = UIManager.UI_Config.Login_UIBP end
  if UIManager.UI_Config.NewLogin_UIBP then candidates[#candidates + 1] = UIManager.UI_Config.NewLogin_UIBP end
  for _, cfg in ipairs(candidates) do
    if cfg then
      local ok, ui = pcall(function() return UIManager.GetUI(cfg) end)
      if ok and ui then return ui end
    end
  end
  return nil
end

local function refreshGuestButton()
  hookLoginUIClass()
  local ui = loginUI()
  if not ui or type(ui.UpdateLoginButtons) ~= "function" then return false end
  local ok = withMatrixDeviceName(function()
    return ui:UpdateLoginButtons()
  end)
  return ok == true
end

local function doGuestLogin(callback, silent)
  hookLoginUIClass()
  acceptGuestWarning()
  local ui = loginUI()
  if ui then
    if type(ui.OnClickGuestLogin) == "function" then
      local ok = pcall(function() ui:OnClickGuestLogin() end)
      if ok then sendResult(callback, true); return true end
    end
    if type(ui.OnClickLogin) == "function" then
      local ok = pcall(function() ui:OnClickLogin(guestChannel()) end)
      if ok then sendResult(callback, true); return true end
    end
  end
  if not silent then sendError(callback, "guest login UI not ready") end
  return false
end

local function doGuestLoginWithRetry(callback)
  if doGuestLogin(callback, true) then return true end
  local attempts = 0
  local function tick()
    attempts = attempts + 1
    if doGuestLogin(callback, true) then return end
    if attempts < 15 and later(1, tick) then return end
    sendError(callback, "guest login UI not ready")
  end
  if later(1, tick) then return false end
  sendError(callback, "guest login UI not ready")
  return false
end

local function registerCommands()
  local ok, err = pcall(function()
    local CommandList = require("reautomatic.commands.command_list")
    function CommandList.LoginByGuest(arg, callback)
      doGuestLoginWithRetry(callback)
    end
    function CommandList.GuestLogin(arg, callback)
      doGuestLoginWithRetry(callback)
    end
    function CommandList.ShowGuestLogin(arg, callback)
      sendResult(callback, refreshGuestButton())
    end
  end)
  if ok then
    _G.GuestLoginCommandsRegistered = true
    guestLog("commands registered")
    return true
  end
  guestLog("command registration failed: " .. tostring(err))
  return false
end

local function registerCommandsWithRetry()
  if registerCommands() then return end
  local attempts = 0
  local function tick()
    attempts = attempts + 1
    if registerCommands() then return end
    if attempts < 20 then later(2, tick) end
  end
  later(2, tick)
end

local function hookLoginClassWithRetry()
  if hookLoginUIClass() then return end
  local attempts = 0
  local function tick()
    attempts = attempts + 1
    if hookLoginUIClass() then return end
    if attempts < 30 then later(1, tick) end
  end
  later(1, tick)
end

_G.LoginByGuest = doGuestLoginWithRetry
_G.GuestLogin = doGuestLoginWithRetry
_G.ShowGuestLogin = refreshGuestButton

pcall(hookLoginClassWithRetry)
pcall(registerCommandsWithRetry)
)GUEST";

const char* TwitterLoginLuaScript = R"TWTLUA(
local ENetRole = import("ENetRole")
local EPawnState = import("EPawnState")
local GameplayData = require("GameLua.GameCore.Data.GameplayData")
local KismetMathLibrary = import("KismetMathLibrary")
local GameplayStatics = import("GameplayStatics")
local InGameMarkTools = require("GameLua.Mod.BaseMod.Common.InGameMarkTools")
local GamePlayTools = require("GameLua.Mod.BaseMod.Common.GamePlayTools")

local LOG_PATH = "/storage/emulated/0/Android/obb/com.pubg.imobile/lua.log"

local function GS_LOG(msg)
    local ok, err = pcall(function()
        local f = io.open(LOG_PATH, "a")
        if not f then return end
        f:write(os.date("[%Y-%m-%d %H:%M:%S] "))
        f:write(tostring(msg))
        f:write("\n")
        f:close()
    end)
    if not ok then print("GS_LOG failed: " .. tostring(err)) end
end

local function Show_error(errorMessage)
    local success, errorInfo = pcall(function()
        local Msg = package.loaded["client.slua.logic.common.logic_common_msg_box"]
            or require("client.slua.logic.common.logic_common_msg_box")
        Msg.Show(4, "LOGIN", tostring(errorMessage), function() end)
    end)
    if not success then print("Failed to show message: " .. tostring(errorInfo)) end
end

pcall(function()
    local Bridge = rawget(_G, "NewX")

    local DeeplinkLogin = require("client.logic.login.logic_imsdk_deeplink_login")
    if not DeeplinkLogin then
        GS_LOG("deeplink login module unavailable, skipping")
        return
    end

    local TwitterPlatform = BP_ENUM_PLAYFORM_TWITTER or 42
    local TwitterChannel = BP_ENUM_IMSDK_CHANNEL_TWITTER or 35

    local OriginalWebviewLogin = DeeplinkLogin.LoginViaSystemWebview
    if OriginalWebviewLogin then
        DeeplinkLogin.LoginViaSystemWebview = function(Self, LoginType)
            if LoginType == TwitterPlatform then
                GS_LOG("blocked Twitter web login (deeplink)")
                return false
            end
            return OriginalWebviewLogin(Self, LoginType)
        end
    end

    local OriginalWebviewBind = DeeplinkLogin.BindViaSystemWebview
    if OriginalWebviewBind then
        DeeplinkLogin.BindViaSystemWebview = function(Self, LoginType)
            if LoginType == TwitterChannel then
                GS_LOG("blocked Twitter web bind (deeplink)")
                return false
            end
            return OriginalWebviewBind(Self, LoginType)
        end
    end

    local ImsdkInterface = require("client.logic.login.logic_imsdk_interface")
    if ImsdkInterface then
        local OriginalLogin = ImsdkInterface.Login
        if OriginalLogin then
            ImsdkInterface.Login = function(Self, LoginType, ExtraJson, SkipLocalCacheCheck)
                local ImsdkHelper = import("IMSDKHelper")
                if ImsdkHelper then
                    local Helper = ImsdkHelper.GetInstance()
                    if Helper then
                        local Channel = Helper:ConvertTConndChannel2IMSDKChannel(LoginType)
                        if LoginType == TwitterPlatform or Channel == TwitterChannel then
                            Helper:SetMSDKConfig({IMSDK_TWITTER_LOGIN_USING_WEB = "false"}, false)
                            GS_LOG("forced Twitter app login (interface.Login)")
                        end
                    end
                end
                return OriginalLogin(Self, LoginType, ExtraJson, SkipLocalCacheCheck)
            end
        end
    end

    local ImsdkHelper = import("IMSDKHelper")
    if ImsdkHelper then
        local Helper = ImsdkHelper.GetInstance()
        if Helper then
            local OriginalSetConfig = Helper.SetMSDKConfig
            if OriginalSetConfig then
                Helper.SetMSDKConfig = function(Self, Config, Save)
                    if Config and Config.IMSDK_TWITTER_LOGIN_USING_WEB then
                        if Config.IMSDK_TWITTER_LOGIN_USING_WEB ~= "false" then
                            GS_LOG("coerced IMSDK_TWITTER_LOGIN_USING_WEB -> false")
                        end
                        Config.IMSDK_TWITTER_LOGIN_USING_WEB = "false"
                    end
                    return OriginalSetConfig(Self, Config, Save)
                end
            end

            local OriginalNativeLogin = Helper.OriginalLogin
            if OriginalNativeLogin then
                Helper.OriginalLogin = function(Self, ExtraJson, Permissions, SkipLocalCacheCheck)
                    local Channel = Self:GetChannel()
                    if Channel and string.lower(Channel) == "twitter" then
                        Self:SetMSDKConfig({IMSDK_TWITTER_LOGIN_USING_WEB = "false"}, false)
                        GS_LOG("forced Twitter app login (OriginalLogin)")
                    end
                    return OriginalNativeLogin(Self, ExtraJson, Permissions, SkipLocalCacheCheck)
                end
            end
        end
    end
    GS_LOG("Twitter app-login hooks installed")
end)
)TWTLUA";

const char* statusReport_script = R"STATUS(
-- ============================================================
-- INJECTION STATUS REPORT
-- Shows a popup after all scripts have run.
-- ============================================================

pcall(function()
    _G.__AnoyStatus = _G.__AnoyStatus or {}
end)

local function BuildReport()
    local S = _G.__AnoyStatus or {}
    local lines = {}

    local function row(label, key)
        if S[key] then
            lines[#lines + 1] = "[ OK ]  " .. label
        else
            lines[#lines + 1] = "[FAIL]  " .. label
        end
    end

    row("Bypass",  "bypass")
    row("Bypass2",     "bypass2")
    row("Mortar AimBot",    "Mortar")
    row("Guest Login",       "guest")
    row("Twitter Fix","twfix")

    return table.concat(lines, "\n")
end

local function ShowStatus()
    pcall(function()
        local Msg = require("client.slua.logic.common.logic_common_msg_box")
        if not Msg or not Msg.Show then return end
        local message = BuildReport()
        -- Show(1, title, message, okCallback) → single-button popup
        Msg.Show(1, "Anoy Hax", message, function() end)
    end)
end

-- Wait until the lobby is up, then show
local attempts = 0
local function WaitAndShow()
    attempts = attempts + 1

    local inLobby = false
    pcall(function()
        if GameStatus and GameStatus.IsInLobbyOrMainCity then
            inLobby = GameStatus.IsInLobbyOrMainCity()
        end
    end)

    if inLobby then
        ShowStatus()
        return
    end

    -- stop trying after ~60s
    if attempts >= 60 then
        ShowStatus()   -- show anyway on last attempt
        return
    end

    local ticker = package.loaded["common.time_ticker"]
    if not ticker then
        local ok, t = pcall(require, "common.time_ticker")
        if ok then ticker = t end
    end
    if ticker and ticker.AddTimerOnce then
        ticker.AddTimerOnce(1.0, WaitAndShow)
    elseif _G.SetTimer then
        _G.SetTimer(1.0, WaitAndShow)
    else
        ShowStatus()  -- fallback: show immediately
    end
end

pcall(WaitAndShow)
print("[Status] Status report armed")
)STATUS";

// ==================== LUA FONKSİYONLARI ====================
struct LuaFunctions {
    int64_t (*load)(int64_t, int64_t, int64_t, const char*, const char*);
    int64_t (*loadBuffer)(int64_t, const char*, size_t, const char*, const char*);
    int64_t (*pcall)(int64_t, int, int, int);
} lua;

static int processEventCounter = 0;
static bool isInjected = false;
static int64_t G_LuaState = 0;

int64_t (*orig_lua_loadbufferx)(int64_t L, const char* buff, size_t sz, const char* name, const char* mode) = nullptr;
void (*Lua_Orig_ProcessEvent)(UObject*, UFunction*, void*) = nullptr;

// ==================== LOG ====================
void WriteLuaLog(const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    std::ofstream file("/sdcard/lua_debug.txt", std::ios::app);
    if (file.is_open()) {
        time_t now = time(nullptr);
        file << "[" << KAUSHIK_NAME << "] " << std::ctime(&now) << " : " << buffer << std::endl;
        file.close();
    }
}

// ==================== STATUS RECORDING HELPER ====================
// Writes/updates a flag inside _G.__AnoyStatus table in Lua.
// Call after each script finishes.
static void AnoySetStatus(int64_t state, const char* key, bool ok) {
    if (!state || !lua.loadBuffer || !lua.pcall) return;
    char buf[256];
    snprintf(buf, sizeof(buf),
        "_G.__AnoyStatus = _G.__AnoyStatus or {}\n"
        "_G.__AnoyStatus['%s'] = %s\n",
        key, ok ? "true" : "false");
    if (lua.loadBuffer(state, buf, strlen(buf), "@status", "t") == 0) {
        lua.pcall(state, 0, 0, 0);
    }
}


// ==================== SCRIPT ÇALIŞTIR ====================
bool Kaushik_ExecuteLuaScript(int64_t state) {
    if (!state || !lua.loadBuffer || !lua.pcall) {
        WriteLuaLog("Invalid parameters");
        return false;
    }

    // Reset status table
    {
        const char* init = "_G.__AnoyStatus = {}";
        if (lua.loadBuffer(state, init, strlen(init), "@statusInit", "t") == 0) {
            lua.pcall(state, 0, 0, 0);
        }
    }

    bool ok = false;
    
    ok = (lua.loadBuffer(state, bypass_script, strlen(bypass_script), "@bypass", "t") == 0);
    if (ok) ok = (lua.pcall(state, 0, 0, 0) == 0);
    AnoySetStatus(state, "bypass", ok);
    if (!ok) WriteLuaLog("bypass failed");
    
    ok = (lua.loadBuffer(state, bypass2_script, strlen(bypass2_script), "@bypass2", "t") == 0);
    if (ok) ok = (lua.pcall(state, 0, 0, 0) == 0);
    AnoySetStatus(state, "bypass2", ok);
    if (!ok) WriteLuaLog("bypass2 failed");

    // 3. Mortar auto-aim
    ok = (lua.loadBuffer(state, mortarAim_script, strlen(mortarAim_script), "@mortar", "t") == 0);
    if (ok) ok = (lua.pcall(state, 0, 0, 0) == 0);
    AnoySetStatus(state, "Mortar", ok);
    if (!ok) WriteLuaLog("Mortar failed");

    ok = (lua.loadBuffer(state, GuestLoginLuaScript, strlen(GuestLoginLuaScript), "@guest", "t") == 0);
    if (ok) ok = (lua.pcall(state, 0, 0, 0) == 0);
    AnoySetStatus(state, "Guest", ok);
    if (!ok) WriteLuaLog("Guest failed");
    
    ok = (lua.loadBuffer(state, TwitterLoginLuaScript, strlen(TwitterLoginLuaScript), "@twfix", "t") == 0);
    if (ok) ok = (lua.pcall(state, 0, 0, 0) == 0);
    AnoySetStatus(state, "Twitter Fix", ok);
    if (!ok) WriteLuaLog("Twitter Fix failed");
    
    // 6. Status report — ALWAYS last, shows the popup
    if (lua.loadBuffer(state, statusReport_script, strlen(statusReport_script), "@status", "t") == 0) {
        lua.pcall(state, 0, 0, 0);
    }

    WriteLuaLog("Injection completed");
    return true;
}

// ==================== HOOK: loadbufferx (state yakala) ====================
int64_t hooked_lua_loadbufferx(int64_t L, const char* buff, size_t sz, const char* name, const char* mode) {
    if (!G_LuaState) {
        G_LuaState = L;
        WriteLuaLog("Captured LuaState: %p", (void*)L);
    }
    return orig_lua_loadbufferx(L, buff, sz, name, mode);
}

// ==================== HOOK: ProcessEvent (inject) ====================
void Lua_Hook_ProcessEvent(UObject* object, UFunction* function, void* params) {
    static bool injectionAttempted = false;

    if (!injectionAttempted && G_LuaState && ++processEventCounter >= 20) {
        injectionAttempted = true;
        isInjected = Kaushik_ExecuteLuaScript(G_LuaState);
    }

    return Lua_Orig_ProcessEvent(object, function, params);
}

// ==================== INIT ====================
void InitLuaHooks(uintptr_t UE4) {
    lua.loadBuffer = (decltype(lua.loadBuffer))(UE4 + LuaLoadBuffer_Offset);
    lua.pcall      = (decltype(lua.pcall))(UE4 + LuaPCall_Offset);
    lua.load       = (decltype(lua.load))(UE4 + LuaLoad_Offset);

    WriteLuaLog("Init - UE4: %p", (void*)UE4);
    WriteLuaLog("Init - loadBuffer: %p", (void*)lua.loadBuffer);
    WriteLuaLog("Init - pcall: %p", (void*)lua.pcall);
    WriteLuaLog("Init - ProcessEvent: %p", (void*)(UE4 + ProcessEvent_Offset));

    // ✅ Dobby hook - loadbufferx (state yakala)
    shadowhook_hook_func_addr((void*)(UE4 + LuaLoadBuffer_Offset),
              (void*)hooked_lua_loadbufferx,
              (void**)&orig_lua_loadbufferx);

    // ✅ Dobby hook - ProcessEvent (inject)
    shadowhook_hook_func_addr((void*)(UE4 + ProcessEvent_Offset),
              (void*)Lua_Hook_ProcessEvent,
              (void**)&Lua_Orig_ProcessEvent);

    WriteLuaLog("Hooks installed");
}