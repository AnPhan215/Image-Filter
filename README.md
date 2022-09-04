# Image-Filter
*This is one of the CS50 projects that I did* 

This program is meant for practice in pset4 of CS50x. One of the course from Harvard University.

You can think of filtering an image as taking the pixels of some original image, and modifying each pixel in such a way that a particular effect is apparent in the resulting image.

My program will let you choose 1 of 4 filters and change the image: Grayscale, Reflection, Blur and Edges

UNDERSTANDING:

**GRAYSCALE**

One common filter is the “grayscale” filter, where we take an image and want to convert it to black-and-white. How does that work?

Recall that if the red, green, and blue values are all set to 0x00 (hexadecimal for 0), then the pixel is black. And if all values are set to 0xff (hexadecimal for 255), then the pixel is white. So long as the red, green, and blue values are all equal, the result will be varying shades of gray along the black-white spectrum, with higher values meaning lighter shades (closer to white) and lower values meaning darker shades (closer to black).

**REFLECTION**

Some filters might also move pixels around. Reflecting an image, for example, is a filter where the resulting image is what you would get by placing the original image in front of a mirror. So any pixels on the left side of the image should end up on the right, and vice versa.

**BLUR**

There are a number of ways to create the effect of blurring or softening an image. For this problem, I’ll use the “box blur,” which works by taking each pixel and, for each color value, giving it a new value by averaging the color values of neighboring pixels.

Consider the following grid of pixels, where we’ve numbered each pixel.

![image](https://user-images.githubusercontent.com/81196027/188294798-f05a758b-a880-4fd5-bdb4-6386755a7b8f.png)

The new value of each pixel would be the average of the values of all of the pixels that are within 1 row and column of the original pixel (forming a 3x3 box). For example, each of the color values for pixel 6 would be obtained by averaging the original color values of pixels 1, 2, 3, 5, 6, 7, 9, 10, and 11 (note that pixel 6 itself is included in the average). Likewise, the color values for pixel 11 would be be obtained by averaging the color values of pixels 6, 7, 8, 10, 11, 12, 14, 15 and 16.

For a pixel along the edge or corner, like pixel 15, we would still look for all pixels within 1 row and column: in this case, pixels 10, 11, 12, 14, 15, and 16.

**EDGES**

In artificial intelligence algorithms for image processing, it is often useful to detect edges in an image: lines in the image that create a boundary between one object and another. One way to achieve this effect is by applying the Sobel operator to the image.

IMPLEMENTATION

I'm using a 24-bit BMP files/image as an input for this program. 

In the #filter.c file, you can notice the definition of filters on line 11. That string tells the program what the allowable command-line arguments to the program are: b, e, g, and r. Each of them specifies a different filter that we might apply to our images: blur, edge detection, grayscale, and reflection. 

Example execution: ./filter -g images/yard.bmp out.bmp

which takes the image at images/yard.bmp, and generates a new image called out.bmp after running the pixels through the grayscale function. 


