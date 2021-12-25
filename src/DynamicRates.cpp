#include "Config.h"
#include "Player.h"
#include "ScriptMgr.h"

uint32 multiplierExperience[3];
uint32 multiplierReputation[3];

class DynamicRatesPlayer : public PlayerScript
{
    public:
        DynamicRatesPlayer() : PlayerScript("DynamicRatesPlayer") {}

        void OnGiveXP(Player* player, uint32& amount, Unit* /*victim*/) override
        {
            if (player->getLevel() < 60)
            {
                amount *= multiplierExperience[0];
            }
            else if (player->getLevel() < 70)
            {
                amount *= multiplierExperience[1];
            }
            else if (player->getLevel() < 80)
            {
                amount *= multiplierExperience[2];
            }
        }

        void OnReputationChange(Player* player, uint32 /*factionId*/, int32& standing, bool /*incremental*/) override
        {
            if (player->getLevel() < 60)
            {
                standing *= multiplierReputation[0];
            }
            else if (player->getLevel() < 70)
            {
                standing *= multiplierReputation[1];
            }
            else if (player->getLevel() < 80)
            {
                standing *= multiplierReputation[2];
            }
        }
};

class DynamicRatesWorld : WorldScript
{
    public:
        DynamicRatesWorld() : WorldScript("DynamicRatesWorld") {}

        void OnAfterConfigLoad(bool /*reload*/) override
        {
            multiplierExperience[0] = sConfigMgr->GetOption<int32>("DynamicRate.Experience.1-59", 3);
            multiplierExperience[1] = sConfigMgr->GetOption<int32>("DynamicRate.Experience.60-69", 2);
            multiplierExperience[2] = sConfigMgr->GetOption<int32>("DynamicRate.Experience.70-79", 1);

            multiplierReputation[0] = sConfigMgr->GetOption<int32>("DynamicRate.Reputation.1-59", 3);
            multiplierReputation[1] = sConfigMgr->GetOption<int32>("DynamicRate.Reputation.60-69", 2);
            multiplierReputation[2] = sConfigMgr->GetOption<int32>("DynamicRate.Reputation.70-79", 1);
        }
};

void AddDynamicRatesScripts()
{
    new DynamicRatesPlayer();
    new DynamicRatesWorld();
}
