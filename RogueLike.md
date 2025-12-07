# Game Design Document
The gist of this idea is you play through the game similar to a randomizer, fulfilling the objectives to reach and beat Ganon, but instead of getting items from checks, they are granted with a leveling/reward system. Among other things like buffs and debuffs.

## Starting out UX
When beginning a game, you will have multiple randomly rolled selections to make, including a starting location, starting item, starting song

## Gameplay
As you progress through the game, you will be rewarded XP for doing various actions throughout the world. When you have enough XP you will level up and you will be presented with a selection of buffs, items, or other rewards to choose from to enhance your character for the rest of the run. Actions include interacting with things, breaking things, killing enemies, talking with NPCs and completing their quests, etc. 

TODO:
- Health upgrades not implemented
- Defense doesn't do anything yet (maybe damage mitigation?)
- Speed doesn't do anything yet (will effect movement speed of bunny hood)
- Quests system in early stages, only two quests currently
- Don't have a global enemy spawning mechanism yet, just relying on existing enemy spawn points
- Not all checks have been replaced with XP rewards yet
- Not sure what to do about ammo yet
- Not sure what to do about shops yet
- Weighted list of XP amounts to grant for every check and enemy. For instance you shouldn't get that much XP for opening chests in Mido's house, but doing frog song minigame is huge etc

## Difficulty Scaling
The main thing that will scale is enemy health & damage to link. Difficulty increases in levels, it will increase each time you kill a major boss, and there will also be a timer that eventually increases your difficulty based on time spent not gaining any experience.

TODO:
- Damage to link scaling not implemented yet
- Defeating bosses to increase difficulty not implemented yet
- Hyper enemies / enemy size scaling could play into this?

## Permanent progression
As you continue playing, the idea is you would very slowly gain a currency to grant you very small bonuses that will benefit you in every following run. Starting health is an example of a potential purchase-able thing, or starting with ocarina or bunny hood. It's likely that this currency would be earned from killing bosses and completing quests

TODO:
- Permanent progression system not implemented yet

## Ideas:
- Lock the player in certain areas to spawn specified waves of enemies before the player can proceed? i.e Hyrule Field or places without a Clear Room
- Utilize the trick from MM to hide/unhide Inventory Items based on what is earned?
- Ammo could have a timed regen based on upgrades? For instance you can only hold 1 stick, and if you break it, it regens after 5 minutes, unless you get an upgrade to hold 2 sticks, then it regens after 4 minutes, etc