# Linux Embedded Engineer - Project Exercises

## Instructions

- Each project has its own folder under this directory (e.g., `01_custom_char_device/`).
- Work inside the corresponding folder for each project.
- Projects are ordered by difficulty. Complete them in order.
- When you believe a project is complete, ask your coding guru to review the folder.
- The guru will check the project folder contents and decide if the task is done.
- New projects will be appended below as you progress.

---

## Project 01: Custom Character Device Driver with IOCTL

**Folder:** `01_custom_char_device/`

**Description:**
Build a Linux kernel module that registers a character device (`/dev/mydevice`). The device must support `open`, `read`, `write`, `release`, and custom `ioctl` commands. Implement a kernel-space circular buffer that userspace can write to and read from. Add at least 3 custom ioctl commands: one to get the current buffer size, one to clear the buffer, and one to set a maximum buffer capacity. Write a userspace test program in C that exercises all operations.

**What you will learn:**
- Kernel module lifecycle (`module_init`, `module_exit`)
- Character device registration (`alloc_chrdev_region`, `cdev_add`)
- File operations struct (`file_operations`)
- IOCTL interface design (`_IOR`, `_IOW`, `_IOWR` macros)
- `copy_to_user` / `copy_from_user` for safe kernel-user data transfer
- Kernel synchronization with mutexes or spinlocks
- `udev` rules for automatic device node creation
- Writing a proper `Makefile` for out-of-tree kernel modules

**Completion criteria:**
- [ ] Kernel module compiles without warnings against the running kernel
- [ ] Module loads (`insmod`) and unloads (`rmmod`) cleanly with no kernel oops
- [ ] `/dev/mydevice` node is created (manually or via udev rule)
- [ ] Userspace program can write data, read it back, and verify correctness
- [ ] All 3 ioctl commands work correctly
- [ ] Circular buffer handles wrap-around and full/empty conditions
- [ ] `dmesg` shows clean log messages for all operations
- [ ] A `Makefile` builds both the kernel module and the userspace test program

---

## Project 02: Platform Driver with Device Tree Binding

**Folder:** `02_platform_driver_with_devicetree/`

**Description:**
Create a platform driver that binds to a custom device tree node. The driver should parse device tree properties (strings, integers, arrays, booleans) and expose them through `sysfs` attributes. Write a device tree overlay (`.dts`) that describes a virtual device with at least 5 custom properties. The driver must handle `probe` and `remove` callbacks correctly. Add a `sysfs` interface that allows userspace to read and modify at least two parameters at runtime.

**What you will learn:**
- Platform driver model (`platform_driver`, `platform_device`)
- Device tree syntax and overlay compilation (`dtc`)
- Device tree property parsing APIs (`of_property_read_*`)
- Compatible string matching (`of_match_table`)
- `sysfs` attribute creation (`DEVICE_ATTR`, `sysfs_create_group`)
- The Linux device model (bus, device, driver relationship)
- Device tree overlay loading at runtime

**Completion criteria:**
- [ ] Device tree overlay compiles cleanly with `dtc`
- [ ] Platform driver loads and binds to the DT node on `probe`
- [ ] All 5+ DT properties are parsed and logged via `dmesg`
- [ ] At least 2 sysfs attributes are readable from userspace (`cat /sys/...`)
- [ ] At least 2 sysfs attributes are writable from userspace (`echo ... > /sys/...`)
- [ ] Driver unbinds and cleans up on `remove` (no resource leaks)
- [ ] `Makefile` builds the module; a script or instructions load the overlay
- [ ] Code uses `dev_info`/`dev_err` (not `printk`) for logging

---

## Project 03: I2C Sensor Driver with Input Subsystem Integration

**Folder:** `03_i2c_sensor_driver/`

**Description:**
Write an I2C client driver for a real or emulated sensor (e.g., BMP280 temperature/pressure sensor, or a virtual I2C device using `i2c-stub`). The driver must initialize the sensor over I2C, read measurement registers periodically using a kernel workqueue or timer, and report values through both the `hwmon` (hardware monitoring) subsystem and a `sysfs` interface. If you don't have physical hardware, use the `i2c-stub` kernel module to emulate an I2C device with predefined register values.

**What you will learn:**
- I2C subsystem (`i2c_driver`, `i2c_client`, `i2c_smbus_*` APIs)
- Kernel workqueues or timers for periodic tasks
- `hwmon` subsystem integration (`hwmon_device_register_with_info`)
- Regmap API for register access abstraction
- I2C device emulation with `i2c-stub` for testing without hardware
- Proper error handling for bus communication failures
- `MODULE_DEVICE_TABLE` for autoloading

**Completion criteria:**
- [ ] Driver compiles and loads without errors
- [ ] Works with real I2C hardware OR `i2c-stub` emulation
- [ ] Sensor registers are read correctly over I2C (verified via `dmesg`)
- [ ] Values exposed through `hwmon` (visible in `/sys/class/hwmon/`)
- [ ] Values also exposed through custom `sysfs` attributes
- [ ] Periodic reading works via workqueue or timer (configurable interval)
- [ ] Graceful error handling when I2C communication fails
- [ ] Driver properly cleans up all resources on removal

---

## Project 04: Kernel Framebuffer Driver for a Virtual Display

**Folder:** `04_kernel_framebuffer_driver/`

**Description:**
Implement a framebuffer driver (`fbdev`) that creates a virtual display device. The driver allocates a memory-backed framebuffer that userspace can mmap and draw to. Implement a userspace program that maps the framebuffer, draws basic shapes (rectangles, lines, gradients), and writes the raw pixel data to a file (BMP or PPM image) for verification. The framebuffer should support at least 640x480 resolution with 32-bit color depth (RGBA). Implement `fb_fillrect`, `fb_copyarea`, and `fb_imageblit` operations.

**What you will learn:**
- Linux framebuffer subsystem (`fb_info`, `fb_ops`, `fb_var_screeninfo`)
- Kernel memory allocation for large buffers (`vmalloc`, `alloc_pages`)
- `mmap` implementation in kernel drivers (`remap_vmalloc_range` or `remap_pfn_range`)
- Pixel formats and color depth handling
- Userspace framebuffer programming (`/dev/fb*`)
- Image file format basics (PPM/BMP) for output verification
- DMA-capable memory considerations for real hardware

**Completion criteria:**
- [ ] Driver registers a framebuffer device (`/dev/fbN` appears)
- [ ] `fbset` or `cat /sys/class/graphics/fbN/virtual_size` shows correct resolution
- [ ] Userspace program successfully mmaps the framebuffer
- [ ] Drawing operations produce correct pixel data in the buffer
- [ ] Output image file (BMP or PPM) visually verifies the drawings
- [ ] `fb_fillrect`, `fb_copyarea`, `fb_imageblit` are implemented
- [ ] No memory leaks on module removal (checked via `kmemleak` or manual review)
- [ ] Makefile builds both the kernel module and the userspace drawing program

---

## Project 05: Build a Minimal Embedded Linux System from Scratch

**Folder:** `05_embedded_linux_from_scratch/`

**Description:**
Build a minimal bootable embedded Linux system entirely from source. Cross-compile a Linux kernel (for ARM or your native x86_64), build BusyBox as the userspace, create a minimal root filesystem with an init script, and package it into an `initramfs`. Boot the system using QEMU. The init script must mount `proc`, `sys`, and `devtmpfs`, set up a basic networking interface (loopback at minimum), and drop into a shell. Then write a custom daemon in C that starts at boot, logs to a file, and responds to `SIGTERM` for clean shutdown. Include a `build.sh` script that automates the entire build process.

**What you will learn:**
- Cross-compilation toolchains and `CROSS_COMPILE` usage
- Linux kernel configuration (`make menuconfig`, `.config`)
- BusyBox configuration and static linking
- Root filesystem layout (`/bin`, `/sbin`, `/etc`, `/proc`, `/sys`, `/dev`)
- `initramfs` / `initrd` creation (`cpio` archive format)
- QEMU for embedded system emulation
- Init process and PID 1 responsibilities
- Signal handling in daemons (`SIGTERM`, `SIGHUP`)
- Boot sequence: bootloader -> kernel -> initramfs -> init -> userspace
- Shell scripting for build automation

**Completion criteria:**
- [ ] `build.sh` downloads, configures, and compiles kernel + BusyBox from source
- [ ] Root filesystem contains correct directory layout and busybox symlinks
- [ ] `initramfs` is generated as a cpio archive
- [ ] System boots in QEMU to a working shell
- [ ] `proc`, `sys`, and `devtmpfs` are mounted by the init script
- [ ] Loopback network interface is up (`ping 127.0.0.1` works)
- [ ] Custom daemon starts at boot, writes logs, and handles `SIGTERM`
- [ ] System shuts down cleanly without kernel panics
- [ ] The entire process is documented in a `README` inside the project folder

---

## Progress Tracker

| # | Project | Status |
|---|---------|--------|
| 1 | Custom Character Device Driver with IOCTL | Not Started |
| 2 | Platform Driver with Device Tree Binding | Not Started |
| 3 | I2C Sensor Driver with Input Subsystem | Not Started |
| 4 | Kernel Framebuffer Driver for Virtual Display | Not Started |
| 5 | Embedded Linux System from Scratch | Not Started |
