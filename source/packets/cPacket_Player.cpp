
// cPacket_Player.cpp

/* Implements the player-related packets:
	- PlayerAbilities (0xca)
	- PlayerListItem  (0xc9)
	- PlayerLook      (0x0c)
	- PlayerMoveLook  (0x0d)
	- PlayerPosition  (0x0b)
*/

#include "Globals.h"

#include "cPacket_Player.h"
#include "../cPlayer.h"
#include "../cChatColor.h"





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cPacket_PlayerAbilities:

int cPacket_PlayerAbilities::Parse(const char * a_Data, int a_Size)
{
	if (a_Size < 4)
	{
		return PACKET_INCOMPLETE;
	}
	m_Invulnerable = (a_Data[0] != 0);
	m_IsFlying     = (a_Data[1] != 0);
	m_CanFly       = (a_Data[2] != 0);
	m_InstaMine    = (a_Data[3] != 0);
	return 4;
}





void cPacket_PlayerAbilities::Serialize(AString & a_Data) const
{
	char Data[5];
	Data[0] = m_PacketID;
	Data[1] = (char)m_Invulnerable;
	Data[2] = (char)m_IsFlying;
	Data[3] = (char)m_CanFly;
	Data[4] = (char)m_InstaMine;
	a_Data.append(Data, 5);
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cPacket_PlayerListItem:

cPacket_PlayerListItem::cPacket_PlayerListItem(const AString & a_PlayerName, bool a_Online, short a_Ping)
{
	m_PacketID = E_PLAYER_LIST_ITEM;
	m_PlayerName = a_PlayerName;
	m_Online = a_Online;
	m_Ping = a_Ping;
}





int cPacket_PlayerListItem::Parse(const char * a_Data, int a_Size)
{
	int TotalBytes = 0;
	HANDLE_PACKET_READ(ReadString16, m_PlayerName, TotalBytes);
	HANDLE_PACKET_READ(ReadBool,     m_Online,     TotalBytes);
	HANDLE_PACKET_READ(ReadShort,    m_Ping,       TotalBytes);
	return TotalBytes;
}





void cPacket_PlayerListItem::Serialize(AString & a_Data) const
{
	AString PlayerName(m_PlayerName);
	if (PlayerName.length() > 16)
	{
		PlayerName.erase(16);
	}
	else if (PlayerName.length() <= 14)
	{
		PlayerName += cChatColor::White;
	}

	AppendByte    (a_Data, m_PacketID);
	AppendString16(a_Data, PlayerName);
	AppendBool    (a_Data, m_Online);
	AppendShort   (a_Data, m_Ping);
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cPacket_PlayerLook:

cPacket_PlayerLook::cPacket_PlayerLook( cPlayer* a_Player )
{
	m_PacketID = E_PLAYERLOOK;
	m_Rotation = a_Player->GetRotation();
	m_Pitch    = a_Player->GetPitch();
	m_bFlying  = a_Player->GetFlying();
}





int cPacket_PlayerLook::Parse(const char * a_Data, int a_Size)
{
	int TotalBytes = 0;
	HANDLE_PACKET_READ(ReadFloat, m_Rotation, TotalBytes);
	HANDLE_PACKET_READ(ReadFloat, m_Pitch,    TotalBytes);
	HANDLE_PACKET_READ(ReadBool,  m_bFlying,  TotalBytes);
	return TotalBytes;
}





void cPacket_PlayerLook::Serialize(AString & a_Data) const
{
	AppendByte	(a_Data, m_PacketID);
	AppendFloat	(a_Data, m_Rotation);
	AppendFloat	(a_Data, m_Pitch);
	AppendBool	(a_Data, m_bFlying);
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cPacket_PlayerMoveLook:

cPacket_PlayerMoveLook::cPacket_PlayerMoveLook( cPlayer* a_Player )
{
	m_PacketID = E_PLAYERMOVELOOK;
	m_PosX     = a_Player->GetPosX();
	m_PosY     = a_Player->GetPosY() + 1.65;
	m_PosZ     = a_Player->GetPosZ();
	m_Stance   = a_Player->GetStance();
	m_Rotation = a_Player->GetRotation();
	m_Pitch    = a_Player->GetPitch();
	m_bFlying  = a_Player->GetFlying();
}





int cPacket_PlayerMoveLook::Parse(const char * a_Data, int a_Size)
{
	int TotalBytes = 0;
	HANDLE_PACKET_READ(ReadDouble, m_PosX,     TotalBytes);
	HANDLE_PACKET_READ(ReadDouble, m_PosY,     TotalBytes);
	HANDLE_PACKET_READ(ReadDouble, m_Stance,   TotalBytes);
	HANDLE_PACKET_READ(ReadDouble, m_PosZ,     TotalBytes);
	HANDLE_PACKET_READ(ReadFloat,  m_Rotation, TotalBytes);
	HANDLE_PACKET_READ(ReadFloat,  m_Pitch,    TotalBytes);
	HANDLE_PACKET_READ(ReadBool,   m_bFlying,  TotalBytes);
	return TotalBytes;
}





void cPacket_PlayerMoveLook::Serialize(AString & a_Data) const
{
	AppendByte	(a_Data, m_PacketID);
	AppendDouble(a_Data, m_PosX);
	AppendDouble(a_Data, m_PosY);
	AppendDouble(a_Data, m_Stance);
	AppendDouble(a_Data, m_PosZ);
	AppendFloat	(a_Data, m_Rotation);
	AppendFloat	(a_Data, m_Pitch);
	AppendBool	(a_Data, m_bFlying);
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cPacket_PlayerPosition:

cPacket_PlayerPosition::cPacket_PlayerPosition( cPlayer* a_Player )
{
	m_PacketID = E_PLAYERPOS;

	m_PosX = a_Player->GetPosX();
	m_PosY = a_Player->GetPosY() + 1.65;
	m_PosZ = a_Player->GetPosZ();
	m_Stance = a_Player->GetStance();
	m_bFlying = a_Player->GetFlying();
}





int cPacket_PlayerPosition::Parse(const char * a_Data, int a_Size)
{
	int TotalBytes = 0;
	HANDLE_PACKET_READ(ReadDouble, m_PosX,    TotalBytes);
	HANDLE_PACKET_READ(ReadDouble, m_PosY,    TotalBytes);
	HANDLE_PACKET_READ(ReadDouble, m_Stance,  TotalBytes);
	HANDLE_PACKET_READ(ReadDouble, m_PosZ,    TotalBytes);
	HANDLE_PACKET_READ(ReadBool,   m_bFlying, TotalBytes);
	return TotalBytes;
}





void cPacket_PlayerPosition::Serialize(AString & a_Data) const
{
	AppendByte	 (a_Data, m_PacketID);
	AppendDouble (a_Data, m_PosX);
	AppendDouble (a_Data, m_PosY);
	AppendDouble (a_Data, m_Stance);
	AppendDouble (a_Data, m_PosZ);
	AppendBool	 (a_Data, m_bFlying);
}




