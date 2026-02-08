# Linux Embedded Engineer - Learning Path

A hands-on project-based learning repository for becoming an expert Linux embedded engineer. Each project progressively builds core skills — from writing kernel modules to building an entire embedded Linux system from scratch.

All project specifications, learning objectives, and completion criteria are tracked in [exercises.md](exercises.md). Code is developed inside each project's numbered folder and reviewed against the defined criteria.

## Available Hardware

- Ubuntu PC (native Linux development)
- Raspberry Pi
- BeagleBone Black
- Windows WSL (userspace/cross-compilation only — not suitable for kernel modules)

## Table of Contents

| # | Project | Target Device |
|---|---------|---------------|
| 1 | [Custom Character Device Driver with IOCTL](01_custom_char_device/) | Ubuntu PC |
| 2 | [Platform Driver with Device Tree Binding](02_platform_driver_with_devicetree/) | BeagleBone Black |
| 3 | [I2C Sensor Driver with Input Subsystem Integration](03_i2c_sensor_driver/) | Raspberry Pi / Ubuntu PC (i2c-stub) |
| 4 | [Kernel Framebuffer Driver for a Virtual Display](04_kernel_framebuffer_driver/) | Ubuntu PC |
| 5 | [Build a Minimal Embedded Linux System from Scratch](05_embedded_linux_from_scratch/) | Ubuntu PC → QEMU → BeagleBone Black |
