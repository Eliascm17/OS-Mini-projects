For questions 5-9, go to your kernel source directory and do either a `make menuconfig` or a `make xconfig` (you may need to install packages (https://askubuntu.com/questions/520864/how-to-install-needed-qt-packages-to-build-kernel-on-14-04) to use xconfig). This allows you to view and configure the options that your kernel will be built with. 

1. What is the version of the kernel you compiled?

2. Run the following command from a terminal: ``uname -a``.
What is the output from your old kernel? What's the output from the new kernel?

3. Go to the `/boot` directory and issue an `ls -rlt` command (this puts newly created files at the bottom). You should see four new files: vmlinuz-*version*, System.map-*version*, config-*version* and initrd.img-*version*, where *version* is the kernel version you compiled. Give a short description of the purpose of each of these four files.

4. What is the size of the kernel binary (e.g., your vmlinuz file) in MB? You can use the ``ls -lh`` command to determine this.

5. Find the "Timer frequency" configuration option (under "Processor type and features"). What does this configuration option control?  What performance differences do you expect to observe with the different options?

6. What does the configuration menu say about a 100Hz timer interrupt vs a 1000Hz timer interrupt?

7. Look for the "Network packet filtering framework (Netfilter)" option and describe what Netfilter is. You may use Netfilter later on (e.g., can be an option for the final project).

8. Look for the "Randomize the address of the kernel image (KASLR)" option. What does this option do?

9. Ensure that you have the "64-bit kernel" option enabled and look under the "Security options" category for the "Remove the kernel mapping in user mode" option. What does the help message say about this option?

10. Is the kernel compiled against a C library (like regular user-space programs)? Why or why not?

**To answer these questions, you can definitely refer to things online, but don't forget to provide links.**
