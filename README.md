# arch-files
Refer to the Guides directory for the written guides under the sub-directories Installation, Configuration and Issues.

## Guides
#### Installation
Contains the _Installation.txt_ and _After-Install.txt_ files. The _Installation.txt_ file contains the process required to install Arch Linux from a bootable device and have a working bare-bones operating system. The _After-Install.txt_ details the steps taken to add basic functionality on top of the basic installation. Simple things like ensuring network setup is finalised, and configuring sudo privileges.

#### Configuration
Contains all the files detailing how to configure packages I have installed on Arch. Each file considers the installation process, the configuration steps, any problems encountered and their requisite solutions, and finally provides the actual Linux commands used, every single one. The _packages.txt_ file contains a variety of packages that only required install, and possibly some basic configuration, and did not warrant a separate file.

#### Issues
This directory contains files of issues encountered whilst setting up and configuring the system. Those that are solved have the word solved in the file name, and each file chronicles the steps taken to solve the issue, or as much information about the unresolved issue as possible.

## Packages
Contains the list of packages that I have installed, both from the AUR, and the Official Repository. There are two further "packages" installed, both from Github, that are not found in this list, nor in any of these files, except for their guide text file in the _Guides/Configuration/_ directory.

#### Github Repositories
_bettterlockscreen_ and _pakku_ are the only two Github repositories that I have cloned for use on my system. _pakku_ is a pacman wrapper for AUR package builds, and _betterlockscreen_ is essentially a wrapper for i3lock-color, and combines the functions of i3lock-blur.

## .scripts
I use the scripts contained in the _i3blocks_ directory, not the _lstatusbar_ directory. These scripts are the ones I wrote myself and use for my status bar, the scripts in _lstatusbar_ are the ones that Luke Smith uses.
