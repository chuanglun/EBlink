# Cortex-M GDB server, flash tool 
## for Win32, Linux_x86_64 and Raspberry
### STlink V2 & V3 support

EBlink ARM Cortex-M debug tool with squirrel scripting device support

NEW (16-11-2019)
- Raspberry binary

CHANGES (14-11-2019)
- Reset behavior changed: "Connect under reset" is now always enabled and for hotplug use the Disable Reset ("dr") stlink interface option
- New script interfaceApi function "resetCtrl(bool)" which controls the NRST line directly
- Bug minor fixes

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
- Supports Hotplug for Embitz 1.1 [see issue](https://github.com/EmBitz/EBlink/issues/3#issue-518281157) and 2.0 (monitor command "IsRunning" for target state query)
- Stand alone command line flashing tool (elf, ihex and srec) 
- All device related functions by squirrel scripting e.g. flash algorithm, device reset strategy etc etc
- Ready for multiple interfaces

Remarks:

1) EBlink uses ROM caching for speed performance. If GDB reads memory from the ROM (flash) region then EBlink will not query the target but will instead return from cache. Sometimes, like debugging flash writing applications (e.g. bootloader), this behavior is not preferred and doesn't show the real flash modifications in GDB. If flash modifying code is debugged, turn off the caching with the "nc" GDB server option.

2) By default, the "Connection under reset" for the stlink interface is enabled. For hotplugging use the "dr" switch (Disable Reset) for the stlink interface e.g. -I stlink,dr

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

       e.g.
       	EBlink -I stlink -D stm32-auto -G
       	EBlink -I stlink,dr,speed=3000 -D silabs-auto -F erase,verify,run,file=mytarget.elf
       	EBlink -I cmsis-dap -T cortex-m,nu -G port=4242,nc


==== Interfaces


name: CMSIS-DAP - ARM debug protocol driver 
	
	Usage -I cmsis-dap[,options]

        <not yet implemented>


name: STlink - STmicro V2/3 interface driver 
	
	Usage -I stlink[,options]

        dr           : Disable reset at connection (hotplug)
        speed=nnn    : Interface speed (default max possible)
        swd          : use SWD (default)
        jtag         : use Jtag
        device=<usb_bus>:<usb_addr> : Select probe explicit

        e.g.  -I stlink,dr,speed=3000

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
             -F run,file=test.hex		
             -F erase,verify,run,file=test.srec
             -F erase
             -F run			 

        Default (without erase) only modified sectors are (re)flashed.



==== GDB server
     
     Usage -G [options]

        S            : Shutdown after disconnect
        nc           : Don't use EBlink flash cache
        port=ppp     : Select different TCP port, default 2331
        address=x.x.x.x : Select different listen address, default 0.0.0.0

        e.g.  -G S,nc
