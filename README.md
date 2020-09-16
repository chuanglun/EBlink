# Cortex-M GDB server, flash tool e.g. STlink V2 & V3 support
## for Win32, Linux_x86_64 and Raspberry

EBlink ARM Cortex-M debug tool with squirrel scripting device support

Upcomming 3.0 release: 
 - New: Windows installer with optional windows context menu for file flashing [.hex,.elf and .srec] and core control (reset,halt and resume)

Changes (16-9-2020) Release 2.9
 - Added: "-F cmp=myimage.elf" command to compare the content of file [elf,hex or srec] against MCU for e.g. automated testing.
 - Added: "-F dump=lenght@address:file" command to dump the memory content to file [hex or bin].
 - Added: On verbose level > 5 give info if and which environment variables are used for user feedback.
 - Added: Cortex-m target options (-T cortex-m,<...>)  for reset=[0..2],halt and resume e.g. automated testing.
 - Mod: Verbose level 0 is now minimal printing (previous level 8) for -F read memory output. Default verbose level will be 5 (previous level 4)
 - Mod: All the CLI length and address fields (e.g. flash write, read or dump) are now decimal or hex if starting with 0x

   
 ##### When to consider EBlink instead of OpenOCD:
- if you need live variables for e.g. Embitz (OpenOCD doesn't support live variables)
- as a non-intrusive memory inspector (eblink supports hot-plugging and non-stop mode )
- if you need a CLI memory reader to read particular memory locations (also on running targets) and print them at stdout
- if you need a CLI programmer to modify particular in-place flash locations (checksum, serials etc)
- for easy complex custom board reset strategies or memory maps with special options
- for faster debug sessions because of the EBlink flash cache (e.g. only modified sectors are rewritten)
- for using easy auto configuration scripts e.g. custom flashing of ext. EEprom's etc
- as a remote (wifi) GDB server e.g. Raspberry (lightweight)
- simple standalone flash tool (program, verify, compare or dump)
  
### EBlink features:
- Integrated target stack frame UNWIND in case of exception with message box popup in windows.
- GDB server with flash caching, with EmBitz live variables/expression support!
- Full Semi-hosting support
- Supports Hotplug for Embitz 1.1 [see issue](https://github.com/EmBitz/EBlink/issues/3#issue-518281157) and 2.0 (monitor command "IsRunning" for target state query)
- Inplace memory (flash or ram) modifications of any length byte array from the command line (e.g. serials or checksum programming)
- Any length byte array memory reading also on running target from the command line (automated testing)
- Core control (halt, reset and resume) from the command line (automated testing)
- Stand alone command line flashing tool (elf, ihex and srec)  for production
- Dump memory (also on running target) to file in Intel hex or binary format
- Compare flash against a srec, ihex or elf file.
- All device related functions by c-like squirrel scripting e.g. flash or ext. EEprom algorithms, device reset strategy etc etc 
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
	-v <level>,   --verbose <0..8>		Specify level of verbose logging (default 5)
	-a [type],    --animation [0..]		Set the animation type (0=off, 1 = cursor, >1 = dot)
	-H,           --hotplug                 Don't reset/stop at target connection
	-I <options>, --interf			Select interface
	-T <options>, --target			Select target(optional)
	-S <file>,    --script <file>		Add a device script file
	-P <path>,    --path <path>		Add a search path for scripts
	-D <def>,     --define <def>		Add a script global define "name=value"
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
		
        read=<dec byte length>@<hex address>
                     : Read memory location at address with a given length and print as hex string.
					   Use verbose level 0 for minimal print info."
		
        write=<hex byte(s)>@<hex address>
                     : Modify flash location at address with a given byte array
					 
        file=<file>  : Load the file, <file>.hex  = Intel HEX format
                                      <file>.srec = Motorola srec file format

                                      Default     = ELF file format
									  
        cmp=<file>   : Compare Flash with file, <file>.hex  = Intel HEX format
                                      <file>.srec = Motorola srec file format

                                      Default     = ELF file format		

        dump=<length>@<address>:<file> 
                     : Dump memory to file, <file>.hex  = Intel HEX format
		                            Default     = Binary file format									  

        e.g. -F file=test.elf
             -F run,file=test.hex		
             -F read=0x4@0x0800000A,read=12@0x0800000C			 
             -F run,verify,write=DEAD@0x08000004
             -F run,file=test.hex,write=45FECA1245@0x80000004,write=EBAB@0x08000100
             -F erase,verify,run,file=test.srec
             -F erase
             -F run			 

        Default (without erase) only modified sectors are (re)flashed.
	Multiple writes and reads are allowed and is done after any file upload.


==== GDB server
     
     Usage -G [options]

        s            : Shutdown after disconnect
        nc           : Don't use EBlink flash cache
        port=ppp     : Select different TCP port, default 2331
        address=x.x.x.x : Select different listen address, default 0.0.0.0

        e.g.  -G s,nc
