#include "ScriptPCH.h"
#include "Chat.h"

using namespace std;

uint32 auras[] = { 48162, 48074, 48170, 43223, 36880, 467, 48469 };

class commands : public CommandScript
{
public:
	commands() : CommandScript("buffcommand") { }

	vector<ChatCommand> GetCommands() const override
	{
		static vector<ChatCommand> IngameCommandTable =
		{
			{ "buff",	SEC_PLAYER,	true,	&HandleBuffCommand,	"" },
			{ "chat",	SEC_PLAYER,	true,	&HandleChatCommand,	"" },
			{ NULL,		0,			false,	NULL,				""}
		};
		return IngameCommandTable;
	}

	// Buff Script
	static bool HandleBuffCommand(ChatHandler * handler, const char * args)
	{
		Player * pl = handler->GetSession()->GetPlayer();
		if (pl->InArena())
		{
			pl->GetSession()->SendNotification("You can't use that item in an arena match!");
			return false;

		}else if(pl->InBattleground()){

			pl->GetSession()->SendNotification("You can't use that item in an battleground!");
			return false;

		}else if (pl->IsInCombat())
		{
			pl->GetSession()->SendNotification("You can't use that item in an battleground!");
			return false;
		}
		else {
			pl->RemoveAurasByType(SPELL_AURA_MOUNTED);
			for (int i = 0; i < 7; i++)
				pl->AddAura(auras[i], pl);
			handler->PSendSysMessage("|cffB400B4You have been buffed, enjoy!");
			return true;
		}
	}

	// Chat Script
	static bool HandleChatCommand(ChatHandler * handler, const char * args)
	{
		if (!args)
			return false;

		string msg = "";
		Player * player = handler->GetSession()->GetPlayer();

		switch (player->GetSession()->GetSecurity())
		{
		case SEC_PLAYER:
			// Player -- GM level 0
				if (player->GetTeam() == ALLIANCE)
				{
					msg += "|cff00FFFB[Alera]|cff0000EE[Alliance]|cff00CD00[";
					msg += player->GetName();
					msg += "]:|cffffffff ";
				}

			if (player->GetTeam() == HORDE)
			{
				msg += "|cff00FFFB[Alera]|cffCC1100[Horde]|cff00CD00[";
				msg += player->GetName();
				msg += "]:|cffffffff ";
			}
			break;

			// VIP -- GM level 1
		case SEC_VIP:
			if (player->GetTeam() == ALLIANCE)
			{
				msg += "|cff00FFFB[Alera]|cff0000EE[Alliance]|cff800080[VIP]|cff00CD00[";
				msg += player->GetName();
				msg += "]:|cffffffff ";
			}

			if (player->GetTeam() == HORDE)
			{
				msg += "|cff00FFFB[Alera]|cffCC1100[Horde]|cff800080[VIP]|cff00CD00[";
				msg += player->GetName();
				msg += "]:|cffffffff ";
			}
			break;

			// Moderator -- GM level 2
		case SEC_MODERATOR:
			msg += "|cff00FFFB[Alera]|cffEEB422[Moderator]|cff00CD00[";
			msg += player->GetName();
			msg += "]:|cffffffff ";
			break;

			// Gamemaster -- GM level 3
		case SEC_GAMEMASTER:
			msg += "|cff00FFFB[Alera]|cffF0A804[Gamemaster]|cff00CD00[";
			msg += player->GetName();
			msg += "]:|cffffffff ";
			break;

			// Head GM -- GM level 4
		case SEC_ADMINISTRATOR:
			msg += "|cff00FFFB[Alera]|cffFF0000[Administrator]|cff00CD00[";
			msg += player->GetName();
			msg += "]:|cffffffff ";
			break;

			//Owner -- GM level 5
		case SEC_CONSOLE:
			msg += "|cff00FFFB[Alera]|cffFF0000[Owner]|cff00CD00[";
			msg += player->GetName();
			msg += "]:|cffffffff ";
			break;

		}

		msg += args;
		sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);

		return true;
	}


};

void AddSC_commands()
{
	new commands();
}