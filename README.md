# Mango

Mango is a powerful command-line tool that converts images into ASCII art and displays them in the terminal with advanced color support.

![screen shot v2.1](doc/screenshot-2.1.png)

## Features

- Supports multiple image formats (PNG, JPEG, BMP, JPG, JFIF, GIF)
- True Color support for more accurate color representation (16 million colors)
- Customizable padding for output
- Adjustable maximum width for resizing large images
- Colored output using terminal escape sequences
- Bold output characters for improved visibility
- Cross-platform compatibility (Windows and Linux)
- Simple and intuitive command-line interface

## Requirements

- Terminal with color support (True Color support recommended)
- C compiler (GCC or Clang recommended)
- Git

## Setup

Before building the project, you need to clone the `stb` repository to get the required header files:

1. Open a terminal and navigate to the project root directory.

2. Run the following command to clone the `stb` repository into the `src/stb` directory:
   ```
   git clone https://github.com/nothings/stb src/stb
   ```

   This will create a `src/stb` directory containing all the necessary header files, including `stb_image.h` and `stb_image_resize2.h`.

## Usage

After building the project, you can run Mango with the following syntax:

```
./mango [options] <file-path>
```

### Options

- `-p, --pad <value>`: Set padding (default: 1)
- `-w, --width <value>`: Set maximum width (default: console width)
- `-t, --true-color`: Enable True Color mode
- `-v, --version`: Display version information
- `-h, --help`: Display help message

## Examples

1. Convert an image with default settings:
   ```
   ./mango image.png
   ```

2. Convert an image with custom padding and width:
   ```
   ./mango -p 2 -w 100 image.jpg
   ```

3. Convert an image using True Color mode:
   ```
   ./mango -t image.gif
   ```

## Changelog

For a detailed list of changes and version history, please see the [CHANGELOG.md](CHANGELOG.md) file.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [stb](https://github.com/nothings/stb) library for image loading and resizing
- Inspired by various terminal-based image viewers