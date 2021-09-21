# Ready to go Debian package AMD64 / ARMHF(raspberryPi)

This package will install everything needed to start using EBlink with STlink(c) on a fresh machine.  
Dependencies: none

**_AMD64_**
    Install: sudo apt install ./eblink-debian-amd64.deb
    Remove:  sudo dpkg  --remove eblink-debian-amd64
    
**_RaspberryPi_**
    Install: sudo apt install ./eblink-debian-armhf.deb
    Remove:  sudo dpkg  --remove eblink-debian-armhf

Installed files:

    /usr/bin/eblink                     // Executable  
    /usr/share/eblink                   // Scripts folder  
    /etc/profile.d/eblink.sh            // EBlink Environment variables export at linux startup  
    /etc/udev/rules.d/80-eblink.rules   // The STlink device registrations  


The following environment variables are active after linux reboot:

    EB_DEFAULT_PROBE=stlink
    EB_DEFAULT_SCRIPT=auto

You can launch EBlink from every terminal with just **_eblink -G_**  


    GDB launch:     eblink -G
    Flash file:     eblink -F file=test.elf
    Target control: eblink -T cortex-m,halt, eblink -T cortex-m,reset=2 or eblink -T cortex-m,resume
    etc (check eblink -h )  

IF you need a particular script file you can just overrule the environment by **_eblink -S silabs-auto -G_**  
or **_eblink -I stlink,speed=1000 -G nc_** etc.
    
