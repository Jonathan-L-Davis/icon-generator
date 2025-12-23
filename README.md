# Jon's icon-generator

Generates \*.ico files.<br><br>

Can only encode .png files.<br><br>

Doesn't do any error checking, so be wary.<br>
.ico files can only encode .bmp or .png files.<br><br>

There are some constraints on the png files that I can't check without parsing png's.<br>
Namely "The file header must be in 32bpp ARGB format"<br><br>

Hopefully it's not necessary to generate mask data for the png's. (It is for bmp's).<br>
