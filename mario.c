#include<cs50.h>
#include<stdio.h>

void print_row(int bricks);

int main(void)
{
    int height;
    do
    {
        height = get_int("height: ");
    }
    while (height < 1 || height > 8);

    int row = 0;
    while (row < height)
    {
        for (int i = 0; i < height - row - 1; i++)
        {
            printf(" ");
        }
        for (int j = 0; j < row + 1; j++)
        {
            printf("#");
        }
        printf("\n");
        row++;
    }
}
