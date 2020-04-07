# Cortex-M GDB server, flash tool 
## for Win32, Linux_x86_64 and Raspberry
### STlink V2 & V3 support

EBlink ARM Cortex-M debug tool with squirrel scripting device support

Also available at: https://git.embitz.org/explore/repos

Changes (7-4-2020) Release 2.3
- Added: The flash option "mod" to do flash modifications. This option can be used with or
         without file flashing. If a file is given then the modifications are done at file image. Muliple mods are allowed.
	 
		 e.g. EBlink -I stlink -S stm32-auto -F mod=080000004;DEAD12345678,mod=080001000;4567FE,mod=08000A200;EB
		 
		      EBlink -I stlink -S stm32-auto -F file=test,mod=080000004;DEAD12345678		 
		 
Changes (5-4-2020) Release 2.2
- Added: --hotplug (-H) used in Embitz 2.0 for launching EBlink at a running target without stopping the target

   
 ##### When to consider EBlink instead of OpenOCD:
- if you need live variables for e.g. Embitz (OpenOCD doesn't support live variables)
- as a non-intrusive memory inspector (eblink supports hot-plugging and non-stop mode )
- for easy complex custom board reset strategies or memory maps with special options
- for faster debug sessions because of the EBlink flash cache (e.g. only modified sectors are rewritten)
- for using easy auto configuration scripts
- as a remote (wifi) GDB server e.g. Raspberry (lightweight)
- If you need a CLI programmer to modify particular flash locations (checksum, serials etc)
- simple standalone flash tool

![Silabs with STlink-V2](https://www.sysdes.nl/github/SilabsStlinkV2_4.png)  

  
### EBlink features:
- Integrated target stack frame UNWIND in case of exception with message box popup in windows.
- GDB server with flash caching, with EmBitz live variables/expression support!
- Supports Hotplug for Embitz 1.1 [see issue](https://github.com/EmBitz/EBlink/issues/3#issue-518281157) and 2.0 (monitor command "IsRunning" for target state query)
- Stand alone command line flashing tool (elf, ihex and srec) 
- All device related functions by squirrel scripting e.g. flash algorithm, device reset strategy etc etc
- Ready for multiple interfaces

#### Remarks:

1) EBlink uses ROM caching for speed performance. It is parsing the same XML memory map, which is provided by scripting, which is offered to GDB to get the memory information. If GDB reads memory from the ROM (flash) region then EBlink will not query the target but will instead return from cache. Sometimes, like debugging flash writing applications (e.g. bootloader), this behavior is not preferred and doesn't show the real flash modifications in GDB. If flash modifying code is debugged, turn off the caching with the "nc" GDB server option.

2) By default, the "Connection under reset" for the stlink interface is enabled. For hotplugging use the CLI option --hotplug (-H) or the stlink interface swith "dr" (Disable Reset) e.g. -I stlink,dr  Both options are the same but set at different levels.


#### ISSUES
- If flash is empty and program is flashed and reset, a target exception is detected 
  and an UNWIND is happening. Just ignore!
- Non STmicro devices (e.g. Silabs, NXP) are only working with STlink-V2.

## EBlink - usage:

	EBlink <options>

	-h,           --help			Print this help
	-g,           --nogui			No GUI message boxes
	-v <level>,   --verbose <0..7>		Specify level of verbose logging (default 4)
	-a [type],    --animation [0..]		Set the animation type (0=off, 1 = cursor, >1 = dot)
	-H,           --hotplug                 Don't reset at target connection
	-I <options>, --interf			Select interface
	-T <options>, --target			Select target(optional)
	-S <file>,    --script <file>		Load a device script file
	-P <path>,    --path <path>		Add a search path for scripts
	-D <def>,     --define <def>		Define script global variable "name=value"
	-F <options>, --flash <options>		Run image flashing
	-G [options], --gdb <options>		Launch GDB server
	
	--script and --interf are mandatory, normally combined with --flash or/and --gdb

       e.g.
        EBlink -I stlink -S stm32-auto -G
        EBlink -I stlink -S stm32-auto -G -D FLASH_SIZE=1024 -D RAM_SIZE=16
        EBlink -I stlink,dr,speed=3000 -S silabs-auto -F erase,verify,run,file=mytarget.elf
        EBlink -I cmsis-dap -T cortex-m,nu -S stm32-auto -G port=4242,nc,s -S myReset.scr


==== Interfaces


name: CMSIS-DAP - ARM debug protocol driver 
	
	Usage -I cmsis-dap[,options]

        <not yet implemented>


name: STlink - STmicro V2/3 interface driver 
	
	Usage -I stlink[,options]

        dr           : Disable reset at connection (same as cli --hotplug)
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
        run          : Start image
        mod=<hex address>;<hex byte(s)>
                     : Modify flash location at address with a given byte array
        file=<file>  : Load the file, <file>.hex  = Intel HEX format
                                      <file>.srec = Motorola srec file format

                                      Default     = ELF file format

        e.g. -F file=test.elf
             -F run,file=test.hex		
             -F run,verify,mod=80000004;DEAD
             -F run,file=test.hex,mod=80000004;45FECA1245,mod=80000100;DEAD
             -F erase,verify,run,file=test.srec
             -F erase
             -F run			 

        Default (without erase) only modified sectors are (re)flashed.
		Multiple modifications are allowed and is done after any file upload.


==== GDB server
     
     Usage -G [options]

        s            : Shutdown after disconnect
        nc           : Don't use EBlink flash cache
        port=ppp     : Select different TCP port, default 2331
        address=x.x.x.x : Select different listen address, default 0.0.0.0

        e.g.  -G s,nc
