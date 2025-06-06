local StarterGui = game:GetService("StarterGui")

-- Instances
local ScreenGui = Instance.new("ScreenGui")
local MainFrame = Instance.new("Frame")
local Title = Instance.new("TextLabel")
local InnerFrame = Instance.new("Frame")
local SpeedTextBox = Instance.new("TextBox")
local DecreaseButton = Instance.new("TextButton")
local IncreaseButton = Instance.new("TextButton")
local FlyButton = Instance.new("TextButton")
local DestroyButton = Instance.new("TextButton")
local UIGradient = Instance.new("UIGradient")
local UICorner = Instance.new("UICorner")
local UIStroke = Instance.new("UIStroke")

-- ScreenGui properties
ScreenGui.Parent = game.Players.LocalPlayer:WaitForChild("PlayerGui")
ScreenGui.ResetOnSpawn = false

-- MainFrame properties
MainFrame.Parent = ScreenGui
MainFrame.BackgroundColor3 = Color3.fromRGB(45, 45, 45)
MainFrame.Position = UDim2.new(0.3, 0, 0.5, -100)
MainFrame.Size = UDim2.new(0, 200, 0, 190)
MainFrame.Active = true
MainFrame.Draggable = true

-- UIStroke properties for MainFrame
UIStroke.Parent = MainFrame
UIStroke.Color = Color3.fromRGB(0, 0, 0)
UIStroke.Thickness = 2

-- Title properties
Title.Parent = MainFrame
Title.BackgroundTransparency = 1
Title.Size = UDim2.new(1, 0, 0.2, 0)
Title.Font = Enum.Font.GothamBold
Title.Text = "Летающая машина"
Title.TextColor3 = Color3.fromRGB(0, 255, 0)
Title.TextScaled = true

-- InnerFrame properties
InnerFrame.Parent = MainFrame
InnerFrame.BackgroundColor3 = Color3.fromRGB(60, 60, 60)
InnerFrame.Size = UDim2.new(1, 0, 0.6, 0)
InnerFrame.Position = UDim2.new(0, 0, 0.2, 0)

-- SpeedTextBox properties
SpeedTextBox.Parent = InnerFrame
SpeedTextBox.BackgroundColor3 = Color3.fromRGB(255, 255, 0)
SpeedTextBox.Position = UDim2.new(0.5, -25, 0.1, 0)
SpeedTextBox.Size = UDim2.new(0, 50, 0, 30)
SpeedTextBox.Font = Enum.Font.Gotham
SpeedTextBox.Text = "1"
SpeedTextBox.TextColor3 = Color3.fromRGB(0, 255, 255)
SpeedTextBox.TextScaled = true
SpeedTextBox.PlaceholderText = "Скорость"

-- DecreaseButton properties
DecreaseButton.Parent = InnerFrame
DecreaseButton.BackgroundColor3 = Color3.fromRGB(255, 255, 0)
DecreaseButton.Size = UDim2.new(0, 50, 0, 30)
DecreaseButton.Position = UDim2.new(0.1, 0, 0.1, 0)
DecreaseButton.Font = Enum.Font.Gotham
DecreaseButton.Text = "Уменьшить"
DecreaseButton.TextColor3 = Color3.fromRGB(255, 0, 0)
DecreaseButton.TextScaled = true

-- IncreaseButton properties
IncreaseButton.Parent = InnerFrame
IncreaseButton.BackgroundColor3 = Color3.fromRGB(255, 255, 0)
IncreaseButton.Size = UDim2.new(0, 50, 0, 30)
IncreaseButton.Position = UDim2.new(0.8, -30, 0.1, 0)
IncreaseButton.Font = Enum.Font.Gotham
IncreaseButton.Text = "Добавить"
IncreaseButton.TextColor3 = Color3.fromRGB(0, 255, 0)
IncreaseButton.TextScaled = true

-- FlyButton properties
FlyButton.Parent = InnerFrame
FlyButton.BackgroundColor3 = Color3.fromRGB(255, 255, 0)
FlyButton.Size = UDim2.new(0.8, 0, 0.2, 0)
FlyButton.Position = UDim2.new(0.1, 0, 0.40, 0)
FlyButton.Font = Enum.Font.GothamBold
FlyButton.Text = "Летать"
FlyButton.TextColor3 = Color3.fromRGB(255, 0, 255)
FlyButton.TextScaled = true




-- DestroyButton properties
DestroyButton.Parent = InnerFrame
DestroyButton.BackgroundColor3 = Color3.fromRGB(255, 255, 0)
DestroyButton.Size = UDim2.new(0.8, 0, 0.2, 0)
DestroyButton.Position = UDim2.new(0.1, 0, 0.65, 0)
DestroyButton.Font = Enum.Font.GothamBold
DestroyButton.Text = "Убрать"
DestroyButton.TextColor3 = Color3.fromRGB(0, 0, 255)
DestroyButton.TextScaled = true

-- UICorner properties
UICorner.CornerRadius = UDim.new(0.1, 0)
UICorner.Parent = MainFrame

-- UIGradient properties
UIGradient.Parent = MainFrame
UIGradient.Color = ColorSequence.new{
    ColorSequenceKeypoint.new(0, Color3.fromRGB(45, 45, 45)),
    ColorSequenceKeypoint.new(1, Color3.fromRGB(75, 75, 75))
}

-- Button functionalities
DecreaseButton.MouseButton1Click:Connect(function()
    local speed = tonumber(SpeedTextBox.Text) or 1
    SpeedTextBox.Text = tostring(math.max(speed - 1, 1))
end)

IncreaseButton.MouseButton1Click:Connect(function()
    local speed = tonumber(SpeedTextBox.Text) or 1
    SpeedTextBox.Text = tostring(speed + 1)
end)

--Enable Fly Function
local velocityHandlerName
local gyroHandlerName
local camera
local v3none
local v3zero
local v3inf
local controlModule
local bv
local bg
local mfly1
local mfly2

local function EnableFly()
    velocityHandlerName = 32
    gyroHandlerName = 64
    camera = workspace.CurrentCamera
    v3none = Vector3.new()
    v3zero = Vector3.new(0, 0, 0)
    v3inf = Vector3.new(9e9, 9e9, 9e9)
    controlModule = require(game.Players.LocalPlayer.PlayerScripts:WaitForChild("PlayerModule"):WaitForChild("ControlModule"))

    bv = Instance.new("BodyVelocity")
    bv.Name = velocityHandlerName
    bv.Parent = game.Players.LocalPlayer.Character.HumanoidRootPart
    bv.MaxForce = v3zero
    bv.Velocity = v3zero

    bg = Instance.new("BodyGyro")
    bg.Name = gyroHandlerName
    bg.Parent = game.Players.LocalPlayer.Character.HumanoidRootPart
    bg.MaxTorque = v3inf
    bg.P = 1000
    bg.D = 50

    mfly1 = game.Players.LocalPlayer.CharacterAdded:Connect(function()
        local bv = Instance.new("BodyVelocity")
        bv.Name = velocityHandlerName
        bv.Parent = game.Players.LocalPlayer.Character.HumanoidRootPart
        bv.MaxForce = v3zero
        bv.Velocity = v3zero

        bg = Instance.new("BodyGyro")
        bg.Name = gyroHandlerName
        bg.Parent = game.Players.LocalPlayer.Character.HumanoidRootPart
        bg.MaxTorque = v3inf
        bg.P = 1000
        bg.D = 50
    end)

    mfly2 = game:GetService('RunService').RenderStepped:Connect(function()
        camera = workspace.CurrentCamera
        local speed = tonumber(SpeedTextBox.Text) or 1 -- Default to 1 if input is invalid

        if game.Players.LocalPlayer.Character:FindFirstChildWhichIsA("Humanoid") 
            and game.Players.LocalPlayer.Character.HumanoidRootPart 
            and game.Players.LocalPlayer.Character.HumanoidRootPart:FindFirstChild(velocityHandlerName) 
            and game.Players.LocalPlayer.Character.HumanoidRootPart:FindFirstChild(gyroHandlerName) then

            local humanoid = game.Players.LocalPlayer.Character:FindFirstChildWhichIsA("Humanoid")
            local VelocityHandler = game.Players.LocalPlayer.Character.HumanoidRootPart:FindFirstChild(velocityHandlerName)
            local GyroHandler = game.Players.LocalPlayer.Character.HumanoidRootPart:FindFirstChild(gyroHandlerName)

            VelocityHandler.MaxForce = v3inf
            GyroHandler.MaxTorque = v3inf
            GyroHandler.CFrame = camera.CFrame

            local direction = controlModule:GetMoveVector()
            local calculatedVelocity = v3none

            -- Apply movement based on direction and speed
            calculatedVelocity = calculatedVelocity 
                                 + camera.CFrame.RightVector * direction.X * speed * 50
                                 - camera.CFrame.LookVector * direction.Z * speed * 50

            VelocityHandler.Velocity = calculatedVelocity
        end
    end)
end
--


--Disable Fly Function
local function DisableFly()
	if game.Players.LocalPlayer.Character.HumanoidRootPart:FindFirstChild(velocityHandlerName) and game.Players.LocalPlayer.Character.HumanoidRootPart:FindFirstChild(gyroHandlerName) then
		game.Players.LocalPlayer.Character.HumanoidRootPart:FindFirstChild(velocityHandlerName):Destroy()
		game.Players.LocalPlayer.Character.HumanoidRootPart:FindFirstChild(gyroHandlerName):Destroy()
	end
	game.Players.LocalPlayer.Character:FindFirstChildWhichIsA("Humanoid").PlatformStand = false
    if mfly1 then
        mfly1:Disconnect()
    end
    if mfly2 then
        mfly2:Disconnect()
    end
end
--


FlyButton.MouseButton1Click:Connect(function()
    if FlyButton.Text == "Летать" then
        FlyButton.Text = "Не летать"
        EnableFly()
    else
        FlyButton.Text = "Летать"
        DisableFly()
    end
end)

DestroyButton.MouseButton1Click:Connect(function()
    DisableFly() -- Disconnect fly functions
    ScreenGui:Destroy()
end)
