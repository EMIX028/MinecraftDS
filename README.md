# Minecraft DS

Minecraft DS is a Minecraft Demake project for the Nintendo DS, written in C using **BlocksDS libs**.

> **A playable voxel-based technical demo running on Nintendo DS hardware.**
>
> The project explores how far a Minecraft-inspired game can be pushed on Nintendo DS hardware.

<img width="2558" height="1346" alt="v1.1a new features" src="https://github.com/user-attachments/assets/1689104c-7c6d-4448-9af2-c6fa3c14da59" />

## 🚧 Current Status

Minecraft DS is currently a **playable technical demo rather than a complete game**.

The current version focuses on:

- 3D voxel rendering
- Chunk-based world management
- Player movement and collision
- Block placement and breaking
- Multiple block types and orientations
- Texture transparency
- Basic HUD and performance information

More gameplay systems and technical improvements may be added in future versions.

## 💻 Compatibility

Minecraft DS is designed for Nintendo DS homebrew.

Currently tested on:

- Nintendo DS
- [melonDS](https://melonds.kuribo64.net/)
- [DeSmuMe](https://github.com/TASEmulators/desmume/)

> Compatibility with other Nintendo DS models and emulators may vary.

## 📥 Download

The latest playable version can be downloaded from the [Releases](../../releases) page.

The release contains the `.nds` ROM required to run Minecraft DS on compatible Nintendo DS hardware or an emulator.

If you want to build the source code, Minecraft DS requires **[BlocksDS](https://blocksds.skylyrac.net/)** toolkit.

## ⚙️ Technical

Current technical features include:

- Nintendo DS hardware 3D rendering
- Chunk-based world system
- Voxel block rendering
- Block face visibility culling
- Texture atlas
- Texture transparency
- Block orientation system
- Basic player collision
- Player position display

## ✨ Features

### 🌍 World

- Chunk-based voxel world
- Currently loaded area consisting of **4 chunks**
- Each chunk is **14 × 14 blocks**
- Maximum world height of **20 blocks**

### 🎮 Controls

| Button            | Action                    |
| ----------------- | ------------------------- |
| **D-Pad**         | Move the player           |
| **A / B / X / Y** | Control the camera        |
| **START**         | Reset & switch maps       |
| **SELECT**        | Pause the game            |
| **R**             | Place a block             |
| **L**             | Activate Special Mode     |
| **L + B**         | Jump                      |
| **L + R**         | Break a block             |
| **L + A / Y**     | Change the selected block |

### ✨ Special Mode

Holding **L** activates the **Special Mode**, allowing additional actions to be performed by combining it with other buttons:

- **L + B** → Jump
- **L + R** → Break the targeted block
- **L + A / Y** → Change the block selected for placement

### 🧱 Blocks

There are currently **19 block types** available:

- Dirt
- Grass
- Sand
- Stone
- Cobblestone
- Bedrock
- Moss
- Glass
- Oak Plank
- Oak Log
- Oak Leaves
- Obsidian
- Coal Ore
- Iron Ore
- Gold Ore
- Redstone Ore
- Diamond Ore
- Crafting Table
- Furnace

### 📊 HUD

The bottom screen displays useful gameplay and performance information:

- Game version
- Player position
- Selected block name
- Play time
- FPS

### 🎵 Music

The music currently played at startup is **Wet Hands**, composed by **C418** for Minecraft.

This music is a third-party asset and is not owned or created by this project. See the [NOTICE](NOTICE) file for attribution and additional information.

## Roadmap

Minecraft DS is still in early development. Future features I'm considering include:

- [ ] Expand the playable world
- [ ] Dynamic chunk loading
- [ ] World generation
- [ ] More blocks
- [ ] Inventory system
- [ ] Crafting
- [ ] Save / load system
- [ ] Additional gameplay mechanics
- [ ] Further performance improvements
- [ ] New HUD and interface
- [ ] Game icon

Some features listed here are experimental or may change as development progresses.

## Credits

- **Mojang Studios** — Creator of Minecraft.
- **C418** — Composer of _Wet Hands_.
- Third-party textures, music and other assets used by the project are not original assets created by this project.

See the [NOTICE](NOTICE) file for detailed attribution and legal information.

## 📜 License

The original source code of Minecraft DS is distributed under the **GNU General Public License v3.0**.

See the [LICENSE](LICENSE) file for the complete license.

Third-party assets are not necessarily covered by the project's source code license. See [NOTICE](NOTICE) for more information.

## ⚠️ Disclaimer

Minecraft DS is an **unofficial, fan-made homebrew project** and is not affiliated with, endorsed by, or sponsored by **Mojang Studios, Microsoft, or Nintendo**.

Minecraft and related trademarks belong to their respective owners.

See the [NOTICE](NOTICE) file for additional information regarding third-party assets and attribution.
