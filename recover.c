#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
     if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");//open card.raw ->FILE *f=fopen(filename, "r");
    if (file == NULL)
    {
        printf("Could not open.\n");
        fclose(file);
        return 1;
    }
    //filenames XXX.jpg 000.jpg
    //sprintf(filename, "%03i.jpg",2);
    //FILE *img=fopen(filename, "w");
    //fread( data, size, number, inptr);
    
    unsigned char buffer[512]; 
    bool writing=false;
    int z=0;
    char filename[7];
    FILE *img;
    
    while (fread(&buffer, 512, 1, file)) {   //why1
       // if (buffer == NULL) break;
    
        if (buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3] & 0xf0)==0xe0){
            if (img != NULL) fclose(img);
            
            sprintf(filename, "%03i.jpg",z);    
            img=fopen(filename, "w");
            z++;
            writing=true;
        }
        if (writing == 1) fwrite(buffer, sizeof(buffer), 1, img);
        //if (buffer == NULL) fclose(img);
    }
    fclose(img);
    fclose(file);
      
                
    //fread( int buffer[512], 512, number, file);
    //z=0;
    //for (int i=0; i<size; i+512){
    //if(buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3] & 0xf0)==0xe0){
      //  if(buffer[i]==0xff && buffer[i+1]==0xd8 && buffer[i+2]==0xff && (buffer[i+33] & 0xf0)==0xe0){
            
            
            
      //      fwrite( data, size, number, outptr);
       
    //0xe1 0xe2 ... 0xef
    //each block 512 bytes
    //for (int i=0; i<??; i++){
    //    if i = 0xff && i= ...
    //    open
     //   while i = 0xff
       // close
    //    open new
        
    return 0;

}
