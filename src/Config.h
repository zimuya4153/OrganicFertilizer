#include <string>
#include <vector>

namespace OrganicFertilizer {
struct Config {
    int                      version  = 1;                         // 配置文件版本
    float                    hunger   = 1.0f;                      // 催熟成功减少的饥饿值
    unsigned char            range    = 5;                         // 催熟范围
    std::string              particle = "minecraft:soul_particle"; // 催熟的粒子效果
    std::vector<std::string> blacklist =
        {"minecraft:grass_block", "minecraft:short_grass", "minecraft:fern"}; // 催熟黑名单
};
} // namespace OrganicFertilizer