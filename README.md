# APACHE NUTTX (INCUBATING)

- `make distclean`
- `./tools/configure.sh -L | less`
- `./tools/configure.sh -L | grep imxrt`
- `./tools/configure.sh -l imxrt1052-onekiwi-evk:nsh`
- `make menuconfig`
- `make savedefconfig`
- `make -j8`