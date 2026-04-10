# OOBEBypass

Win11 OOBE Bypass with (native) GUI for account creation.

## Building

Run either `build_msvc.bat`, or if you have MSYS2 MINGW64 with CLang setup, use
`build_msys2_mingw64.bat`.

### `build_msvc.bat`

Usage: `build_msvc.bat "path/to/build" Debug/Release` (E.g. `build_msvc.bat build Release`)

### `build_msys2_mingw64.bat`

Usage: `build_msys2_mingw64.bat "path/to/build" Debug/Release` (E.g. `build_msys2_mingw64.bat build Release`)

## Using

OOBEBypass has 2 main ways it can be used: Graphical (GUI), and Command Line (CLI).

Follow the following instructions before continuing:

1. Either build it yourself (follow the above instructions), or download the latest version
    from the releases tab.
2. Put the executable on a network accessible location, or on a form of external media
    (E.g. A USB drive), and copy the executable onto the host computer.
3. Use `Shift + F10` to start the Command Prompt.
4. Navigate to where you copied the file to (Use `cd`, and `dir` to check if the folder
    you are in has the executable)
5. Run the executable (E.g. `OOBEBypass.exe`), and if it gives you any Windows "Smart"screen
    popups, navigate through them and make sure that the executable runs.
    Windows will most likely flag this as malicious because this does various things to bypass
    the OOBE that Windows just doesn't like.

    (**NOTE**: If you do not wish to use the GUI, please continue to [Using the CLI](#using-the-cli)
    before completing this step, as there are more instructions as to what to append to the end of
    the executable as parameters)
6. Let the program do it's magic.

If you are using a Hyper-V virtual machine to test this, use the following command to copy the file into
the Virtual Machine (Run it as Administrator):
```ps
Copy-VMFile "VMName" -SourcePath "F:\Test.txt" -DestinationPath "C:\Temp\Test.txt" -CreateFullPath -FileSource Host```

If you are developing the program, it is best to create a `copy.ps1` script, as that is in the `.gitignore` file.

### Using the GUI

### Using the CLI
