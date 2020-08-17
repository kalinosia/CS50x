#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
//#include <string.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
     if (argc < 2) 
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }
    
    FILE *fileCard = fopen(argv[1], "r");//open card.raw ->FILE *f=fopen(filename, "r");
    if (fileCard == NULL)
    {
        printf("Could not open.\n");
        fclose(fileCard);
        return 2;
    }
    
    
    
                        //BYTE *buffer=malloc(512); //[512]; ?? what to want
    BYTE buffer[512]; //buffer to read 512 and check first 4 if jpg
    bool firstFile=false; //when we find first jpg
    int z=0;//filename next z++, 001 002 003 ... 999.jpg
    char filename[8]; //XXX.jpg
    FILE *img;//outfile
    
    while (fread(buffer, 512, 1, fileCard)) {   //fread( data, size, number, inptr);
        //(fread(buffer, 512, 1, fileCard));
        if (buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3] & 0xf0)==0xe0){
            
            if (!(firstFile)) firstFile=true; //if first file 
            else fclose(img);//if not first file close first last file then save new
           
            //if (img != NULL) fclose(img);//if any img before
            
            sprintf(filename, "%03i.jpg",z);    
            img=fopen(filename, "w");
            z++;
            //firstFile=true;
    
            fwrite(buffer, sizeof(buffer), 1, img);
        //if (buffer == NULL) fclose(img);
       
        if (img == NULL)
            {
                fclose(img);
                free(buffer);
                fprintf(stderr, "Unable to create image file %s", filename);
                return 3;
            }
        }
        else if (firstFile) fwrite(buffer, sizeof(buffer), 1, img);
    }
    fclose(img);
    fclose(fileCard);
      
                
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
