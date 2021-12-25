#include "Config.h"
#include "Player.h"
#include "ScriptMgr.h"

uint32 multiplier[3];

class DynamicRatesPlayer : public PlayerScript
{
    public:
        DynamicRatesPlayer() : PlayerScript("DynamicRatesPlayer") {}

        void OnGiveXP(Player* player, uint32& amount, Unit* /*victim*/) override
        {
            if (player->getLevel() < 60)
            {
                amount *= multiplier[0];
            }
            else if (player->getLevel() < 70)
            {
                amount *= multiplier[1];
            }
            else if (player->getLevel() < 80)
            {
                amount *= multiplier[2];
            }
        }

        void OnReputationChange(Player* player, uint32 /*factionId*/, int32& standing, bool /*incremental*/) override
        {
            if (player->getLevel() < 60)
            {
                standing *= multiplier[0];
            }
            else if (player->getLevel() < 70)
            {
                standing *= multiplier[1];
            }
            else if (player->getLevel() < 80)
            {
                standing *= multiplier[2];
            }
        }
};

class DynamicRatesWorld : WorldScript
{
    public:
        DynamicRatesWorld() : WorldScript("DynamicRatesWorld") {}

        void OnAfterConfigLoad(bool /*reload*/) override
        {
            multiplier[0] = sConfigMgr->GetOption<int32>("DynamicRate.Level.1-59", 3);
            multiplier[1] = sConfigMgr->GetOption<int32>("DynamicRate.Level.60-69", 2);
            multiplier[2] = sConfigMgr->GetOption<int32>("DynamicRate.Level.70-79", 1);
        }
};

void AddDynamicRatesScripts()
{
    new DynamicRatesPlayer();
    new DynamicRatesWorld();
}
