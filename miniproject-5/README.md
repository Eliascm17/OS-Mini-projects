Mini-project 5
============

**Due: Nov. 6, 2020 by 11:59 PM US Central Time**.

In this mini-project, you are going to download the Linux kernel sources, compile a new kernel, boot into that kernel, and then answer some questions about the configuration process.

## Prerequisites

To do this mini-project, you'll need to use either the Linux VM installed on your laptop, bare-metal Linux installed on your laptop, or a Linux VM installed on the Linux lab machines.

## Tasks

* Go [here](https://kernelnewbies.org/KernelBuild) and follow its instructions on how to download the Linux kernel and compile it. Below is an overview; the website contains detailed instructions for each step:

1. Obtain the latest stable kernel sources; download a compressed archive from [https://www.kernel.org/](https://www.kernel.org/) rather than cloning the git repo.
2. Initially, use make defconfig.
3. Build the kernel (via make).
4. Install the modules and the kernel.
5. Update your grub configuration.
6. Reboot and select your new kernel.

* Answer the questions about the configuration and compilation process in the [questions.md](questions.md) file. Submit your answers in the submission.pdf file.

## Evaluation

Your mini-project will be graded according to the following criteria:

- **100 points** equally divided across all of the questions.
