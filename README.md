# Introduction

A very simple monzo client able to run on Gerda OS. The point was to figure out how to run native code in Gerda OS applications. You could probably interact with the Monzo web api with a webapp in a much easier fashion - no need for C++.

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
  * I will submit a PR with those fixes on day...
