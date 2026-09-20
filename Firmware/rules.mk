MCU = RP2040
BOOTLOADER = rp2040
ENCODER_MAP_ENABLE = no

# Hold SW1 (matrix 0,0) while plugging in to enter the bootloader,
# so the pad can be reflashed without opening the case to reach
# the XIAO's B/R buttons.
BOOTMAGIC_ENABLE = yes
