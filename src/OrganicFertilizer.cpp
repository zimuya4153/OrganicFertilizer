#include "OrganicFertilizer.h"
#include "Config.h"

#include <ll/api/Config.h>
#include <ll/api/event/Event.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/Listener.h>
#include <ll/api/event/player/PlayerSneakEvent.h>
#include <ll/api/mod/RegisterHelper.h>
#include <ll/api/service/Bedrock.h>
#include <mc/world/actor/Actor.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/attribute/AttributeInstance.h>
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/Level.h>
#include <mc/world/level/block/Block.h>
#include <mc/world/level/levelgen/structure/BoundingBox.h>
#include <memory>

OrganicFertilizer::Config config;

namespace OrganicFertilizer {

static std::unique_ptr<Entry> instance;

ll::event::ListenerPtr playerSneakEventListener;

Entry& Entry::getInstance() { return *instance; }

bool Entry::load() {
    auto path = getSelf().getConfigDir() / "config.json";
    try {
        if (!ll::config::loadConfig(config, path)) {
            ll::config::saveConfig(config, path);
        }
    } catch (...) {
        ll::config::saveConfig(config, path);
    }
    return true;
}

bool Entry::enable() {
    playerSneakEventListener = ll::event::EventBus::getInstance().emplaceListener<ll::event::PlayerSneakingEvent>(
        [](ll::event::PlayerSneakingEvent& event) {
            auto& player          = event.self();
            auto  hungerAttribute = player.getMutableAttribute(Player::HUNGER);
            auto& blockSource     = const_cast<BlockSource&>(player.getDimensionBlockSourceConst());
            auto  pos             = player.getFeetBlockPos();
            BoundingBox{-(config.range), config.range}.forEachPos(
                [&player, &hungerAttribute, &blockSource, &pos](BlockPos const& dPos) {
                    if (!player.isCreative() && hungerAttribute->getCurrentValue() < config.hunger) return false;
                    auto  newPos = pos.add(dPos);
                    auto& block  = blockSource.getBlock(newPos);
                    if (std::count(config.blacklist.begin(), config.blacklist.end(), block.getTypeName()) != 0
                        || !block.canBeFertilized(blockSource, newPos, block)) {
                        return true;
                    }
                    if (block.onFertilized(blockSource, newPos, nullptr, (FertilizerType)0)) {
                        if (!player.isCreative()) {
                            hungerAttribute->setCurrentValue(hungerAttribute->getCurrentValue() - config.hunger);
                        }
                        ll::service::getLevel()
                            ->spawnParticleEffect(config.particle, newPos.bottomCenter(), &player.getDimension());
                    }
                    return true;
                }
            );
        }
    );
    return true;
}

bool Entry::disable() {
    ll::event::EventBus::getInstance().removeListener(playerSneakEventListener);
    return true;
}

bool Entry::unload() {
    ll::event::EventBus::getInstance().removeListener(playerSneakEventListener);
    return true;
}

} // namespace OrganicFertilizer

LL_REGISTER_MOD(OrganicFertilizer::Entry, OrganicFertilizer::instance);