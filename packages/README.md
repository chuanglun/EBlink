# Ready to go Debian package AMD64 / ARMHF(RaspberryPi)

This package will install everything needed to start using EBlink with STlink(c) on a fresh machine.  
Dependencies: none

**AMD64**
    
    Install: sudo apt install ./eblink-debian-amd64.deb
    Remove:  sudo dpkg  --remove eblink-debian-amd64
    
**RaspberryPi**

    Install: sudo apt install ./eblink-debian-armhf.deb
    Remove:  sudo dpkg  --remove eblink-debian-armhf

**Installed files**

    /usr/bin/eblink                     // Executable  
    /usr/share/eblink                   // Scripts folder  
    /etc/profile.d/eblink.sh            // EBlink Environment variables export at linux startup  
    /etc/udev/rules.d/80-eblink.rules   // The STlink device registrations  


The following environment variables are active <u>after linux reboot</u>:

    EB_DEFAULT_PROBE=stlink
    EB_DEFAULT_SCRIPT=auto

**Usage**

You can launch EBlink from every terminal, e.g. to launch GDB server **_./eblink -G_**  

Examples:

    GDB launch:     ./eblink -G
    Flash file:     ./eblink -F file=test.elf (file is relative to the terminal's CWD)
    Target halt:    ./eblink -T cortex-m,halt  
    Target reset:   ./eblink -T cortex-m,reset=2    reset types: 0(default)=system,1=core,2=jtag
    Target resume:  ./eblink -T cortex-m,resume
    etc (check "./eblink -h" )  

IF you need a particular script file you can just overrule the environment by **_./eblink -S silabs-auto -G_**  
or if other interface options are needed **_./eblink -I stlink,speed=1000 -G_** etc.
    
