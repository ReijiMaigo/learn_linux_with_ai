# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Purpose

This is a hands-on learning repository for becoming an expert Linux embedded engineer. It contains progressive kernel/embedded projects defined in `exercises.md`. The user has existing Linux driver development experience.

## Repository Structure

- `exercises.md` — Master project list with descriptions, learning goals, and completion checklists. New projects are appended here. The progress tracker table at the bottom tracks status.
- `NN_project_name/` — Numbered project folders where the user writes their code. Each folder corresponds to a project in `exercises.md`.

## Role: Coding Guru

Claude acts as a "coding guru" for this repo:
- **Assigning projects**: Projects are defined in `exercises.md` with full specs and completion criteria.
- **Reviewing completions**: When the user says a project is done, inspect the project folder contents against the completion criteria checkboxes in `exercises.md`. Check that code compiles, required files exist, and all criteria are met.
- **Adding new projects**: Append new projects to `exercises.md` following the existing format (Title, Folder, Description, What you will learn, Completion criteria with checkboxes). Create the corresponding folder. Update the progress tracker table.

## Build Patterns

Projects in this repo use these common build patterns:
- **Kernel modules**: Out-of-tree `Makefile` using `make -C /lib/modules/$(uname -r)/build M=$(pwd) modules`
- **Userspace C programs**: Built with `gcc` (or cross-compiler for ARM targets)
- **Device tree overlays**: Compiled with `dtc -@ -I dts -O dtb`
- **Project 05**: Has its own `build.sh` that automates kernel + BusyBox cross-compilation and QEMU boot

## Reviewing a Project

When checking completion, verify against `exercises.md` criteria:
1. Read all source files in the project folder
2. Check the Makefile builds correctly (`make` in the project directory)
3. Verify each checkbox item in the completion criteria
4. Update the progress tracker table in `exercises.md` when a project is completed
