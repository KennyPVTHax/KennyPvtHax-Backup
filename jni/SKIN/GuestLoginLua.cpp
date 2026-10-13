#pragma once


const char* GuestLoginLuaScript = R"lua(
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
)lua";
