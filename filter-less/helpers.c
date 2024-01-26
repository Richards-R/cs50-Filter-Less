#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtRed = round(average);
        }
    }
    return;
}

// Convert image to sepia

// Function to restrict size to 255 or less
int checksize(pix_size)
{
    if (pix_size > 255)
    {
        return 255;
    }
    else
    {
        return pix_size;
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            image[i][j].rgbtBlue = checksize(round(sepiaBlue));
            image[i][j].rgbtGreen = checksize(round(sepiaGreen));
            image[i][j].rgbtRed = checksize(round(sepiaRed));
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
            RGBTRIPLE left_pix_temp = image[i][j];
            RGBTRIPLE right_pix_temp = image[i][width - j - 1];
            image[i][j] = right_pix_temp;
            image[i][width - j - 1] = left_pix_temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            float average_blue;
            float average_green;
            float average_red;
            float sum_blue = 0.0;
            float sum_green = 0.0;
            float sum_red = 0.0;
            float divisor = 9.0;

            for (int k = -1; k <= 1; k++)
            {

                for (int l = -1; l <= 1; l++)

                {
                    if (i + k < 0 || i + k > height - 1 || j + l < 0 || j + l > width - 1)
                    {
                        divisor--;
                    }
                    else
                    {
                        sum_blue += copy[i + k][j + l].rgbtBlue;
                        sum_green += copy[i + k][j + l].rgbtGreen;
                        sum_red += copy[i + k][j + l].rgbtRed;
                    }
                }
            }
            average_blue = sum_blue / divisor;
            average_green = sum_green / divisor;
            average_red = sum_red / divisor;

            image[i][j].rgbtBlue = round(average_blue);
            image[i][j].rgbtGreen = round(average_green);
            image[i][j].rgbtRed = round(average_red);
        }
    }
    return;
}
