# Orange Pi R1 Yocto experiments

This repository contains a custom Yocto Project for Orange Pi R1

## Repository Structure

- `meta-atwice291-opir1/` — my patches for Orange Pi R1.
- `conf/` — local configuration files (e.g. `local.conf`, `bblayers.conf`).
- `setup-env.sh` — environment setup script.

## Quick Start

Clone this repository and initialize the environment:

```bash
git clone https://github.com/ATwice291/opir1.git
cd opir1
./setup-env.sh
