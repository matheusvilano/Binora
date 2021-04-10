# GAME DESIGN DOCUMENT

## Title
Binora

## Author
Matheus Vilano

## Team

### [Matheus Vilano](https://www.matheusvilano.com/) 
- Game Designer
- Programmer
- Audio Artist

### [Arisa Lutic-Hotta](https://www.arisalutichotta.com/)
- Audio Artist
- Level Designer

### [Connor Staton](https://www.cjs-audio.com)
- Audio Artist
- Level Designer

### Ericka Florencia
- Audio Artist
- Level Designer

## Jam

### Name
[“No Video Game 2”](https://itch.io/jam/no-video-jam-2)

### Rules
* Sound is the focus.
* Visuals should not be necessary for gameplay.

## Tools
* Unreal Engine 4
* FMOD Studio 2

## Concept
The player will listen to a fully-designed ambience for N time. After that, the sounds will fade away, and the player needs to rebuild the soundscape.

## Gameplay

### Mechanics

#### Volume
Defined via FMOD Spatializer / Attenuation (mostly affected by the X axis). Float comparison (with FMOD Parameters). The closer to the original value, the higher the score. An announcer (non-spatialized) will announce performance/score.

#### Panning
Defined via FMOD Spatializer (positioning; mostly affected by the Y axis). 

#### Scoring 
Three trigger spheres

| Score (Numeric) | Score (Categorical) | Trigger Position |
|:---------------:|:------------------- |:---------------- |
| 3               | Perfect             | Innermost        |
| 2               | Great               | Middle           |
| 1               | Good                | Outermost        |
| 0               | Miss                | N/A              |

#### Controls

##### Gamepad

| Action / Axis               | Mapping (String)    | Control / Mechanic                      |
|:--------------------------- |:------------------- |:--------------------------------------- |
| Left/Right Thumbstick Y     | "Volume"            | Up = Quieter                            |
| Left/Right Thumbstick X     | “Panning”           | Right = R                               |
| Face Buttons                | “SelectEmitterN”    | One per button (4 in total)             |
| D-Pad Buttons               | “SelectSpecN”       | One per key (4 in total)                |
| Left/Right Trigger/Shoulder | “SelectBackgroundN” | One per trigger and should (4 in total) |

##### Keyboard & Mouse

TBD

## Naming Convention

### Asset Names

Format: ALLCAPS_PascalCase
Pattern: TYPE_AssetName

### Variable Names

| Object Type | Convention   |
|:-----------:|:------------ |
| Classes     | UClassName   |
| Enums       | TYPE_Name    |
| Functions   | FunctionName |
| Properties  | VariableName |
| Structs     | UStructName  |
| Other       | OtherName    |

### Types & Identifiers

#### Audio
* BG = Background
* EM = Emitter
* SP = Spec(ific)
* UI = User Interface

#### Art
* TX = Texture

#### Code
* BP = Blueprint
* CPP = C++
* WBP = Widget Blueprint
* GM = Game Mode
* GS = Game State
* GI = Game Instance
* PC = Player Controller
* PS = Player State

## Audio Format

| Category       | Amount of Channels | Behaviour | Length (Range in Minutes) | Maximum Amount Per Level |
|:-------------- |:------------------ |:--------- |:-------------------------:|:------------------------ |
| Backgrounds    | 2 (True Stereo)    | Loop      | 2-5                       | 2                        |
| Emitters       | 1 (True Mono)      | Loop      | 1-2                       | 4                        |
| Spec(ifics)    | 1 (True Mono)      | Oneshot   | N/A                       | 4                        |
| User Interface | 2 (True Stereo)    | Oneshot   | N/A                       | N/A                      |
| Music          | 2 (True Stereo)    | Loop      | 2-5                       | N/A                      |

* Sample Rate: 48kHz
* Bit Depth:   24bit