SCP Terminal Viewer
=======

## What does it do?

The SCP Terminal Viewer allows you to browse the SCP Wiki discreetly from the terminal.


![usage demo](https://i.imgur.com/OI9cnoN.gif)

## Installation

### Prerequisites
Have [curl](https://curl.haxx.se/) installed on the system.

#### Windows specific
You may want to type `chcp 65001` in command prompt to allow for unicode characters (in particular, the block character █ commonly in use on a variety of SCPs). However, this can potentially cause issues with a small minority of articles involving quotes. No such issue has been found for other platforms.

### Compiling
`g++ -O2 -std=gnu++11 scp-terminal.cpp -o scp-terminal`

### Direct download (Windows only)
See releases section.

## Usage
Run with `scp-terminal.exe` (Windows) or `./scp-terminal` (most other systems), or just double-click the exe.
Type `help` in the terminal for more info.

## The code
is far from perfect. Significantly far. Feel free to make suggestions and contribute!

## In progress
- Retaining features of the article text ex. bold (currently supported on non-Windows), italic, etc.
- Find ways to allow opening of spoiler sections (ex. click to open classified document). Currently they are all laid out to see.
- Non-hacky way of handling HTML characters

Suggestions are appreciated.