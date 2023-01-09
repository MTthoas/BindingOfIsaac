# Binding Of Isaac

This game is a simple rpg game written in C.<br>

## DOCKER 

```sh
FROM  debian:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    gcc \
    pkg-config \
    cmake-data
WORKDIR /app 
RUN git clone https://github.com/MTthoas/BindingOfIsaac.git
WORKDIR /app/BindingOfIsaac/build
RUN cmake ..
RUN make

CMD ["./BindingOfIsaac"]

```


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


