<div align="center">
    <h3>✶ memory of alessa ✶</h3>
    <p><em>Silent Hill 3 (PS2) matching decompilation project</em></p>
</div>

### project goals

[![sh3 functions](https://decomp.dev/dreamingmoths/memory-of-alessa.svg?mode=shield&label=sh3+functions&color=%236b4e73&style=flat&measure=matched_functions)](https://decomp.dev/dreamingmoths/memory-of-alessa)
![sh2 functions](https://decomp.dev/dreamingmoths/memory-of-alessa/SLUS_202.28.svg?mode=shield&label=sh2+functions&color=%236b4e73&style=flat&measure=matched_functions)
[![sh3 stages](https://img.shields.io/badge/sh3_stages-2%20/%2040-%236b4e73)](https://decomp.dev/dreamingmoths/memory-of-alessa?category=heaven_00)

⋆˙⟡ 100% byte-matching decompilation of Silent Hill 3, a survival horror
masterpiece.

⋆˙⟡ 100% byte-matching decompilation of Silent Hill 2 engine, the
foundation for Silent Hill 3.

⋆˙⟡ Learning & documenting the technical history of Team Silent's PS2 engine.

🔴 This project is in early stages. Things are likely to change and may be wrong.

### setup

0. `python3`, `wget`, and essential build packages are prerequisites.

1. Insert the disc of Silent Hill 3 v1.02 (NTSC-U) for the PlayStation 2 into
   your computer. It has serial number `SLUS_206.22` and its ISO's SHA1 is
   `0f7b0d5d75fe34ddf72e26aae1b4f5e7891282b0`.

2. Copy the `SLUS_206.22` file as well as `B0.MFA` into the folder at
   `rom/SLUS_206.22` in this repository.

Then proceed below depending on your operating system.

#### linux (x86-64) & macOS (aarch64)

On first setup, run the following commands in the root directory of this
repository. They will set up a virtual environment and install the required
Python packages.

```sh
python3 -m venv .venv
source .venv/bin/activate
python3 -m pip install -r requirements.txt
```

Then run `make`. This will download the toolchain, extract files, and build
Silent Hill 3.

```sh
make
```

#### windows

Untested, but WSL or similar is required.

### more on development

See [docs/development.md](docs/development.md).

### credits

Tremendous thanks to the [decompals](https://github.com/decompals) for making
this project possible, as well as to each of the following projects below.

✶ [silent-hill-decomp](https://github.com/Vatuu/silent-hill-decomp) <br>
✶ [Himuro](https://github.com/Mikompilation/Himuro) <br>
✶ [mh1j](https://github.com/2Tie/mh1j) <br>
✶ [parappa2](https://github.com/parappadev/parappa2) <br>
✶ [xenogears-decomp](https://github.com/ladysilverberg/xenogears-decomp) <br>
✶ [3s-decomp](https://github.com/crowded-street/3s-decomp) <br>
✶ [rood-reverse](https://github.com/ser-pounce/rood-reverse) <br>
✶ [SPPS](https://github.com/Daniel-McCarthy/SPPS) <br>
✶ [recvx-decomp](https://github.com/fmil95/recvx-decomp)
