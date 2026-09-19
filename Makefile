# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

BLOCKSDS	?= /opt/blocksds/core

# User config

NAME			:= MinecraftDS
GAME_TITLE		:= Minecraft DS Edition
GAME_SUBTITLE	:= Made by EMIX
GAME_AUTHOR     := https://github.com/EMIX028/MinecraftDS

#GAME_ICON       := icon.gif

INCLUDEDIRS := include

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile
