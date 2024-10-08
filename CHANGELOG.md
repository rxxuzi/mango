# Changelog

## v2.1.0
### Added
- True Color support for more accurate color representation (16 million colors)
- New command line option -t or --true-color to enable True Color mode
- Display of current color mode (True Color or 256 colors) in info output
- Output characters are now displayed in bold for improved visibility

## Changed
- Optimized buffer usage for large images

## v2.0.0
### Added
- Linux support for cross-platform compatibility

## v1.2.0
### Changed
- Default padding changed to 1 for better image quality
- Default output character changed from '@' to '#' for improved visibility

### Added
- Automatic adjustment to console width when width is not specified
- `--version` (-v) option to display version information

### Improved
- Error handling for console width detection

## v1.1.0
### Added
- Maximum width option for resizing large images

### Changed
- Updated to use stb_image_resize2.h for improved image resizing

## v1.0.0
### Added
- Initial release of mango
- Basic functionality to convert images to ASCII art
- Support for various image formats (PNG, JPEG, BMP, JPG, JFIF, GIF)
- Command line options for customization (padding, width)