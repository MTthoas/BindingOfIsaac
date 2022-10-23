# BindingOfIsaac

BindingOfIsaac game written in C.<br>

It uses the [SDL2][SDL] library to render graphics and uses [CMake][] as a bin system.<br>

## Dependencies

- [Git][]
- C Compiler (gcc, ...)
- [CMake][]
- [SDL2][SDL] library
- [SDL2_gfx][] library

**On Debian/Ubuntu based distributions, use the following command:**

```sh
sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev libsdl2-gfx-dev
```

**Optional packages:**

- [SDL2_image][] library
- [SDL2_ttf][] library
- [SDL2_net][] library
- [SDL2_mixer][] library

```sh
sudo apt install libsdl2-image-dev libsdl2-ttf-dev libsdl2-net-dev libsdl2-mixer-dev
```

## bin instructions

```sh
# Clone this repo
git clone https://github.com/MTthoas/BindingOfIsaac.git
cd BindingOfIsaac

# Create a bin folder
mkdir bin
cd bin

# bin
cmake ..
make

# Run
./BindingOfIsaac
```

## License

Author: Pecquery Matthias [@MTthoas](https://github.com/MTthoas/)

CMake SDL biner Contributors : ext/sdl2/Copyright

This project is distributed under the terms of the MIT license


[SDL]: https://www.libsdl.org
[CMake]: https://cmake.org
[Git]: https://git-scm.com
[SDL2_image]: https://www.libsdl.org/projects/SDL_image
[SDL2_ttf]: https://www.libsdl.org/projects/SDL_ttf
[SDL2_net]: https://www.libsdl.org/projects/SDL_net
[SDL2_mixer]: https://www.libsdl.org/projects/SDL_mixer
[SDL2_gfx]: http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx
