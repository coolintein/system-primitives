#include <stdio.h> //normal prints and all
#include <stdint.h> //for uint's(bit specific ints)
#include <stdlib.h> //for malloc/free

#pragma pack(push,1)

struct BMPFileHeader{
    uint16_t file_type;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset_data; 
}; //14 bytes

struct BMPInfoHeader{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitcount;
    uint32_t compression;
    uint32_t sizeimage;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
}; //40 bytes

#pragma pack(pop)

int main(){

    FILE* file=fopen("input.bmp","rb"); //rb to read file as raw binary text

    if(file==NULL){
        printf("Error. File not found.");
        return 1;
    }

    printf("Sucessfully Opened the BMP File.\n\n");
    printf("Creating MetaData Storage in memory...\n");

    struct BMPFileHeader header;
    struct BMPInfoHeader info; // metadatas...

    printf("Reading MetaData....\n\n");

    fread(&header,sizeof(struct BMPFileHeader),1,file);
    fread(&info,sizeof(struct BMPInfoHeader),1,file); //reading from bmp file

    printf("Image Width: %d\n", info.width);
    printf("Image Height: %d\n\n", info.height);

    int total_bytes=info.width * info.height * 3;
    printf("Allocating %d bytes of memory in heap....\n",total_bytes);

    uint8_t* pixels=(uint8_t*)malloc(total_bytes);

    if(pixels==NULL){
        printf("Could not allocate required memory.");
        fclose(file);
        return 1;
    }

    printf("Memory allocation Successful\n");

    fseek(file, header.offset_data, SEEK_SET);
    fread(pixels, 1, total_bytes, file);

    printf("%d Bytes of memory loaded into RAM\n\n",total_bytes);

    for(int i=0;i<total_bytes;i+=3){
        uint8_t avg;
        avg=(pixels[i]+pixels[i+1]+pixels[i+2])/3; //int gray = (pixels[i]*29 + pixels[i+1]*150 + pixels[i+2]*77) >> 8;
        pixels[i]=avg;
        pixels[i+1]=avg;
        pixels[i+2]=avg;
    }

    printf("Greyscale filter applied!\n");

    FILE* opfile=fopen("output.bmp","wb");

    if(opfile==NULL){
        printf("File creation failed");
        return 1;
    }

    fwrite(&header,sizeof(struct BMPFileHeader),1,opfile);
    fwrite(&info,sizeof(struct BMPInfoHeader),1,opfile);
    
    fseek(opfile,header.offset_data,SEEK_SET);

    fwrite(pixels,total_bytes,1,opfile);

    printf("Sucessfully saved Greyscale image as output.bmp!\n");
    
    fclose(opfile);
    free(pixels);
    fclose(file);
    return 0;
}