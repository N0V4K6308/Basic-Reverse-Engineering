# CrackMe Files - Source Code

This repository contains several small "crackme" / registration challenge programs (C++), example source files, and a Python helper `keygen.py` that reproduces the registration algorithm.

**Purpose:**
- Provide compact C++ examples that implement a registration/check algorithm for education and reverse‑engineering practice.
- Include a Python reference implementation (`keygen.py`) that reproduces the same algorithm for generating and validating registration codes.

**Repository layout**
- `source/` : C++ source files (examples such as `CrackMeOne.cpp`, `CrackMeReg.cpp`).
- `bin/`    : Example build outputs or config files.
- `keygen.py`: Python script that replicates the algorithm and can generate/validate registration codes from `CrackMeReg.exe`.
- `requirements.txt`: Python dependencies for `keygen.py`.

**Build (C++)**
- On Windows with MSYS2/MinGW, you can build a file with `g++` (example):

```bash
C:/msys64/mingw64/bin/g++.exe -g source/CrackMeRegistration.cpp -o bin/CrackMeRegistration.exe
```

- Or use the included VS Code task `C/C++: g++.exe build active file` to build the active source file.

**Run (C++)**
- After building, run the produced executable from a console:

```bash
./bin/CrackMeOne.exe
./bin/CrackMeReg.exe
```

Note: some of the sample programs may include a runtime check for a debugger (e.g. `IsDebuggerPresent`) and will exit or show a message box if a debugger is attached.

**Python keygen (`keygen.py`)**
- Install dependencies:

```bash
python -m pip install -r requirements.txt
```

- Basic usage examples:

```
# Printing help menu
python keygen.py --help

# Generate code for a single user
python keygen.py -u test

# Generate codes for multiple users
python keygen.py -u admin -u user

# Interactive mode
python keygen.py --interactive


```
**Author's Note**
- The C++ source files in the `source/` folder and all content in this repository were written by the repository author.
- The Python script `keygen.py` is the author's solution for reproducing the registration algorithm.