# Orange Pi R1 Yocto experiments

This repository contains a custom Yocto Project for Orange Pi R1

# SPI LCD ST7735 branch

This branch demonstrates how to drive an SPI LCD (ST7735) with this project. 

Here is how to connect the display to the board:

![LCD Display](opir1_spi_lcd_st7735.JPG)

And here is how it actually works:

![LCD Animation](opir1_spi_lcd_st7735.gif)

## Repository Structure

- `meta-atwice291-opir1/` — my patches for Orange Pi R1.
- `conf/` — local configuration files (e.g. `local.conf`, `bblayers.conf`).
- `setup-env.sh` — environment setup script.

## Quick Start

Clone this repository and initialize the environment:

```bash
git clone https://github.com/ATwice291/opir1.git
cd opir1
. setup-env.sh
