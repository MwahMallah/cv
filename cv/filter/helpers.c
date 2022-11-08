#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            float new_val = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.00;
            image[i][j].rgbtBlue = round(new_val);
            image[i][j].rgbtRed = round(new_val);
            image[i][j].rgbtGreen = round(new_val);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tmpRed, tmpBlue, tmpGreen;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tmpRed = image[i][j].rgbtRed;
            tmpGreen = image[i][j].rgbtGreen;
            tmpBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = tmpRed;
            image[i][width - j - 1].rgbtGreen = tmpGreen;
            image[i][width - j - 1].rgbtBlue = tmpBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpval[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;

            int counter = 0;

            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    if (i + y < 0 || i + y > height -1 || j + x < 0 || j + x > width - 1)
                    {
                        continue;
                    }
                    sumRed += image[i+y][j+x].rgbtRed;
                    sumGreen += image[i+y][j+x].rgbtGreen;
                    sumBlue += image[i+y][j+x].rgbtBlue;

                    counter++;
                }
            }
            tmpval[i][j].rgbtRed = round(sumRed / counter);
            tmpval[i][j].rgbtGreen = round(sumGreen / counter);
            tmpval[i][j].rgbtBlue = round(sumBlue / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmpval[i][j].rgbtRed;
            image[i][j].rgbtBlue = tmpval[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmpval[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};

    RGBTRIPLE tmpval[height][width];
    RGBTRIPLE fin_val, GXval, GYval;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            GXval.rgbtRed = 0;
            GXval.rgbtGreen = 0;
            GXval.rgbtBlue = 0;

            GYval.rgbtRed = 0;
            GYval.rgbtGreen = 0;
            GYval.rgbtBlue = 0;


            for (int n = -1; n < 2; n++)
            {
                for (int k = -1; k < 2; k++)
                {
                    if (i + n < 0 || j + k < 0 || i + n > height - 1 || j + k > width - 1)
                    {
                        continue;
                    }

                    GXval.rgbtRed += image[i+n][j+k].rgbtRed * Gx[n+1][k+1];
                    GYval.rgbtRed += image[i+n][j+k].rgbtRed * Gy[n+1][k+1];

                    GXval.rgbtGreen += image[i+n][j+k].rgbtGreen * Gx[n+1][k+1];
                    GYval.rgbtGreen += image[i+n][j+k].rgbtGreen * Gy[n+1][k+1];

                    GXval.rgbtBlue += image[i+n][j+k].rgbtBlue * Gx[n+1][k+1];
                    GYval.rgbtBlue += image[i+n][j+k].rgbtBlue * Gy[n+1][k+1];
                }
            }

            fin_val.rgbtRed = round(sqrt(GXval.rgbtRed*GXval.rgbtRed + GYval.rgbtRed*GYval.rgbtRed));
            if (fin_val.rgbtRed > 255)
            {
                fin_val.rgbtRed = 255;
            }

            fin_val.rgbtGreen = round(sqrt(GXval.rgbtGreen*GXval.rgbtGreen + GYval.rgbtGreen*GYval.rgbtGreen));
            if (fin_val.rgbtGreen > 255)
            {
                fin_val.rgbtGreen = 255;
            }

            fin_val.rgbtBlue = round(sqrt(GXval.rgbtBlue*GXval.rgbtBlue + GYval.rgbtBlue*GYval.rgbtBlue));
            if (fin_val.rgbtBlue > 255)
            {
                fin_val.rgbtBlue = 255;
            }

            tmpval[i][j].rgbtRed = fin_val.rgbtRed;
            tmpval[i][j].rgbtGreen = fin_val.rgbtGreen;
            tmpval[i][j].rgbtBlue = fin_val.rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmpval[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmpval[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmpval[i][j].rgbtBlue;
        }
    }

    return;
}
