#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bmp.h"
#include "pixel.h"

void print_header_info(BITMAPFILEHEADER *file_header, BITMAPINFOHEADER *info_header);
void print_histogram(char *name, int *pixel_data, size_t n_pixels);
int main(int argc, char const *argv[])
{
    FILE *file = fopen("c2.bmp","rb");
    if(file==NULL) 
    {
        printf("Failed to read a file.\n");
        return 0;
    }

    BITMAPFILEHEADER file_header;
    fread(&file_header,sizeof(file_header),1,file);
    // fread(&file_header.bfType,2,1,file);
    // fread(&file_header.bfSize,4,1,file);
    // fread(&file_header.bfReserved1,2,1,file);
    // fread(&file_header.bfReserved2,2,1,file);
    // fread(&file_header.bfOffBits,4,1,file);

    BITMAPINFOHEADER info_header;
    fread(&info_header,sizeof(info_header),1,file);
    // fread(&info_header.biSize,4,1,file);
    // fread(&info_header.biWidth,4,1,file);
    // fread(&info_header.biHeight,4,1,file);
    // fread(&info_header.biPlanes,2,1,file);
    // fread(&info_header.biBitCount,2,1,file);
    // fread(&info_header.biCompression,4,1,file);
    // fread(&info_header.biSizeImage,4,1,file);
    // fread(&info_header.biXPelsPerMeter,4,1,file);
    // fread(&info_header.biYPelsPerMeter,4,1,file);
    // fread(&info_header.biClrUsed,4,1,file);
    // fread(&info_header.biClrImportant,4,1,file);

    fseek(file,info_header.biSize-40,SEEK_CUR);
    print_header_info(&file_header,&info_header);
    if (info_header.biCompression !=0 || info_header.biBitCount!=24)
    {
        printf("Histogram calculation is not supported.\n");
        return 0;
    }
    

    Pixel *pixel_row = malloc(sizeof(Pixel)*(info_header.biWidth));
    int red[16] ={0}, green[16]={0}, blue[16]={0};
    for (size_t i = 0; i < info_header.biHeight; i++)
    {
        fread(pixel_row,info_header.biWidth*sizeof(Pixel),1,file);
        for (size_t i = 0; i < info_header.biWidth; i++)
        {
            red[pixel_row[i].red/16]++;
            green[pixel_row[i].green/16]++;
            blue[pixel_row[i].blue/16]++;
        }
        fseek(file,1,SEEK_CUR);
    }

    size_t n_pixels = info_header.biHeight* info_header.biWidth;
    print_histogram("Red",red,n_pixels);
    print_histogram("Green",green,n_pixels);
    print_histogram("Blue",blue,n_pixels);

    fclose(file);
    
    


    return 0;
}
void print_header_info(BITMAPFILEHEADER *file_header, BITMAPINFOHEADER *info_header)
{
    printf("BITMAPFILEHEADER:\n");
    printf("\tbfType:\t\t0x%X\t(%c%c)\n",file_header->bfType,(file_header->bfType) & 0xFF,(file_header->bfType>>8) & 0xFF);
    printf("\tbfSize:\t\t%d\n",file_header->bfSize);
    printf("\tbfReserved1:\t0x%X\n",file_header->bfReserved1);
    printf("\tbfReserved2:\t0x%X\n",file_header->bfReserved2);
    printf("\tbfOffBits:\t%u\n",file_header->bfOffBits);

    printf("BITMAPINFOHEADER:\n");
    printf("\tbiSize:\t\t%u\n",info_header->biSize);
    printf("\tbiWidth:\t%d\n",info_header->biWidth);
    printf("\tbiHeight:\t%d\n",info_header->biHeight);
    printf("\tbiPlanes:\t%u\n",info_header->biPlanes);
    printf("\tbiBitCount:\t%u\n",info_header->biBitCount);
    printf("\tbiCompression:\t%u\n",info_header->biCompression);
    printf("\tbiSizeImage:\t%u\n",info_header->biSizeImage);
    printf("\tbiXPelsPerMeter\t%d\n",info_header->biXPelsPerMeter);
    printf("\tbiYPelsPerMeter\t%d\n",info_header->biYPelsPerMeter);
    printf("\tbiClrUsed\t%u\n",info_header->biClrUsed);
    printf("\tbiClrImportant\t%u\n",info_header->biClrImportant);
}

void print_histogram(char *name, int *pixel_data, size_t n_pixels )
{
    printf("%s:\n",name);
    for (size_t i = 0; i < 16; i++)
    {
        printf("\t%lu-%lu:   \t%.2f%%\n",i*16,(i+1)*16-1,(float)pixel_data[i]*100.0/(float)n_pixels);
    }
}