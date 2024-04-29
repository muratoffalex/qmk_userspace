# Copyright 2019 Manna Harbour
# https://github.com/manna-harbour/miryoku

# SRC += $(USER_PATH)/main.c
# INTROSPECTION_KEYMAP_C = main.c

# mouse keys
MOUSEKEY_ENABLE = yes
# Audio control and System control
EXTRAKEY_ENABLE = yes
# auto shift keys (shift on hold)
AUTO_SHIFT_ENABLE = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
# for realize CAPS on shift + cw_togg (caps word toggle)
KEY_OVERRIDE_ENABLE = yes
COMBO_ENABLE = yes

RGBLIGHT_ENABLE = no

# firmware size optimization
LTO_ENABLE = yes
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
AUDIO_ENABLE = no
BOOTMAGIC_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no


# alternative features

# all cost this feature 6114b of flash
# OLED_ENABLE = yes # 4226b
ifeq ($(strip $(OLED_ENABLE)),yes)
	LUNA = no # 1474b, too expensive and useless
	WPM_ENABLE = yes # 716b
	OS_DETECTION_ENABLE = yes # 754b
endif

ifeq ($(strip $(MIRYOKU_KLUDGE_THUMBCOMBOS)),yes)
  COMBO_ENABLE = yes
  OPT_DEFS += -DMIRYOKU_KLUDGE_THUMBCOMBOS
endif
