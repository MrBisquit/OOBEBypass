@echo off

REM Windows build script for OOBEBYPASS (BATCH script)
REM ---------------------------------------------------------
REM >>>>>
REM >>>>>   THIS USES MSYS2 MINGW64, WHICH REQUIRES EXTRA
REM >>>>>   SETUP STEPS, TO USE MSVC, RUN THE OTHER SCRIPT
REM >>>>>
REM ---------------------------------------------------------
REM Options:
REM     build_msys2_mingw64.bat "path/to/build" Debug/Release "path/to/vcpkg/toolchain/file.cmake"
REM Example:
REM     build_msys2_mingw64.bat build Debug "G:\vcpkg\scripts\buildsystems\vcpkg.cmake"

if not exist %1 (
    echo %1 does not exist, creating...
    mkdir %1
)

if not %2 == Debug if not %2 == Release (
    echo %2 is not a valid option
    exit /B 1
)

cd %1

if %2 == Debug (
    echo Building with Debug configuration

    cmake .. -G "Ninja" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
    cmake --build . --config Debug
) else if %2 == Release (
    echo Building with Release configuration

    cmake .. -G "Ninja" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
    cmake --build . --config Release
)

cd ..