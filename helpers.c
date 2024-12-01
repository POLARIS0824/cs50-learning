#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 计算当前像素的平均值并四舍五入
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // 将 RGB 分量设置为平均值
            image[i][j].rgbtBlue = (int)avg;
            image[i][j].rgbtGreen = (int)avg;
            image[i][j].rgbtRed = (int)avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 获取原始 RGB 值
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // 计算 sepia 的 RGB 值
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // 确保 RGB 值在 0–255 范围内
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
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
            RGBTRIPLE current;
            current = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = current;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
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
            // 设置像素累加值变量
            int redSum = 0, greenSum = 0, blueSum = 0;
            // 设置有效像素数量变量
            int count = 0;
            // 嵌套循环计算周围像素平均值
            for (int m = -1; m <= 1; m++)
            {
                for (int n = -1; n <= 1; n++)
                {
                    int ni = i + m;
                    int nj = j + n;
                    // 检查边界，跳过边界像素
                    if (ni >= 0 && ni <= height - 1 && nj >= 0 && nj <= width - 1)
                    {
                        redSum += copy[ni][nj].rgbtRed;
                        greenSum += copy[ni][nj].rgbtGreen;
                        blueSum += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }
            // 计算平均值并且改变原图像
            image[i][j].rgbtRed = round((float)redSum / count);
            image[i][j].rgbtGreen = round((float)greenSum / count);
            image[i][j].rgbtBlue = round((float)blueSum / count);
        }
    }
    return;
}
