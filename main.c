#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"


int main(int argc, char const *argv[])
{
    FILE *file = fopen("tux.bmp","rb");
    if(file==NULL) 
    {
        printf("Failed to read a file.\n");
        return 0;
    }

    BITMAPFILEHEADER file_header;
    fread(&file_header.bfType,2,1,file);
    fread(&file_header.bfSize,4,1,file);
    fread(&file_header.bfReserved1,2,1,file);
    fread(&file_header.bfReserved2,2,1,file);
    fread(&file_header.bfOffBits,4,1,file);

    BITMAPINFOHEADER info_header;
    fread(&info_header.biSize,4,1,file);
    fread(&info_header.biWidth,4,1,file);
    fread(&info_header.biHeight,4,1,file);
    fread(&info_header.biPlanes,2,1,file);
    fread(&info_header.biBitCount,2,1,file);
    fread(&info_header.biCompression,4,1,file);
    fread(&info_header.biSizeImage,4,1,file);
    fread(&info_header.biXPelsPerMeter,4,1,file);
    fread(&info_header.biYPelsPerMeter,4,1,file);
    fread(&info_header.biClrUsed,4,1,file);
    fread(&info_header.biClrImportant,4,1,file);

    fseek(file,info_header.biSize-40,SEEK_CUR);
    LONG buff=0;
    fread(&buff,2,1,file);
    printf("%X\n",buff);


        


    fclose(file);
    
    


    return 0;
}
