# game-of-life

### Where will the executable find resource files it loads?

- When the executable is generated within the build tree, it will load resources locally from the project's assets directory.

- When the executable is installed to a standard system location such as ```usr/local/bin```, it needs to load resources from another standard location such as ```use/local/share/GameLife/assets/``` to ensure the resources will always be avaialable.


CMake files and explanation based on 
https://dane-bulat.medium.com/cmake-building-sfml-and-game-projects-on-linux-3947b3ba6e8

