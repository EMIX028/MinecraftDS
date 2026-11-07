# SPDX-License-Identifier: CC0-1.0
# SPDX-FileContributor: Antonio Niño Díaz, 2024

BLOCKSDS	?= /opt/blocksds/core

# User config

NAME			:= MinecraftDS
GAME_TITLE		:= Minecraft DS Edition
GAME_SUBTITLE	:= Made by EMIX
GAME_AUTHOR     := https://github.com/EMIX028/MinecraftDS

GAME_ICON       := Icon.gif

INCLUDEDIRS := include
GFXDIRS := graphics

CFLAGS  += -fverbose-asm -O2 -ffunction-sections -fdata-sections -g
LDFLAGS += -Wl,--gc-sections

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile


.PHONY: disassemble

disassemble: build/MinecraftDS.elf
	/opt/wonderful/toolchain/gcc-arm-none-eabi/bin/arm-none-eabi-objdump.exe -d -S $< > build/MinecraftDS.s