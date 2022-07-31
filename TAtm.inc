/*
    
    TAtm - Dynamic ATM framework.
    
    [Scripter]: Tiyo#7124 & Zaxx
    [Script Date]: July 1, 2022
    
    ATM Functions:
    ATM:CreateATM(Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
    GetATMPos(ATM:atmID);
    GetATMRotation(ATM:atmID);
    
    SetATMPos(ATM:atmID, Float:x, Float:y, Float:z);
    SetATMRotation(ATM:atmID, Float:rx, Float:ry, Float:rz);
    DestroyATM(ATM:atmID);
    ShowATMProfile(ATM:atmID);
    
    CallBack:
    public OnPlayerOnATM(playerid)
    
    Tips:
    If you are using this include to filterscript make sure to
    define #define TAtm_FILTERSCRIPT before you including this file.
   
*/



#define MAX_TATMS (500)

forward OnPlayerIsOnATM(playerid);
enum E_ATM
{
    atm_Exists,
    atm_ID,
    Float:atm_X,
    Float:atm_Y,
    Float:atm_Z,
    Float:atm_RX,
    Float:atm_RY,
    Float:atm_RZ
};
static 
    ATMData[MAX_TATMS * 2][E_ATM],
    ATMCash[MAX_PLAYERS];
    
    
static GetFreeAtmID()
{
   for(new i = 0; i < MAX_TATMS; i++) {
       if(!ATMData[i][atm_Exists])
           return i;
   }
   return -1;
}
    
stock ATM:CreateATM(Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    new atmIDS = GetFreeAtmID();
    
    ATMData[atmIDS][atm_Exists] = 1;
    ATMData[atmIDS][atm_ID] = CreateDynamicObject(19324, x, y, z-0.5, rx, ry, rz);
    
    ATMData[atmIDS][atm_X] = x;
    ATMData[atmIDS][atm_Y] = y;
    ATMData[atmIDS][atm_Z] = z;
    
    ATMData[atmIDS][atm_RX] = rx;
    ATMData[atmIDS][atm_RY] = ry;
    ATMData[atmIDS][atm_RZ] = rz;
    printf("[TAtm-Success]: Server was created ATM at position %f, %f, %f, and rotation %f, %f, %f", x, y, z, rx, ry, rz);
    return ATM:atmIDS;
}

stock SetATMPos(ATM:atmID, Float:x, Float:y, Float:z)
{
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, ATMData[_:atmID][atm_ID], E_STREAMER_X, x);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, ATMData[_:atmID][atm_ID], E_STREAMER_Y, y);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, ATMData[_:atmID][atm_ID], E_STREAMER_Z, z - 0.5);
    
    ATMData[_:atmID][atm_X] = x;
    ATMData[_:atmID][atm_Y] = y;
    ATMData[_:atmID][atm_Z] = z - 2;
    printf("[TAtm-Update]: Server was edited atmID %i to position %f, %f, %f", _:atmID, x, y, z);
    return 1;
}

stock SetATMRotation(ATM:atmID, Float:rx, Float:ry, Float:rz)
{
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, ATMData[_:atmID][atm_ID], E_STREAMER_R_X, rx);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, ATMData[_:atmID][atm_ID], E_STREAMER_R_Y, ry);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, ATMData[_:atmID][atm_ID], E_STREAMER_R_Z, rz);
    
    ATMData[_:atmID][atm_RX] = rx;
    ATMData[_:atmID][atm_RY] = ry;
    ATMData[_:atmID][atm_RZ] = rz;
    printf("[TAtm-Update]: Server was edited atmID %i to rotation %f, %f, %f", _:atmID, rx, ry, rz);
    return 1;
}

stock GetATMPos(ATM:atmID, &Float:x, &Float:y, &Float:z)
{
    x = ATMData[_:atmID][atm_X];
    y = ATMData[_:atmID][atm_Y];
    z = ATMData[_:atmID][atm_Z];
    return 1;
}

stock GetATMRotation(ATM:atmID, Float:rx, Float:ry, Float:rz)
{
    rx = ATMData[_:atmID][atm_RX];
    ry = ATMData[_:atmID][atm_RY];
    rz = ATMData[_:atmID][atm_RZ];
    return 1;
}

stock DestroyATM(ATM:atmID)
{
    ATMData[_:atmID][atm_Exists] = 0;
    ATMData[_:atmD][atm_X] = 0.0;
    ATMData[_:atmD][atm_Y] = 0.0;
    ATMData[_:atmD][atm_Z] = 0.0;
    
    ATMData[_:atmD][atm_RX] = 0.0;
    ATMData[_:atmD][atm_RY] = 0.0;
    ATMData[_:atmD][atm_RZ] = 0.0;
    return 1;
}

stock ShowATMProfile(ATM:atmID)
{
    printf("[TAtm Profiler]:\n\
    MODELID = 19324\n\
    X = %f\n\
    Y = %f\n\
    Z = %f\n\
    RX = %f\n\
    RY = %f\n\
    RZ = %f",
    ATMData[_:atmID][atm_X],
    ATMData[_:atmID][atm_Y], 
    ATMData[_:atmID][atm_Z], 
    ATMData[_:atmID][atm_RX], 
    ATMData[_:atmID][atm_RY], 
    ATMData[_:atmID][atm_RZ]);
    return 1;
}
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == KEY_YES) {
        for(new i = 0; i < MAX_TATMS; i++) {
	        if(IsPlayerInRangeOfPoint(playerid, 1.0, ATMData[i][atm_X], ATMData[i][atm_Y], ATMData[i][atm_Z])) {
	            CallLocalFunction("OnPlayerOnATM", "i", playerid);
	            
	        }
	    }
	    return 1;
    }
    return 1;
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange OnPlayerOnATM
forward OnPlayerOnATM(playerid);

    
