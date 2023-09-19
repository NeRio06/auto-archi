
# auto-archi

Program that build the archi of your project by parsing his tree command output.

## Prerequisites

Before you proceed with the installation, ensure that you have the GCC compiler installed on your system. You can check if it's installed by running the following command:

```bash
  gcc --version
```

If GCC is not installed, you can typically install it using your system's package manager. For example, on Debian-based systems (such as Ubuntu), you can use apt-get:

```bash
  sudo apt-get install gcc
```
## Installation

To install auto-archi, first clone the repository, and then navigate to the directory.

```bash
  git clone https://github.com/NeRio06/auto-archi.git
  cd auto-archi
```

If you are a student from epita and you want to install auto-archi and your session, run the command :

```bash
  make epita-install
```

Else, you can install the program using the make install command. By default, this will place the executable in /usr/local/bin:

```bash
  make install
```
If you wish to specify a custom installation path, use the INSTALL_PATH variable like this:

```bash
  make install INSTALL_PATH=/custom/path
```
## Usage
This C program is designed to be executed from the terminal with the following format:

```bash
  archi [OPTIONS] tree-path [build-path]
```

The arguments can be interchanged, but there are some rules to follow:

- `tree-path` is mandatory and represents the path to a file that contain the tree command output.
- `-a login` is an optional flag that must be followed by a login in the format 'firstname.name'. If used it fill the AUTHORS file if the `tree-file` contains it.
- `build-path` is also optional. By default the program build in the current working directory. The build directory must do not contains the same file and directory that the `tree-path` file contains.
- `-r` is an optional flag. If used it removes the tree-file after the execution.

## Examples

Here are some examples of how to use the program. 


First create a file, fill it with the tree command output of the archi that you want. DO NOt paste the first line of the tree command outpout.

Here my `tree` file contains :
```
  ├── AUTHORS
  ├── fractal_canopy
  │   ├── dynamic.c
  │   ├── Makefile
  │   └── static.c
  └── image
      ├── display.c
      ├── grayscale.c
      ├── image.png
      └── Makefile
```

Then you can call the programm in your terminal :

```
  archi /shrek/tree -a andrew.tate ../suuuwi/ -r
```
In this exemple :
 - The program will build the archi in the directory from the relative path `../suuuwi/`
 - The program will build the archi by parsing the file that contains the tree command output from the absolute path `/shrek/tree`
 - The program will fill the `AUTHORS` file using the login `zinedine.zidane`
 - The program will remove `/shrek/tree` file

 The content of the `AUTHORS` file after the execution:
 ```
 Zinedine
 ZIDANE 
 zinedine.zidane
 zinedine.zidane@epita.fr
 ```