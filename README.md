# Gomoku_SFML

play gomoku built with SFML(#Graphic_Library #AI)

## Game Screen

![Start Menu Image](https:://github.com/GatsLee/Gomoku_SFML/blob/main/doc/startMenu.png?raw=true)

## Objective

---

- to build Gomoku with multi media library(SFML)
- to utilize various algorithm as an opponent for user

## Game Flow

---

![Gomoku Game Flow](https::/github.com/GatsLee/Gomoku_SFML/blob/main/doc/gameFlow.png?raw=true)

## How to play

---

### 1. execute init.sh to clone my repo & install SFML

- because this game has a dependency on SFML, you have to install SFML with this
- I include both cloning my repo & installing SFML in the shellscript, so you can just copy & paste the command below

```shell
 bash -c "$(curl-fsSL https://raw.github.com/GatsLee/Gomoku_SFML/main/init.sh)"
```

### 2. build the game

- you can now build Gomoku with makefile in root of the directory

```shell
make -C Gomoku_SFML all
```

## Further

- The game can only be built in Unix-like OS for now. So, I will work on the Windows Build system later
- I'm going to make multiplayer using TCP socket communication

## Thanks to

- @jeekpark : I took many references related to SFML & build process from him
