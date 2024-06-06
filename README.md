# IOCTL Driver
Self made kernel IO Control Driver сделан xyz

__________

This repository contains a simple kernel-level driver for Windows that demonstrates how to handle IO Control (IOCTL) requests from user mode. The driver sets up a basic framework for communication between user mode and kernel mode using IOCTLs.
Features

    IOCTL Handling: The driver implements IOCTL handling to perform various operations in the kernel.
    Basic Operations: Provides a foundation for more complex kernel-level projects by showcasing device creation, dispatch, and control handling.
    Clean Codebase: The codebase is well-structured and follows best practices for kernel-level development.


To use this driver:

    Clone the repository to your local machine.
    Open the project in Visual Studio or your preferred IDE.
    Build the project to generate the driver binary.
    Load the driver using the appropriate tools (sc command, DriverLoader, etc.).
    Communicate with the driver from user mode using IOCTLs.
