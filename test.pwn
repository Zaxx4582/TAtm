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
