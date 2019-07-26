# AbyssEngine
Game engine to be used for upcoming game Abysswalker.

The purpose of the project is to gain experience with creating a fully fleshed out
project that can give a broader understanding of programming.

Dependencies: GLEW, GLFW, FreeImage, FreeType.

## Features
* **Graphics**
    * OpenGL
    * 3D ~~and 2D~~
    * Currently supports drawing
      * Sprites (Using single textures or texture atlas)
      * Text
      * Polygons
      * Lines
      * Points
* **~~Collision & Physics~~**
    * ~~Broad-phase~~
    * ~~Narrow-phase~~
* **~~Audio~~**
* **Entity-Component-System (ECS)**
    * A Data-Oriented architectural pattern that favours composition over inheritance.
    * Entities are solely defined by the components it exists of, and are identified by an entityId which it
s components stores.
    * Components are logicless data objects stored continuously in memory in the entitymanager.
    * Events are components that have a limited lifetime and can be used to broadcast information.
    * [More information](https://github.com/jonaskris/EntitySystem)
* **Resource Loading**
    * Resources are all loaded on program start and kept in memory for the entirety of the session.
    * Textures are loaded using [FreeImage](https://github.com/imazen/freeimage).
    * Fonts are loaded using [FreeType](https://www.freetype.org/).
    
* **Input**
    * Keyboard and mouse.
    * ~~Controller~~
## Usage
