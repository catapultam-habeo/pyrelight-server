#include "../client.h"
#include <map>
#include <functional>

void command_filterheroic(Client *c, const Seperator *sep)
{
	const auto arguments = sep->argnum;
    if (!arguments) {
        c->Message(Chat::White, "Command Syntax: #[filterheroic] - [str|sta|dex|agi|int|wis|cha] [on|off (optional)] - Set or toggle the visibility of additional info about heroic stat effects.");
        return;
    } else {
		LogDebug("[{}] [{}] [{}]", sep->arg[0], sep->arg[1], sep->arg[2]);

        std::map<std::string, std::function<void()>> statMap = {
			{"str", [&](){ 
				if (Strings::ToLower(sep->arg[2]) == "on") {
					c->SetAccountFlag("filter_hSTR_" + c->GetID(), "on");
				} else if (Strings::ToLower(sep->arg[2]) == "off") {
					c->SetAccountFlag("filter_hSTR_" + c->GetID(), "off");
				} else {
					//toggle flag
					std::string currentFlag = c->GetAccountFlag("filter_hSTR_" + c->GetID());
					if (currentFlag == "off" || currentFlag.empty()) {
						c->SetAccountFlag("filter_hSTR_" + c->GetID(), "on");
					} else {
						c->SetAccountFlag("filter_hSTR_" + c->GetID(), "off");
					}
				}
			}},
            {"sta", [](){ /* handle case STA */ }},
            {"dex", [](){ /* handle case DEX */ }},
            {"agi", [](){ /* handle case AGI */ }},
            {"int", [](){ /* handle case INT */ }},
            {"wis", [](){ /* handle case WIS */ }},
            {"cha", [](){ /* handle case CHA */ }}
        };

        auto statFunction = statMap.find(Strings::ToLower(sep->arg[1]));

        if (statFunction != statMap.end()) {
            statFunction->second();
        } else {
            c->Message(Chat::White, "Command Syntax: #[filterheroic] - [str|sta|dex|agi|int|wis|cha] [on|off (optional)] - Set or toggle the visibility of additional info about heroic stat effects.");
        }
    }
}