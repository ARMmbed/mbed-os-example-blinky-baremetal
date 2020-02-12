![](./resources/official_armmbed_example_badge.png)
# Bare metal blinky Mbed OS example

This example shows how to achieve memory optimizations in Mbed OS. Starting with a blinky application, the example illustrates how to enable the bare metal profile and further memory optimizations.

You can build this project with all supported [Mbed OS build tools](https://os.mbed.com/docs/mbed-os/latest/tools/index.html). However, this example project specifically refers to the command-line interface tool [Arm Mbed CLI](https://github.com/ARMmbed/mbed-cli#installing-mbed-cli).

1. Install Mbed CLI.
1. Clone this repository on your system.
1. Change the current directory to where the project was cloned.

## Application functionality

The `main()` function toggles the state of a digital output connected to an LED on the board.

## Building and running

1. Connect a USB cable between the USB port on the target and the host computer.
1. Run the following command to build the example project and program the microcontroller flash memory:

   ```bash
   $ mbed compile -m <TARGET> -t <TOOLCHAIN> --flash --sterm
   ```
   
Note: You can use the Mbed CLI command-line option "--sterm" to open a serial terminal after flashing.

Your PC may take a few minutes to compile your code.

The binary is located at `./BUILD/<TARGET>/<TOOLCHAIN>/mbed-os-example-blinky-baremetal.bin`.

Alternatively, you can manually copy the binary to the target, which gets mounted on the host computer through USB.

Depending on the target, you can build the example project with the `GCC_ARM`, `ARM` or `IAR` toolchain. After installing Arm Mbed CLI, run the command below to determine which toolchain supports your target:

```bash
$ mbed compile -S
```

## Expected output 

The LED on your target turns on and off every 500 milliseconds, and the serial terminal shows an output similar to: 

``` 
--- Terminal on /dev/tty.usbmodem21102 - 9600,8,N,1 ---
This is the bare metal blinky example running on Mbed OS 99.99.99.
``` 

## Configuring the application

### The bare metal mode

The bare metal mode is a configuration of Mbed OS that excludes the RTOS, as well as other features. We designed it specifically for memory-constrained devices because it gives you more control over the system. For more details, please see [the bare metal documentation](https://os.mbed.com/docs/mbed-os/latest/reference/mbed-os-bare-metal.html)

To build with the bare metal profile, the application configuration file must contain:

```
{
    "requires": ["bare-metal"]
}
```

### Futher optimizations

#### Linking with smaller C libraries

Both the `ARM` and `GCC_ARM` toolchains support optimized versions of their C standard libraries, microlib and newlib-nano. We recommend using them with the bare metal profile.

To build with the smaller C libraries, modify the application configuration file:

```
{
    "target_overrides": {
        "*": {
            "target.c_lib": "small"
        }
    }
}
```

If the build system throws an error when compiling with the small C library, you can find more information [here]( https://github.com/ARMmbed/mbed-os-5-docs/blob/development/docs/program-setup/bare_metal/c_small_libs.md).

#### Using Mbed minimal printf library

Mbed OS offers a smaller `printf()` alternative. The [minimal printf](https://github.com/ARMmbed/mbed-os/blob/master/platform/source/minimal-printf/README.md) library implements a subset of the `v/s/f/printf` function family, and you can disable floating points to save additional code size.

To build with the minimal printf library and disable floating points printing, you need to modify the application configuration file:

```
{
    "target_overrides": {
        "*": {
            "target.printf_lib": "minimal-printf",
            "platform.minimal-printf-enable-floating-point": "false"
        }
    }
}
```

Further optimizations are possible. For more details, please see the minimal printf README.

#### Using a minimal console

If your application only needs unbuffered I/O operations, you can save additional memory by using a configuration of the platform library, which removes file handling functionality from the [system I/O retarget code](https://github.com/ARMmbed/mbed-os/blob/master/platform/source/mbed_retarget.cpp).

To build with the minimal console functionality, modify the application configuration file:

```
{
    "target_overrides": {
        "*": {
            "platform.stdio-minimal-console-only": "true"
        }
    }
}
```

#### Memory comparison

The below table shows the result for the blinky bare metal application compiled with the release profile on K64F for two toolchains.

The baseline configuration used is the blinky bare metal application built with the standard C library.

GCC_ARM:

|Standard C lib|Small C lib|Minimal printf|Minimal console|RAM|Flash|
| :---:        | :---:     | :---:        | :---:         | :---: | :---: |
| X            |           |              |               | 0 | 0 |
|              | X         |              |               | -2,592 | -24,727 |
| X            |           | X            |               | 0 | -14,700 | 
|              | X         | X            |               | -2,592 | -24,338 |
| X            |           |              | X             | 0 | -904 |
|              | X         | X            | X             | -2,592 | -25,226 |
|              | X         |              | X             |  **-2,592** | **-25,615** |

Arm Compiler 6:

|Standard C lib|Small C lib|Minimal printf|Minimal console|RAM|Flash|
| :---:        | :---:     | :---:        | :---:         | :---: | :---: |
| X            |           |              |               | xxxxx | 0 |
|              | X         |              |               | xxxxx | -6,820 |
| X            |           | X            |               | xxxxx | -5,555 | 
|              | X         | X            |               | xxxxx | -8.878 |
| X            |           |              | X             | xxxxx | -1,698 |
|              | X         | X            | X             | xxxxx | **-10,348** |
|              | X         |              | X             | xxxxx | -8,290 |

## Troubleshooting 

If you have problems, you can review the [documentation](https://os.mbed.com/docs/latest/tutorials/debugging.html) for suggestions on what could be wrong and how to fix it. 

## Related links 

- [Mbed OS bare metal](https://os.mbed.com/docs/mbed-os/latest/reference/mbed-os-bare-metal.html).
- [Mbed OS configuration](https://os.mbed.com/docs/latest/reference/configuration.html). 
- [Mbed OS serial communication](https://os.mbed.com/docs/latest/tutorials/serial-communication.html). 
- [Mbed boards](https://os.mbed.com/platforms/).

### License and contributions

The software is provided under the Apache-2.0 license. Contributions to this project are accepted under the same license. Please see contributing.md for more information.

This project contains code from other projects. The original license text is included in those source files. They must comply with our license guide.
