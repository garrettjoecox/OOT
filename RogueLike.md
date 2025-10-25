# Game Design Document
The gist of this idea is you play through the game similar to a randomizer, fulfilling the objectives to reach and beat Ganon, but instead of getting items from checks, they are granted with a leveling/reward system. Among other things like buffs and debuffs.

## Starting out UX
When beginning a game, you will have multiple randomly rolled selections to make, including a starting buff, starting location, starting item, starting song

## Gameplay
In addition to the normal gameplay experience, you will constantly be fighting monsters outside of safe locations like the Market or Kakariko Village. Killing monsters and hitting what would normally be considered randomizer checks will grant you XP, upon leveling up you will be granted additional buffs, items, and health.

## Difficulty Scaling
The main thing that will scale is enemy health & damage to link. Difficulty will increase with each boss defeated, as well as increasing at a set time increment after not defeating a boss for too long.

## Permanent progression
As you continue playing, the idea is you would very slowly gain a currency to grant you very small bonuses that will benefit you in every following run. Starting health is an example of a potential purchase-able thing.

## Technical Components TODO:
- ImGui Overlay to place persistent UI elements (XP bar, difficulty timer, etc)
- ImGui Prompt to randomly roll an item (slot machine-like interface)
- ImGui Prompt to select between 3 different buffs
- Unified way to scale incoming/outgoing damage and enemy health across all enemies in the game (bosses separate cause they are finicky)
- Weighted list of XP amounts to grant for every check and enemy. For instance you shouldn't get that much XP for opening chests in Mido's house, but doing frog song minigame is huge. 
