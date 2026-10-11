#pragma once


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