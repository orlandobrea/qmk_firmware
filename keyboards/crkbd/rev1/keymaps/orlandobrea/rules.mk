NKRO_ENABLE = yes
BOOTMAGIC_ENABLE = lite   
EXTRAKEY_ENABLE = no        # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no         # Commands for debug and configuration
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_ENABLE  = yes
OLED_DRIVER = ssd1306
SPLIT_KEYBOARD = yes
MOUSEKEY_ENABLE = yes
LTO_ENABLE = yes
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no 
MAGIC_ENABLE = no
MUSIC_ENABLE = yes


# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/logo_reader.c  
        #./lib/glcdfont.c \
				# ./lib/keylogger.c \
        #./lib/layer_state_reader.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \
				
VPATH += keyboards/crkbd/lib
#LIB_SRC += i2c.c
