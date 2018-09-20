# ft_ls

## About ft_ls

* ft_ls is the replica of the [ls](http://man.openbsd.org/ls) command.

## What do you need to compile ft_ls ?

* gcc or clang

* make

* C library

* ar

## How to compile ft_ls ?

* Use `make` to compile `ft_ls`.

## Usage:

* `./ft_ls [-Rlartgs1of] [file ...]`

## Rules of Makefile:

all: compile `libft.a`, `ft_ls`

clean: delete objects

fclean: call clean and delete `libft.a`, `ft_ls`

re: call fclean and all

## Notes:

* this project was done on macOS, the compilation can fail on Linux distrubution.
