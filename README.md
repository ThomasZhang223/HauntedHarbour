
All_projects.pdf
PDF
ThomasZhang223/HauntedHarbour
main
GITHUB
Analyze how each project was described in the following resume style. Please analyze this c++ game project and do the same. Requirements are three lines, focusing on core technologies, algorithms, architecture or design philosophy, and technical elements. Be descriptive without being verbose, use STAR method to clearly outline why use a technology then impact. Also generate a short but concise read_me for the project that explains the general game
9:46 PM

Dissected game architecture and synthesized resume-style technical descriptions.
17s
Looking at the code structure, I can analyze the technical elements of this 2D side-scrolling shooter game. Let me create the resume bullets and README.
Resume Description
HauntedHarbour | C++, Win32 GDI, ATL
Developed 2D side-scrolling platformer using Win32 GDI with double-buffered rendering pipeline, implementing OOP inheritance hierarchy (GraphicsObject → WeaponsObject → PlayerObject/EnemyObject) with polymorphic enemy behaviors for extensible game entity management
Engineered AABB collision detection system with directional resolution logic using previous-frame position tracking to determine collision side, enabling proper physics responses including entity pushing, platform landing, and wall blocking for both player and AI entities
Implemented parallax scrolling background system with configurable scroll speeds, finite state machine for 8-state player control (movement, jumping, shooting), object pooling pattern for projectile management, and text-based level parser for dynamic map loading with support for multiple entity types
README

2 steps

Presented file

Synthesized resume framework and documentation strategy.
Here's the resume-style description and README for your HauntedHarbour project.
Resume Bullets:
HauntedHarbour | C++, Win32 GDI, ATL
Developed 2D side-scrolling platformer using Win32 GDI with double-buffered rendering pipeline, implementing OOP inheritance hierarchy (GraphicsObject → WeaponsObject → PlayerObject/EnemyObject) with polymorphic enemy behaviors for extensible game entity management
Engineered AABB collision detection system with directional resolution logic using previous-frame position tracking to determine collision side, enabling proper physics responses including entity pushing, platform landing, and wall blocking for both player and AI entities
Implemented parallax scrolling background system with configurable scroll speeds, finite state machine for 8-state player control (movement, jumping, shooting), object pooling pattern for projectile management, and text-based level parser for dynamic map loading with support for multiple entity types
The README covers gameplay, controls, technical architecture (class hierarchy diagram), build requirements, and the level file format for your text-based map system.
Hauntedharbour readme
Document · MD 




Claude is AI and can make mistakes. Please double-check responses.


Hauntedharbour readme · MD
Copy

HauntedHarbour
A 2D side-scrolling action platformer built with C++ and the Windows GDI API.
Overview
HauntedHarbour is a classic-style shooter where players control Viktor Tesla, navigating through haunted harbor environments while battling supernatural enemies. The game features smooth parallax scrolling, projectile combat, and multiple enemy types with distinct AI behaviors.
Gameplay
Movement: Arrow keys to move left/right and jump
Combat: Spacebar to fire projectiles
Objective: Survive enemy encounters while navigating through the level
Features
Player Character: Viktor Tesla with 8 animation states (walking, standing, jumping, shooting) in both directions
Enemy Types:
Ground Enemies (SkullCrab): Patrol horizontally, reverse direction on obstacles, fire projectiles randomly
Flying Enemies (SeaHag): Orbit in circular patterns, track player position, fire aimed projectiles
Physics: Gravity-based movement with platform collision and entity pushing
Health System: Visual life bar with damage feedback and respawn on death
Level System: Text-based level files for easy map creation and modification
Technical Architecture
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
Build Requirements
Windows OS
Visual Studio 2019+ with Windows SDK
C++14 or later
Level File Format
Levels are defined in /Levels/LevelX.txt with sections:
[Viktor]
0 100 100

[Little-Block]
0 200 350
-1 0 0

[Ground-Enemy]
0 400 200
-1 0 0

[End]
Controls
Key	Action
← →	Move left/right
↑	Jump
Space	Shoot
Enter	Start game
Assets
Place sprite sheets and images in the /pics directory:
ViktorTesla.bmp - Player sprite sheet
SkullCrab.bmp - Ground enemy sprites
SeaHag.bmp - Flying enemy sprites
Background3.jpg - Parallax background
Ground.bmp - Ground tiles
