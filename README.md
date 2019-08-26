# AbyssEngine

The purpose of the project is to gain experience with creating a fully fleshed out
project that can give a broader understanding of programming.

Dependencies: GLEW, GLFW, SOIL, FreeType and Nlohmann's JSON library.

## Features
* **Graphics**
    * Deferred rendering with OpenGL
    * 3D ~~and 2D~~
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
    * Supports setting default resources per type that are returned if the requested resource was not found.
    * Textures are loaded using [SOIL](https://www.lonesock.net/soil.html).
    * Fonts are loaded using [FreeType](https://www.freetype.org/).
    * JSON is loaded using [nlohmann's JSON library](https://github.com/nlohmann/json).
* **Input**
    * Keyboard and mouse.
    * ~~Controller~~
## Usage
