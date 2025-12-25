# Jon's icon-generator

Generates \*.ico files.<br>
Got tired of having to rely on websites to create these files.<br>
Currently can only encode .png files.<br><br>
Doesn't do any error checking, so be wary.<br>
.ico files can only encode .bmp or .png files.<br>

There are some constraints on the png files that I can't check without parsing png's.<br>
Namely "The png file header must be in 32bpp ARGB format".<br>
You probably don't need to worry about it so long as your png is valid.<br>

## Usage

./rt/igen -w w1 -h h1 -f img1.png -w w2 -h h2 -f img2.png -o favicon.ico

-o output_file arg pair can be commuted with any other arg pair. If you give more than one, the last one will be taken.<br>
-w W & -h H pairs set the width and height for all subsequent -f input_file pairs.<br>

Since modern software should only grab the image size from the actual image data, instead of the ICONDIRENTRY,
you can probably get away with ignoring -h & -w args, but bewarned, old (pre windows Vista era) software may get grumpy about that.<br>

All info on file format was grabbed from here:<br>
https://en.wikipedia.org/wiki/ICO\_(file\_format)

## Building
./build.sh

Expecting bash and zig installed. You should be able to just run the build command.
Worst case, this is a very simple app. You should be able to build it with any of the major C++ compilers. All files in src get built together. No extra preprocessor defines or anything.
