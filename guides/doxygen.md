# Doxygen

## What is Doxygen

Doxygen is a way of documenting code in a way that can be automatically parsed and formatted into
an easy to navigate docs page. 

## Basics

Comments that Doxygen can parse look like the following:

```
/**
 *
 *
 */
```

This is found at the top of each file, as well as above function prototypes or implementations.
Whether you include comments in the source or header (or both) files is up to you, but think about what makes
more sense for your application.

## User Setup

First, get the Doxygen Documentation Generator on VsCode. This will allow you to type `/**` then
click enter and the Doxygen comment will automatically be made with the required fields. 

You can also set up your name, email ect. by adding this to your `settings.json:
```json
    "doxdocgen.generic.authorEmail": "aidenoleary2004@gmail.com",
    "doxdocgen.generic.authorName": "Aiden O'Leary"
```
You can access this file by clicking `ctrl-shift-p` and typing `settings.json`

## Project Setup

Doxygen needs to be added to your project. This is done via a `Doxyfile` which is essentially
a bunch of settings that can be changed according to your project setup. 

To complete this process: 

1. In the root of your project create a `docs/` folder. Populate it with 3 files:
    1. Empty README.md
    2. `doxygen-awesome.css`
    3. `doxygen-awesome-sidebar-only.css`
    
    You can grab these files from another existing `docs/` folder
2. Copy an existing Doxyfile and make the following edits:
    1. Change the PROJECT_NAME
    2. Change the OUTPUT_DIRECTORY (should be a relative path to the root docs/[prj_name]) directory
    3. Change the INPUT paths for your project. Recursive is a setting that can simplify this

## Docs Generation

To generate doxygen docs, be on linux or open `WSL` and run: 

```bash
sudo apt install doxygen
doxygen
```
in the directory with your Doxyfile

The repository's GitHub Actions workflow builds the BatMan and VCU documentation when either
project changes and publishes both under GitHub Pages. The Pages home page links to each project.