# Peanuts
Useful C/C++ unittest/fuzztest API

# Getting started
## Prerequisites
### Mandatories
* make: `apt install make`

### Optionals
* clang-format (version >= 8.0): `apt install clang-format-8`

## Installation
1. Clone the current repository: `git clone https://gitlab.com/project/kimye/peanuts.git`
2. Install submodules: 
* `git submodule sync --recursive`
* `git submodule update --init --recursive`
3. Build: `make`

# Running the tests
`./run.sh`

# API
ToDo

# Exemples
Some unitary tests and fuzz tests can be found in the file `srcs/exemple.cpp`

# Butter (ToDo)
- Fill README
- Implement missing combinatorials: combinations_with_repetition, permutations_with_repetition, combinations_without_repetition, permuations_without_repetition
