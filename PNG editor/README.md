# BMP editor with steganography #
Picture format:
* BMP picture 
* DIB format - BITMAPINFOHEADER
* 24 bits per pixel
* No palette

Options:
* ./main crop-rotate \<in-bmp\> \<out-bmp\> \<x\> \<y\> \<w\> \<h\> // where x y - left top corner,
w - width, h - height. Crops specified part of the picture and rotate 90.
* ./main insert \<in-bmp\> \<out-bmp\> \<key-txt\> \<msg-txt\>
* ./main extract \<in-bmp\> \<key-txt\> \<msg-txt\>

each line in key-txt consists of two numbers x, y - pixel position and symbol
(R, G, B) pointing to pixel color, where message inserts
