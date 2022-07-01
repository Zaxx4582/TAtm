# TAtm
SA-MP include helps scripters made atm easier

# Functions
```pawn
ATM:CreateATM(Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
SetATMPos(ATM:atmID, Float:x, Float:y, Float:z);
SetATMRotation(ATM:atmID, Float:rx, Float:ry, Float:rz);

GetATMPos(ATM:atmID, Float:x, Float:y, Float:z);
GetATMRotaion(ATM:atmID, Float:rx, Float:ry, Float:rz);

DestroyATM(ATM:atmID);
ShowATMProfile(ATM:atmID);
```

# Callback
```pawn
public OnPlayerOnATM(playerid)
```
