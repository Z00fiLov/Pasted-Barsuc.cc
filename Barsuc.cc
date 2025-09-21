suithud:
-- barsyc.cc Exploit Script by Colin
if not game:IsLoaded() then 
    game.Loaded:Wait()
end

if not syn or not protectgui then
    getgenv().protectgui = function() end
end

-- Services
local Players = game:GetService("Players")
local RunService = game:GetService("RunService")
local UIS = game:GetService("UserInputService")
local TweenService = game:GetService("TweenService")
local SoundService = game:GetService("SoundService")
local LocalPlayer = Players.LocalPlayer
local Mouse = LocalPlayer:GetMouse()
local Camera = workspace.CurrentCamera

-- Config
local Config = {
    InfRange = false,
    SpeedBoost = {
        Enabled = false,
        Speed = 50
    },
    SilentAim = {
        Enabled = false,
        ToggleKey = "RightAlt",
        TargetPart = "Head", -- Changed from HumanoidRootPart to Head
        FOVRadius = 130,
        ShowSilentAimTarget = true
    },
    ESP = {
        Enabled = false,
        ShowNames = true,
        ShowHealth = true
    },
    Music = {
        CurrentTrack = 1,
        Tracks = {
            {id = 120785124326826, name = "Village Track 1"},
            {id = 118906631204450, name = "Village Track 2"},
            {id = 88067083009297, name = "Village Track 3"},
            {id = 85141435607173, name = "Track 1"},
            {id = 98463334765906, name = "Track 2"}
        }
    }
}

-- GUI Creation
local ScreenGui = Instance.new("ScreenGui")
ScreenGui.Name = "barsycGUI"
ScreenGui.Parent = game.CoreGui
ScreenGui.ResetOnSpawn = false
protectgui(ScreenGui)

local MainFrame = Instance.new("Frame")
MainFrame.Size = UDim2.new(0, 400, 0, 450)
MainFrame.Position = UDim2.new(0.5, -200, 0.5, -225)
MainFrame.BackgroundColor3 = Color3.fromRGB(45, 45, 45)
MainFrame.BorderSizePixel = 0
MainFrame.BorderColor3 = Color3.fromRGB(255, 105, 180)
MainFrame.BorderMode = Enum.BorderMode.Outline
MainFrame.Active = true
MainFrame.Draggable = true
MainFrame.Parent = ScreenGui

local UICorner = Instance.new("UICorner")
UICorner.CornerRadius = UDim.new(0, 8)
UICorner.Parent = MainFrame

local Title = Instance.new("TextLabel")
Title.Size = UDim2.new(1, 0, 0, 40)
Title.BackgroundColor3 = Color3.fromRGB(255, 20, 147)
Title.Text = "barsyc.cc"
Title.TextColor3 = Color3.fromRGB(0, 0, 0)
Title.Font = Enum.Font.GothamBlack
Title.TextSize = 18
Title.Parent = MainFrame

local UICorner_2 = Instance.new("UICorner")
UICorner_2.CornerRadius = UDim.new(0, 8)
UICorner_2.Parent = Title

local CloseButton = Instance.new("TextButton")
CloseButton.Size = UDim2.new(0, 40, 0, 40)
CloseButton.Position = UDim2.new(1, -40, 0, 0)
CloseButton.BackgroundColor3 = Color3.fromRGB(255, 50, 50)
CloseButton.Text = "X"
CloseButton.TextColor3 = Color3.fromRGB(0, 0, 0)
CloseButton.Font = Enum.Font.GothamBlack
CloseButton.TextSize = 16
CloseButton.Parent = MainFrame

local UICorner_3 = Instance.new("UICorner")
UICorner_3.CornerRadius = UDim.new(0, 8)
UICorner_3.Parent = CloseButton

-- Music Player
local MusicSound = Instance.new("Sound")
MusicSound.SoundId = "rbxassetid://" .. Config.Music.Tracks[Config.Music.CurrentTrack].id
MusicSound.Volume = 0.5
MusicSound.Parent = SoundService

local MusicLabel = Instance.new("TextLabel")
MusicLabel.Size = UDim2.new(0.9, 0, 0, 25)
MusicLabel.Position = UDim2.new(0.05, 0, 0.1, 0)
MusicLabel.BackgroundTransparency = 1
MusicLabel.Text = "Music: " .. Config.Music.Tracks[Config.Music.CurrentTrack].name
MusicLabel.TextColor3 = Color3.fromRGB(255, 255, 255)
MusicLabel.Font = Enum.Font.GothamBold
MusicLabel.TextSize = 14
MusicLabel.Parent = MainFrame

local MusicToggle = Instance.new("TextButton")
MusicToggle.Size = UDim2.new(0.4, 0, 0, 35)
MusicToggle.Position = UDim2.new(0.05, 0, 0.15, 0)
MusicToggle.BackgroundColor3 = Color3.fromRGB(75, 75, 75)
MusicToggle.Text = "Play"
MusicToggle.TextColor3 = Color3.fromRGB(0, 0, 0)
MusicToggle.Font = Enum.Font.GothamBold
MusicToggle.TextSize = 14
MusicToggle.Parent = MainFrame

local UICorner_4 = Instance.new("UICorner")
UICorner_4.CornerRadius = UDim.new(0, 6)
UICorner_4.Parent = MusicToggle

local NextTrackButton = Instance.new("TextButton")
NextTrackButton.Size = UDim2.new(0.4, 0, 0, 35)
NextTrackButton.Position = UDim2.new(0.55, 0, 0.15, 0)
NextTrackButton.BackgroundColor3 = Color3.fromRGB(75, 75, 75)
NextTrackButton.Text = "Next Track"
NextTrackButton.TextColor3 = Color3.fromRGB(0, 0, 0)
NextTrackButton.Font = Enum.Font.GothamBold
NextTrackButton.TextSize = 14
NextTrackButton.Parent = MainFrame

local UICorner_5 = Instance.new("UICorner")
UICorner_5.CornerRadius = UDim.new(0, 6)
UICorner_5.Parent = NextTrackButton

-- Infinite Range Toggle
local InfRangeToggle = Instance.new("TextButton")
InfRangeToggle.Size = UDim2.new(0.9, 0, 0, 35)
InfRangeToggle.Position = UDim2.new(0.05, 0, 0.25, 0)
InfRangeToggle.BackgroundColor3 = Color3.fromRGB(75, 75, 75)
InfRangeToggle.Text = "Infinite Range: OFF"
InfRangeToggle.TextColor3 = Color3.fromRGB(0, 0, 0)
InfRangeToggle.Font = Enum.Font.GothamBold
InfRangeToggle.TextSize = 14
InfRangeToggle.Parent = MainFrame

local UICorner_6 = Instance.new("UICorner")
UICorner_6.CornerRadius = UDim.new(0, 6)
UICorner_6.Parent = InfRangeToggle

-- Speed Boost Toggle
local SpeedToggle = Instance.new("TextButton")
SpeedToggle.Size = UDim2.new(0.9, 0, 0, 35)
SpeedToggle.Position = UDim2.new(0.05, 0, 0.35, 0)
SpeedToggle.BackgroundColor3 = Color3.fromRGB(75, 75, 75)
SpeedToggle.Text = "Speed Boost: OFF"
SpeedToggle.TextColor3 = Color3.fromRGB(0, 0, 0)
SpeedToggle.Font = Enum.Font.GothamBold
SpeedToggle.TextSize = 14
SpeedToggle.Parent = MainFrame

local UICorner_7 = Instance.new("UICorner")
UICorner_7.CornerRadius = UDim.new(0, 6)
UICorner_7.Parent = SpeedToggle

-- Speed Slider
local SpeedLabel = Instance.new("TextLabel")
SpeedLabel.Size = UDim2.new(0.9, 0, 0, 25)
SpeedLabel.Position = UDim2.new(0.05, 0, 0.45, 0)
SpeedLabel.BackgroundTransparency = 1
SpeedLabel.Text = "Speed: 50"
SpeedLabel.TextColor3 = Color3.fromRGB(255, 255, 255)
SpeedLabel.Font = Enum.Font.GothamBold
SpeedLabel.TextSize = 14
SpeedLabel.Parent = MainFrame

local SpeedSlider = Instance.new("Frame")
SpeedSlider.Size = UDim2.new(0.9, 0, 0, 25)
SpeedSlider.Position = UDim2.new(0.05, 0, 0.5, 0)
SpeedSlider.BackgroundColor3 = Color3.fromRGB(60, 60, 60)
SpeedSlider.Parent = MainFrame

local UICorner_8 = Instance.new("UICorner")
UICorner_8.CornerRadius = UDim.new(0, 6)
UICorner_8.Parent = SpeedSlider

local SpeedFill = Instance.new("Frame")
SpeedFill.Size = UDim2.new(0.5, 0, 1, 0)
SpeedFill.BackgroundColor3 = Color3.fromRGB(255, 20, 147)
SpeedFill.Parent = SpeedSlider

local UICorner_9 = Instance.new("UICorner")
UICorner_9.CornerRadius = UDim.new(0, 6)
UICorner_9.Parent = SpeedFill

local SpeedButton = Instance.new("TextButton")
SpeedButton.Size = UDim2.new(0, 25, 0, 25)
SpeedButton.Position = UDim2.new(0.5, -12.5, 0, 0)
SpeedButton.BackgroundColor3 = Color3.fromRGB(200, 200, 200)
SpeedButton.Text = ""
SpeedButton.Parent = SpeedSlider

local UICorner_10 = Instance.new("UICorner")
UICorner_10.CornerRadius = UDim.new(0, 12)
UICorner_10.Parent = SpeedButton

-- Silent Aim Toggle
local SilentAimToggle = Instance.new("TextButton")
SilentAimToggle.Size = UDim2.new(0.9, 0, 0, 35)
SilentAimToggle.Position = UDim2.new(0.05, 0, 0.6, 0)
SilentAimToggle.BackgroundColor3 = Color3.fromRGB(75, 75, 75)
SilentAimToggle.Text = "Silent Aim: OFF"
SilentAimToggle.TextColor3 = Color3.fromRGB(0, 0, 0)
SilentAimToggle.Font = Enum.Font.GothamBold
SilentAimToggle.TextSize = 14
SilentAimToggle.Parent = MainFrame

local UICorner_11 = Instance.new("UICorner")
UICorner_11.CornerRadius = UDim.new(0, 6)
UICorner_11.Parent = SilentAimToggle

-- ESP Toggle
local ESPToggle = Instance.new("TextButton")
ESPToggle.Size = UDim2.new(0.9, 0, 0, 35)
ESPToggle.Position = UDim2.new(0.05, 0, 0.7, 0)
ESPToggle.BackgroundColor3 = Color3.fromRGB(75, 75, 75)
ESPToggle.Text = "ESP: OFF"
ESPToggle.TextColor3 = Color3.fromRGB(0, 0, 0)
ESPToggle.Font = Enum.Font.GothamBold
ESPToggle.TextSize = 14
ESPToggle.Parent = MainFrame

local UICorner_12 = Instance.new("UICorner")
UICorner_12.CornerRadius = UDim.new(0, 6)
UICorner_12.Parent = ESPToggle

-- Silent Aim Variables
getgenv().SilentAimSettings = Config.SilentAim

local GetPlayers = Players.GetPlayers
local WorldToScreen = Camera.WorldToScreenPoint
local WorldToViewportPoint = Camera.WorldToViewportPoint
local FindFirstChild = game.FindFirstChild
local RenderStepped = RunService.RenderStepped
local GetMouseLocation = UIS.GetMouseLocation

local resume = coroutine.resume 
local create = coroutine.create

local mouse_box = Drawing.new("Square")
mouse_box.Visible = Config.SilentAim.ShowSilentAimTarget 
mouse_box.ZIndex = 999 
mouse_box.Color = Color3.fromRGB(54, 57, 241)
mouse_box.Thickness = 20 
mouse_box.Size = Vector2.new(20, 20)
mouse_box.Filled = true 

local fov_circle = Drawing.new("Circle")
fov_circle.Thickness = 1
fov_circle.NumSides = 100
fov_circle.Radius = Config.SilentAim.FOVRadius
fov_circle.Filled = false
fov_circle.Visible = true
fov_circle.ZIndex = 999
fov_circle.Transparency = 1
fov_circle.Color = Color3.fromRGB(54, 57, 241)

-- ESP Variables
local ESP = {
    Drawings = {}
}

local ExpectedArguments = {
    Raycast = {
        ArgCountRequired = 3,
        Args = {
            "Instance", "Vector3", "Vector3", "RaycastParams"
        }
    }
}

-- Functions
local function getPositionOnScreen(Vector)
    local Vec3, OnScreen = WorldToScreen(Camera, Vector)
    return Vector2.new(Vec3.X, Vec3.Y), OnScreen
end

local function ValidateArguments(Args, RayMethod)
    local Matches = 0
    if #Args < RayMethod.ArgCountRequired then
        return false
    end
    for Pos, Argument in next, Args do
        if typeof(Argument) == RayMethod.Args[Pos] then
            Matches = Matches + 1
        end
    end
    return Matches >= RayMethod.ArgCountRequired
end

local function getSilentAimDirection(origin, position, velocity)
    return (position - origin).Unit * (velocity or 1000)
end

local function safeCopyArguments(args)
    local copy = {}
    for i, v in ipairs(args) do
        copy[i] = v
    end
    return copy
end

local function getMousePosition()
    return GetMouseLocation(UIS)
end

local function getClosestPlayer()
    if not Config.SilentAim.TargetPart then return end
    local Closest
    local DistanceToMouse
    for _, Player in next, GetPlayers(Players) do
        if Player == LocalPlayer then continue end

        local Character = Player.Character
        if not Character then continue end

        local Head = FindFirstChild(Character, "Head")
        local Humanoid = FindFirstChild(Character, "Humanoid")
        if not Head or not Humanoid or Humanoid and Humanoid.Health <= 0 then continue end

        local ScreenPosition, OnScreen = getPositionOnScreen(Head.Position)
        if not OnScreen then continue end

        local Distance = (getMousePosition() - ScreenPosition).Magnitude
        if Distance <= (DistanceToMouse or Config.SilentAim.FOVRadius or 2000) then
            Closest = Character[Config.SilentAim.TargetPart] -- This will now target Head
            DistanceToMouse = Distance
        end
    end
    return Closest
end

local function applyGunValues(tool)
    local gun = tool:FindFirstChild("Gun")
    if not gun then return end
    if not Config.OriginalValues then Config.OriginalValues = {} end
    if not Config.OriginalValues[gun] then
        Config.OriginalValues[gun] = {}
        for _, v in ipairs(gun:GetChildren()) do
            if v:IsA("NumberValue") or v:IsA("BoolValue") then
                Config.OriginalValues[gun][v.Name] = v.Value
            end
        end
    end
    
    local range = gun:FindFirstChild("Range")
    if range then
        range.Value = Config.InfRange and 100000 or (Config.OriginalValues[gun][range.Name] or range.Value)
    end
end

-- ESP Functions
local function createESP(player)
    if ESP.Drawings[player] then return end
    
    local drawings = {}
    local character = player.Character or player.CharacterAdded:Wait()
    
    -- Player Name
    local name = Drawing.new("Text")
    name.Visible = false
    name.Color = Color3.fromRGB(255, 255, 255)
    name.Size = 14
    name.Center = true
    name.Outline = true
    name.Text = player.Name
    drawings.Name = name
    
    -- Health Bar Background
    local healthBg = Drawing.new("Square")
    healthBg.Visible = false
    healthBg.Color = Color3.fromRGB(50, 50, 50)
    healthBg.Thickness = 1
    healthBg.Filled = true
    drawings.HealthBg = healthBg
    
    -- Health Bar Fill
    local healthFill = Drawing.new("Square")
    healthFill.Visible = false
    healthFill.Color = Color3.fromRGB(0, 255, 0)
    healthFill.Thickness = 1
    healthFill.Filled = true
    drawings.HealthFill = healthFill
    
    -- Health Text
    local healthText = Drawing.new("Text")
    healthText.Visible = false
    healthText.Color = Color3.fromRGB(255, 255, 255)
    healthText.Size = 12
    healthText.Center = true
    healthText.Outline = true
    drawings.HealthText = healthText
    
    ESP.Drawings[player] = drawings
    
    local function updateESP()
        if not character or not character:FindFirstChild("Humanoid") or character.Humanoid.Health <= 0 then
            name.Visible = false
            healthBg.Visible = false
            healthFill.Visible = false
            healthText.Visible = false
            return
        end
        
        local head = character:FindFirstChild("Head")
        if not head then return end
        
        local position, onScreen = WorldToScreen(Camera, head.Position)
        if not onScreen then
            name.Visible = false
            healthBg.Visible = false
            healthFill.Visible = false
            healthText.Visible = false
            return
        end
        
        local humanoid = character:FindFirstChild("Humanoid")
        local health = humanoid and humanoid.Health or 0
        local maxHealth = humanoid and humanoid.MaxHealth or 100
        
        if Config.ESP.Enabled and Config.ESP.ShowNames then
            name.Position = Vector2.new(position.X, position.Y - 40)
            name.Visible = true
        else
            name.Visible = false
        end
        
        if Config.ESP.Enabled and Config.ESP.ShowHealth then
            local barWidth = 50
            local barHeight = 6
            local healthPercentage = health / maxHealth
            
            healthBg.Size = Vector2.new(barWidth, barHeight)
            healthBg.Position = Vector2.new(position.X - barWidth/2, position.Y - 30)
            healthBg.Visible = true
            
            healthFill.Size = Vector2.new(barWidth * healthPercentage, barHeight)
            healthFill.Position = Vector2.new(position.X - barWidth/2, position.Y - 30)
            healthFill.Color = Color3.fromRGB(255 * (1 - healthPercentage), 255 * healthPercentage, 0)
            healthFill.Visible = true
            
            healthText.Text = math.floor(health) .. "/" .. math.floor(maxHealth)
            healthText.Position = Vector2.new(position.X, position.Y - 45)
            healthText.Visible = true
        else
            healthBg.Visible = false
            healthFill.Visible = false
            healthText.Visible = false
        end
    end
    
    RunService.RenderStepped:Connect(updateESP)
end

local function setupESP()
    for _, player in ipairs(Players:GetPlayers()) do
        if player ~= LocalPlayer then
            player.CharacterAdded:Connect(function(character)
                createESP(player)
            end)
            if player.Character then
                createESP(player)
            end
        end
    end
    
    Players.PlayerAdded:Connect(function(player)
        player.CharacterAdded:Connect(function(character)
            createESP(player)
        end)
    end)
    
    Players.PlayerRemoving:Connect(function(player)
        if ESP.Drawings[player] then
            for _, drawing in pairs(ESP.Drawings[player]) do
                drawing:Remove()
            end
            ESP.Drawings[player] = nil
        end
    end)
end

local function toggleESP(state)
    Config.ESP.Enabled = state
    for player, drawings in pairs(ESP.Drawings) do
        if drawings.Name then drawings.Name.Visible = state and Config.ESP.ShowNames end
        if drawings.HealthBg then drawings.HealthBg.Visible = state and Config.ESP.ShowHealth end
        if drawings.HealthFill then drawings.HealthFill.Visible = state and Config.ESP.ShowHealth end
        if drawings.HealthText then drawings.HealthText.Visible = state and Config.ESP.ShowHealth end
    end
end

-- Music Functions
local function changeTrack()
    MusicSound:Stop()
    MusicSound.SoundId = "rbxassetid://" .. Config.Music.Tracks[Config.Music.CurrentTrack].id
    MusicLabel.Text = "Music: " .. Config.Music.Tracks[Config.Music.CurrentTrack].name
    if MusicToggle.Text == "Pause" then
        MusicSound:Play()
    end
end

local function nextTrack()
    Config.Music.CurrentTrack = Config.Music.CurrentTrack % #Config.Music.Tracks + 1
    changeTrack()
end

-- Infinite Range Implementation
local function setupInfRange()
    LocalPlayer.CharacterAdded:Connect(function(character)
        character.ChildAdded:Connect(function(child)
            if child:IsA("Tool") then
                applyGunValues(child)
            end
        end)
    end)

    for _, tool in ipairs(LocalPlayer.Character:GetChildren()) do
        if tool:IsA("Tool") then
            applyGunValues(tool)
        end
    end
end

-- Speed Boost Implementation
local function setupSpeedBoost()
    local function modifySpeed()
        if LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid") then
            LocalPlayer.Character.Humanoid.WalkSpeed = Config.SpeedBoost.Enabled and Config.SpeedBoost.Speed or 16
        end
    end

    LocalPlayer.CharacterAdded:Connect(function(character)
        character:WaitForChild("Humanoid")
        modifySpeed()
    end)

    if LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid") then
        modifySpeed()
    end
end

-- Silent Aim Hooks
local oldNamecall
oldNamecall = hookmetamethod(game, "__namecall", newcclosure(function(...)
    local Method = getnamecallmethod()
    local Arguments = {...}
    local self = Arguments[1]
    if Config.SilentAim.Enabled and self == workspace and not checkcaller() and Method == "Raycast" then
        local HitPart = getClosestPlayer()
        if HitPart and typeof(HitPart) == "Instance" and typeof(HitPart.Position) == "Vector3" and typeof(Arguments[2]) == "Vector3" then
            local Args = safeCopyArguments(Arguments)
            local velocity = Arguments[3] and Arguments[3].Magnitude or nil
            Args[3] = getSilentAimDirection(Arguments[2], HitPart.Position, velocity)
            if typeof(Args[1]) == "Instance" and typeof(Args[2]) == "Vector3" and typeof(Args[3]) == "Vector3" then
                local ok, res = pcall(oldNamecall, unpack(Args))
                if ok then
                    return res
                end
            end
        end
    end
    return oldNamecall(...)
end))

-- GUI Handlers
CloseButton.MouseButton1Click:Connect(function()
    ScreenGui.Enabled = not ScreenGui.Enabled
end)

MusicToggle.MouseButton1Click:Connect(function()
    if MusicSound.IsPlaying then
        MusicSound:Pause()
        MusicToggle.Text = "Play"
    else
        MusicSound:Play()
        MusicToggle.Text = "Pause"
    end
end)

NextTrackButton.MouseButton1Click:Connect(function()
    nextTrack()
end)

InfRangeToggle.MouseButton1Click:Connect(function()
    Config.InfRange = not Config.InfRange
    InfRangeToggle.Text = "Infinite Range: " .. (Config.InfRange and "ON" or "OFF")
    InfRangeToggle.BackgroundColor3 = Config.InfRange and Color3.fromRGB(0, 255, 127) or Color3.fromRGB(75, 75, 75)
    
    for _, tool in ipairs(LocalPlayer.Character:GetChildren()) do
        if tool:IsA("Tool") then
            applyGunValues(tool)
        end
    end
end)

SpeedToggle.MouseButton1Cl
