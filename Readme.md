# SKELETON PROJECT


## build and run on [**STM32F407G-DISC1**](https://www.st.com/en/evaluation-tools/stm32f4discovery.html) evaluation board

### Prerequisites ###

- **arm-none-eabi-gcc** [toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads).
- [**stlink**](https://github.com/texane/stlink) to flash binaries into the development board. Some distribution have packages for this.
- standard development tools: **CMake**, **make**, **git**
- **python** and **python3** (both command must be present and running on the development machine).
- may be Im missing some....

### configure and build ###

```bash
cmake -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi-libopencm3.toolchain  -DCMAKE_INSTALL_PREFIX=./cmake-build/binaries -S. -Bcmake-build -DCMAKE_BUILD_TYPE=Release
make -C cmake-build/
#run
st-flash --reset write  cmake-build/test_xxx  0x8000000
```

## Cmake configuration flags

