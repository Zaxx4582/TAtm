# TAtm
SA-MP include helps scripters made atm easier

# Tips
- OnPlayerOnATM callback base of KEY_YES to execute click Y.
- Must have streamer plugin to work this include.

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

# Example
```pawn
#include <a_samp>
#include <streamer>
#include <TAtm>

#define DIALOG_ATM (1)

new ATM:g_ATM;

public OnGameModeInit()
{
    g_ATM = CreateATM(100.0, 100.0, 9.0, 1.0, 1.0, 1.0);
    ShowATMProfile(g_ATM);
    return 1;
}

public OnPlayerOnATM(playerid)
{
    ShowPlayerDialog(playerid, DIALOG_ATM, DIALOG_STYLE_LIST, "ATM", "Withdraw\nDeposit\nTransfer", "Select", "Cancel");     
    return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == DIALOG_ATM) {
        if(!response) return 1;
        
        SendClientMessage(playerid, -1, "Hi!");
    }
    return 1;
}

