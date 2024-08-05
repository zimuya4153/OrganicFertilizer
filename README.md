# OrganicFertilizer - 有机肥

## 简介
通过不断下蹲促使农作物快速生长，只要能被骨粉催熟的方块均可。
> 支持addon

## 配置文件
```json
{
    "version": 1, // 配置文件版本(勿动)
    "hunger": 1.0, // 催熟成功减少的饥饿值(浮点数)
    "range": 5, // 催熟范围(0-255的整数)
    "particle": "minecraft:soul_particle", // 催熟的粒子效果
    "blacklist": [ // 催熟黑名单
        "minecraft:grass_block", // 草方块
        "minecraft:short_grass", // 矮草丛
        "minecraft:fern" // 蕨
    ]
}
```

## 安装方法

- 手动安装
  - 前往[Releases](https://github.com/zimuya4153/OrganicFertilizer/releases)下载最新版本的`OrganicFertilizer-windows-x64.zip`
  - 解压`压缩包内的`文件夹到`./plugins/`目录
- Lip 安装
  - 输入命令`lip install -y github.com/zimuya4153/OrganicFertilizer`
- ~~一条龙安装~~
  - ~~去 Q 群，喊人，帮你安装~~