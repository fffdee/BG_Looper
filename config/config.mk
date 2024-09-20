
   
config LOOPER_ENABLE
	bool "Enable the BG_Looper"
	default n



menu "BG Looper config"

config LOOPER_MAX_CH
    int "Looper max channel"
    default 10
    help
    	This is a Looper max channelthat can be configured.

config NOW_USE_CH
    int "Looper used channel"
    default 0
    help
    	This is a Looper used channel.

config PRINT_INFO

	bool "print BG_Looper's Init INFO"
	default n


endmenu


