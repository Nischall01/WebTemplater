# WebTemplater

WebTemplater is a basic CLI program designed to quickly set up a barebones web development project structure. It creates a folder with optional date-based naming, generates HTML, CSS, and JavaScript files using predefined (and modifiable) templates, and automatically links the files. This tool is perfect for beginners or for quick prototyping!

## Features

- **Quick Setup**: Easily create a new web project with a predefined structure.
- **Template Generation**: Automatically generate HTML, CSS, and JavaScript files from customizable templates.
- **Date-Based Naming**: Optionally create project folders with date-based naming for better organization.
- **File Linking**: Automatically link generated files for immediate use.

## Installation

You can download the [latest release](https://github.com/Nischall01/WebTemplater/releases/latest) and simply extract the program directory.

Or,

To build WebTemplater yourself, follow these steps:

1. Clone the repository:

   ```pwsh
   git clone https://github.com/Nischall01/WebTemplater.git
   ```

2. Navigate to the project directory and then to the _src_ directory

   ```pwsh
   cd WebTemplater/src
   ```

3. Use a compiler of your choice to compile the src files

   ```pwsh
   gcc -o webtem WebTemplater.c userinput.c
   ```

> [!NOTE]
> The _Templates_ directory and the executable must be in the same parent directory for the program to function. _Add the directory to path_ to use it from any location in your system.

## How to use

After installing WebTemplater and [_adding the directory to the path_](https://www.eukhost.com/kb/how-to-add-to-the-path-on-windows-10-and-windows-11/), simply call "webtem" in your terminal to use the program.

> [!Note]
> You can modify each template to your liking. However, in the HTML template, the `<head>` and `<body>` tags are required for the program to function correctly. Do not rename the template files.

## Screenshots

![Screenshot 1](./media/screenshots/Screenshot%201.png)
![Screenshot 1](./media/screenshots/Screenshot%202.png)
![Screenshot 1](./media/screenshots/Screenshot%203.png)
![Screenshot 1](./media/screenshots/Screenshot%204.png)
