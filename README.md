# Mango

Mango is a command-line tool that converts images into ASCII art and displays them in the terminal with color support.

![screen shot v1.0](doc/img.png)

## Features

- Supports multiple image formats (PNG, JPEG, BMP, JPG, JFIF, GIF)
- Customizable padding for output
- Adjustable maximum width for resizing large images
- Colored output using terminal escape sequences
- Simple and intuitive command-line interface

## Requirements

- Terminal with color support
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

- `-p, --pad <value>`: Set padding (default: 3, auto-set to 1 if width is specified)
- `-w, --width <value>`: Set maximum width (default: no limit)
- `-h, --help`: Display help message

### Examples

To convert an image named "example.png" with a padding of 2:

```
./mango -p 2 example.png
```

To convert an image and set its maximum width to 80 characters:

```
./mango -w 80 example.png
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [stb](https://github.com/nothings/stb) library for image loading and resizing
- Inspired by various terminal-based image viewers