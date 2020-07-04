# Introduction

A very simple monzo client able to run on Gerda OS. The point was to figure out how to run native code in Gerda OS applications. You could probably interact with the Monzo web api with a webapp in a much easier fashion - no need for C++.

# How It Works

The GAB file format allows for specifying a custom start command run by the system to start the app. GerdaOS will allocate a port for the app. The app can then serve the interface over HTTP on this designated port.

This is exactly what the C++ code does.

Unfortunately the GAB format is not well supported at the time of writing. Once i managed to get the C++ code running from the GerdaOS interface I lost interest. In principle this approach could be used to develop native apps when code system libraries or hardware access is required. For all other purpouses emscripten would suffice.

# Building and Running

1. Build `libcurl` for android.
2. Create a `lib` directory
3. Place `libcurl` directory in lib directory with includes and binary placed in `include` and `lib` subdirectories of the `libcurl` directory
4. Run `cmake .`
5. Run `make` to build
6. Run `make install` to package app into .gab format in the `bin` directory
7. Run `sh deploy.sh` to push to the downloads folder of plugged in GerdaOS device
8. Run from your phone by navigating to downloads and running the .gab file

# Known Issues

* There is currently a bug with the Gerda OS gab launcher where it will not detect a free port correctly.
  * To resolve you have to edit the gab.gerda.tech app on your phone
