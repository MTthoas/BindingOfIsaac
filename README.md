# Binding Of Isaac

This game is a simple rpg game written in C.<br>

## Dependencies

- [Git]
- C Compiler (gcc, ...)
- [CMake]

**On Debian/Ubuntu based distributions, use the following command:**

```sh
sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev libsdl2-gfx-dev
```

## Build instructions

```sh
# Clone this repo
git clone https://github.com/MTthoas/BindingOfIsaac.git
cd BindingOfIsaac
```

## Create a build folder
```sh
mkdir bin
cd bin
```

## Build
```sh
cmake ..
make
```

## Run
```sh
./BindingOfIsaac
```


