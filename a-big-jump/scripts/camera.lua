-- Enum
local behaviours = {
	FOLLOW = {},
	LOCK   = {},
	BEHIND = {},
	TRIPOD = {}
}

local radiansPerSecond = 10

local x = 0
local y = 0
local delta = 0

local incrementedRotations = False
local behaviour = behaviours.FOLLOW;

UpdateCameraControls = function(X, Y, Delta)
	x = X
	y = Y
	delta = Delta
end

return x * radiansPerSecond * delta
