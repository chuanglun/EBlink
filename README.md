# Cortex-M GDB server, flash tool (Win32, Linux_x86_64)
## STlink V2 & V3 support

EBlink ARM Cortex-M debug tool with squirrel scripting device support

NEW (29-10-2019)
- STlink V3 support
- Linux_x64 build 

ISSUES
- If flash is empty and program is flashed and reset, a target exception is detected 
  and an UNWIND is happening. Just ignore!
- Non STmicro devices (e.g. Silabs, NXP) are only working with STlink-V2.
  

![Silabs with STlink-V2](https://www.sysdes.nl/github/SilabsStlinkV2_4.png)  

  
EBlink features:
- Integrated target stack frame UNWIND in case of exception with message box popup in windows.
- GDB server with flash caching, with EmBitz live variables/expression support!
- Supports Hotplug for Embitz 2.0 (monitor command "IsRunning" for target state query)
- Stand alone command line flashing tool (elf, ihex and srec) 
- All device related functions by squirrel scripting e.g. flash algorithm, device reset strategy etc etc
- Ready for multiple interfaces

eblink - usage:

	EBlink <options>

	-h,           --help			Print this help
	-g,           --nogui			No GUI message boxes (win32 only)
	-v <level>,   --verbose <0..7>		Specify generally verbose logging
	-D <script>,  --device <script>		Select the device script <>.script
	-T <options>, --target			Select target(optional) default cortex-m
	-I <options>, --interf			Select interface
	-F <options>, --flash <options>		Run image flashing
	-G [options], --gdb <options>		Launch GDB server
	
	--device and --interf are mandatory, normally combined with --flash or/and --gdb


==== Interfaces


name: CMSIS-DAP - ARM debug protocol driver 
	
	Usage -I cmsis-dap[,options]

        <not yet implemented>


name: STlink - STmicro V2/3 interface driver 
	
	Usage -I stlink[,options]

        rconnect     : Connect under reset
        speed=nnn    : Interface speed (default max possible)
        swd          : use SWD (default)
        jtag         : use Jtag
        device=<usb_bus>:<usb_addr> : Select probe explicit

        e.g.  -I stlink,rconnect,speed=3000

==== Targets


name: cortex-m
     
     Usage -T cortex-m[,options]

        nu           : Disable stack unwind at exception

        e.g.  -T cortex-m,nu

==== Flash loader
	
	Usage -F [options]

        erase        : Chip erase the flash
        verify       : Verify flash after upload
        run          : Start image after upload
        file=<file>  : Load the file, <file>.hex  = Intel HEX format
                                      <file>.srec = Motorola srec file format

                                      Default     = ELF file format

        e.g. -F file=test.elf
             -F verify,run,file=test.srec
             -F erase
             -F erase,run,file=test.hex

        Default (without erase) only modified sectors are (re)flashed.



==== GDB server
     
     Usage -G [options]

        S            : Shutdown after disconnect
        nc           : Don't use EBlink flash cache
        port=ppp     : Select different TCP port, default 2331
        address=x.x.x.x : Select different listen address, default 0.0.0.0

        e.g.  -G S,nc
