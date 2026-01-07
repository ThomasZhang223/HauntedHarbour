# HauntedHarbour

A 2D side-scrolling action platformer built with C++ and the Windows GDI API.

## Overview

HauntedHarbour is a classic-style shooter where players control Viktor Tesla, navigating through haunted harbor environments while battling supernatural enemies. The game features smooth parallax scrolling, projectile combat, and multiple enemy types with distinct AI behaviors.

## Gameplay

- **Movement**: Arrow keys to move left/right and jump
- **Combat**: Spacebar to fire projectiles
- **Objective**: Survive enemy encounters while navigating through the level

## Features

- **Player Character**: Viktor Tesla with 8 animation states (walking, standing, jumping, shooting) in both directions
- **Enemy Types**:
  - *Ground Enemies (SkullCrab)*: Patrol horizontally, reverse direction on obstacles, fire projectiles randomly
  - *Flying Enemies (SeaHag)*: Orbit in circular patterns, track player position, fire aimed projectiles
- **Physics**: Gravity-based movement with platform collision and entity pushing
- **Health System**: Visual life bar with damage feedback and respawn on death
- **Level System**: Text-based level files for easy map creation and modification

## Technical Architecture

```
GraphicsObject (Base rendering class)
├── BackgroundObject (Parallax scrolling layers)
└── WeaponsObject (Entities with projectile capability)
    ├── PlayerObject (Player-controlled character)
    └── EnemyObject (Abstract enemy base)
        ├── GroundEnemy (Patrol AI)
        └── FlyingEnemy (Tracking AI)

BulletObject (Base projectile class)
├── PurpleBullet (Player projectiles)
└── GreenBullet (Enemy projectiles)
```

## Build Requirements

- Windows OS
- Visual Studio 2019+ with Windows SDK
- C++14 or later

## Level File Format

Levels are defined in `/Levels/LevelX.txt` with sections:
```
[Viktor]
0 100 100

[Little-Block]
0 200 350
-1 0 0

[Ground-Enemy]
0 400 200
-1 0 0

[End]
```

## Controls

| Key | Action |
|-----|--------|
| ← → | Move left/right |
| ↑ | Jump |
| Space | Shoot |
| Enter | Start game |

## Assets

Place sprite sheets and images in the `/pics` directory:
- `ViktorTesla.bmp` - Player sprite sheet
- `SkullCrab.bmp` - Ground enemy sprites
- `SeaHag.bmp` - Flying enemy sprites
- `Background3.jpg` - Parallax background
- `Ground.bmp` - Ground tiles
