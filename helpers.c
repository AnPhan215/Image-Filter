#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //getting averaging value
            int avr = (int)roundf((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            //Change color value to avr value
            image[i][j].rgbtRed = avr;
            image[i][j].rgbtGreen = avr;
            image[i][j].rgbtBlue = avr;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int tmp = 0;
            //Swap Red channel
            tmp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][(width - 1) - j].rgbtRed;
            image[i][(width - 1) - j].rgbtRed = tmp;

            //Swap Green channel
            tmp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][(width - 1) - j].rgbtGreen;
            image[i][(width - 1) - j].rgbtGreen = tmp;

            //Swap Blue channel
            tmp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][(width - 1) - j].rgbtBlue;
            image[i][(width - 1) - j].rgbtBlue = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    //copy image to copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //blur image from copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0.0;

            //make surround area
            for (int m = i - 1; m < (i + 2); m++)
            {
                for (int n = j - 1; n < (j + 2); n++)
                {
                    if ((m >= 0) && (m < height) && (n >= 0) && (n < width))
                    {
                        //Get sum from copy
                        sumRed += copy[m][n].rgbtRed;
                        sumGreen += copy[m][n].rgbtGreen;
                        sumBlue += copy[m][n].rgbtBlue;
                        count++;
                    }
                }
            }

            //Extract data from copy and write it to image
            image[i][j].rgbtRed = (int)roundf(sumRed / (float)count);
            image[i][j].rgbtGreen = (int)roundf(sumGreen / (float)count);
            image[i][j].rgbtBlue = (int)roundf(sumBlue / (float)count);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    //copy image to copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    printf("\n");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRedX = 0, sumGreenX = 0, sumBlueX = 0;
            int sumRedY = 0, sumGreenY = 0, sumBlueY = 0;
            int count = 0;
            //make surround area
            for (int m = i - 1; m < (i + 2); m++)
            {
                for (int n = j - 1; n < (j + 2); n++)
                {
                    if ((m >= 0) && (m < height) && (n >= 0) && (n < width))
                    {
                        sumRedX += (Gx[count] * copy[m][n].rgbtRed);
                        sumGreenX += (Gx[count] * copy[m][n].rgbtGreen);
                        sumBlueX += (Gx[count] * copy[m][n].rgbtBlue);
                        sumRedY += (Gy[count] * copy[m][n].rgbtRed);
                        sumGreenY += (Gy[count] * copy[m][n].rgbtGreen);
                        sumBlueY += (Gy[count] * copy[m][n].rgbtBlue);
                        count++;
                    }
                    else
                    {
                        sumRedX += (Gx[count] * 0);
                        sumGreenX += (Gx[count] * 0);
                        sumBlueX += (Gx[count] * 0);
                        sumRedY += (Gy[count] * 0);
                        sumGreenY += (Gy[count] * 0);
                        sumBlueY += (Gy[count] * 0);
                        count++;
                    }
                }
            }

            //Edges

            //For Red
            if ((int)roundf(sqrt(pow(sumRedX, 2) + pow(sumRedY, 2))) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = (int)roundf(sqrt(pow(sumRedX, 2) + pow(sumRedY, 2)));
            }

            //For Green
            if ((int)roundf(sqrt(pow(sumGreenX, 2) + pow(sumGreenY, 2))) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = (int)roundf(sqrt(pow(sumGreenX, 2) + pow(sumGreenY, 2)));
            }

            //For Blue
            if ((int)roundf(sqrt(pow(sumBlueX, 2) + pow(sumBlueY, 2))) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = (int)roundf(sqrt(pow(sumBlueX, 2) + pow(sumBlueY, 2)));
            }
        }
    }

    return;
}
