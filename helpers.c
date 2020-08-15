#include "helpers.h"
#include <math.h>//square root

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            int gray=round(((float)image[i][j].rgbtRed+(float)image[i][j].rgbtGreen+(float)image[i][j].rgbtBlue)/3);
            image[i][j].rgbtRed=gray;
            image[i][j].rgbtGreen=gray;
            image[i][j].rgbtBlue=gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE hold[1][1];

    /*int h;
    int w;

    if(height%2==0) h=height/2;
    else if (height%2==1) h=height/2+1;
    if (width%2==0) w=width/2;
    else if (width%2==1) w=width/2+1;
    */
    
    for (int i=0; i<height; i++){
        int l=1;
        for (int j=0; j<width/2; j++){
            hold[0][0]=image[i][j];
            image[i][j]=image[i][width-l];
            image[i][width-l]=hold[0][0];

            l++;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE hold[height][width];

    for (int i=1; i<height-1; i++){
        for (int j=1; j<width-1; j++){
            hold[i][j].rgbtRed=round((float)(
            image[i-1][j-1].rgbtRed+image[i-1][j].rgbtRed+image[i-1][j+1].rgbtRed+
            image[i][j-1].rgbtRed+image[i][j].rgbtRed+image[i][j+1].rgbtRed+
            image[i+1][j-1].rgbtRed+image[i+1][j].rgbtRed+image[i+1][j+1].rgbtRed)/9);

            hold[i][j].rgbtGreen=round((float)(
            image[i-1][j-1].rgbtGreen+image[i-1][j].rgbtGreen+image[i-1][j+1].rgbtGreen+
            image[i][j-1].rgbtGreen+image[i][j].rgbtGreen+image[i][j+1].rgbtGreen+
            image[i+1][j-1].rgbtGreen+image[i+1][j].rgbtGreen+image[i+1][j+1].rgbtGreen)/9);

            hold[i][j].rgbtBlue=round((float)(
            image[i-1][j-1].rgbtBlue+image[i-1][j].rgbtBlue+image[i-1][j+1].rgbtBlue+
            image[i][j-1].rgbtBlue+image[i][j].rgbtBlue+image[i][j+1].rgbtBlue+
            image[i+1][j-1].rgbtBlue+image[i+1][j].rgbtBlue+image[i+1][j+1].rgbtBlue)/9);
        }
    }
    for (int i=1; i<height-1; i++){//pionowo lewo
        hold[i][0].rgbtRed=round((float)(
            image[i-1][0].rgbtRed+image[i-1][1].rgbtRed+
            image[i][0].rgbtRed+image[i][1].rgbtRed+
            image[i+1][0].rgbtRed+image[i+1][1].rgbtRed)/6);

            hold[i][0].rgbtGreen=round((float)(
            image[i-1][0].rgbtGreen+image[i-1][1].rgbtGreen+
            image[i][0].rgbtGreen+image[i][1].rgbtGreen+
            image[i+1][0].rgbtGreen+image[i+1][1].rgbtGreen)/6);

            hold[i][0].rgbtBlue=round((float)(
            image[i-1][0].rgbtBlue+image[i-1][1].rgbtBlue+
            image[i][0].rgbtBlue+image[i][1].rgbtBlue+
            image[i+1][0].rgbtBlue+image[i+1][1].rgbtBlue)/6);
    }
    for (int i=1; i<height-1; i++){//pionowo prawa j=width
        hold[i][width-1].rgbtRed=round((float)(
            image[i-1][width-2].rgbtRed+image[i-1][width-1].rgbtRed+
            image[i][width-2].rgbtRed+image[i][width-1].rgbtRed+
            image[i+1][width-2].rgbtRed+image[i+1][width-1].rgbtRed)/6);

            hold[i][width-1].rgbtGreen=round((float)(
            image[i-1][width-2].rgbtGreen+image[i-1][width-1].rgbtGreen+
            image[i][width-2].rgbtGreen+image[i][width-1].rgbtGreen+
            image[i+1][width-2].rgbtGreen+image[i+1][width-1].rgbtGreen)/6);

            hold[i][width-1].rgbtBlue=round((float)(
            image[i-1][width-2].rgbtBlue+image[i-1][width-1].rgbtBlue+
            image[i][width-2].rgbtBlue+image[i][width-1].rgbtBlue+
            image[i+1][width-2].rgbtBlue+image[i+1][width-1].rgbtBlue)/6);
    }
    for (int j=1; j<width-1; j++){//poziomo góra
        hold[0][j].rgbtRed=round((float)(
            image[0][j-1].rgbtRed+image[0][j].rgbtRed+image[0][j+1].rgbtRed+
            image[1][j-1].rgbtRed+image[1][j].rgbtRed+image[1][j+1].rgbtRed)/6);

            hold[0][j].rgbtGreen=round((float)(
            image[0][j-1].rgbtGreen+image[0][j].rgbtGreen+image[0][j+1].rgbtGreen+
            image[1][j-1].rgbtGreen+image[1][j].rgbtGreen+image[1][j+1].rgbtGreen)/6);

            hold[0][j].rgbtBlue=round((float)(
            image[0][j-1].rgbtBlue+image[0][j].rgbtBlue+image[0][j+1].rgbtBlue+
            image[1][j-1].rgbtBlue+image[1][j].rgbtBlue+image[1][j+1].rgbtBlue)/6);
    }
    for (int j=1; j<width-1; j++){//poziomo dół
        hold[height-1][j].rgbtRed=round((float)(
            image[height-2][j-1].rgbtRed+image[height-2][j].rgbtRed+image[height-2][j+1].rgbtRed+
            image[height-1][j-1].rgbtRed+image[height-1][j].rgbtRed+image[height-1][j+1].rgbtRed)/6);

            hold[height-1][j].rgbtGreen=round((float)(
            image[height-2][j-1].rgbtGreen+image[height-2][j].rgbtGreen+image[height-2][j+1].rgbtGreen+
            image[height-1][j-1].rgbtGreen+image[height-1][j].rgbtGreen+image[height-1][j+1].rgbtGreen)/6);

            hold[height-1][j].rgbtBlue=round((float)(
            image[height-2][j-1].rgbtBlue+image[height-2][j].rgbtBlue+image[height-2][j+1].rgbtBlue+
            image[height-1][j-1].rgbtBlue+image[height-1][j].rgbtBlue+image[height-1][j+1].rgbtBlue)/6);
    }
    //corners
    hold[0][0].rgbtRed=round((float)(image[0][0].rgbtRed+image[0][1].rgbtRed+image[1][0].rgbtRed+image[1][1].rgbtRed)/4);
    hold[0][width-1].rgbtRed=round((float)(image[0][width-2].rgbtRed+image[0][width-1].rgbtRed+image[1][width-2].rgbtRed+image[1][width-1].rgbtRed)/4);
    hold[height-1][0].rgbtRed=round((float)(image[height-1][0].rgbtRed+image[height-2][0].rgbtRed+image[height-1][1].rgbtRed+image[height-2][1].rgbtRed)/4);
    hold[height-1][width-1].rgbtRed=round((float)(image[height-1][width-1].rgbtRed+image[height-1][width-2].rgbtRed+image[height-2][width-2].rgbtRed+image[height-2][width-1].rgbtRed)/4);

    hold[0][0].rgbtGreen=round((float)(image[0][0].rgbtGreen+image[0][1].rgbtGreen+image[1][0].rgbtGreen+image[1][1].rgbtGreen)/4);
    hold[0][width-1].rgbtGreen=round((float)(image[0][width-2].rgbtGreen+image[0][width-1].rgbtGreen+image[1][width-2].rgbtGreen+image[1][width-1].rgbtGreen)/4);
    hold[height-1][0].rgbtGreen=round((float)(image[height-1][0].rgbtGreen+image[height-2][0].rgbtGreen+image[height-1][1].rgbtGreen+image[height-2][1].rgbtGreen)/4);
    hold[height-1][width-1].rgbtGreen=round((float)(image[height-1][width-1].rgbtGreen+image[height-1][width-2].rgbtGreen+image[height-2][width-2].rgbtGreen+image[height-2][width-1].rgbtGreen)/4);

    hold[0][0].rgbtBlue=round((float)(image[0][0].rgbtBlue+image[0][1].rgbtBlue+image[1][0].rgbtBlue+image[1][1].rgbtBlue)/4);
    hold[0][width-1].rgbtBlue=round((float)(image[0][width-2].rgbtBlue+image[0][width-1].rgbtBlue+image[1][width-2].rgbtBlue+image[1][width-1].rgbtBlue)/4);
    hold[height-1][0].rgbtBlue=round((float)(image[height-1][0].rgbtBlue+image[height-2][0].rgbtBlue+image[height-1][1].rgbtBlue+image[height-2][1].rgbtBlue)/4);
    hold[height-1][width-1].rgbtBlue=round((float)(image[height-1][width-1].rgbtBlue+image[height-1][width-2].rgbtBlue+image[height-2][width-2].rgbtBlue+image[height-2][width-1].rgbtBlue)/4);

     for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            image[i][j]= hold[i][j];
        }
     }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE hold[height][width];
    int gxr, gxg, gxb, gyr, gyg, gyb, holdrgb;
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            if(i==0 && j==0){
                gxr=image[i][j+1].rgbtRed*2+image[i+1][j+1].rgbtRed*1;
                gyr=image[i+1][j].rgbtRed*2+image[i+1][j+1].rgbtRed*1;
                gxg=image[i][j+2].rgbtGreen*2+image[i+1][j+1].rgbtGreen*1;
                gyg=image[i+1][j].rgbtGreen*2+image[i+1][j+1].rgbtGreen*1;
                gxb=image[i][j+2].rgbtBlue*2+image[i+1][j+1].rgbtBlue*1;
                gyb=image[i+1][j].rgbtBlue*2+image[i+1][j+1].rgbtBlue*1;
            }
            else if(i==0 && j==width-1){
                gxr=image[i][j-1].rgbtRed*(-2)+image[i+1][j-1].rgbtRed*(-1);
                gyr=image[i+1][j-1].rgbtRed+image[i+1][j].rgbtRed*(2);
                gxg=image[i][j-1].rgbtGreen*(-2)+image[i+1][j-1].rgbtGreen*(-1);
                gyg=image[i+1][j-1].rgbtGreen+image[i+1][j].rgbtGreen*(2);
                gxb=image[i][j-1].rgbtBlue*(-2)+image[i+1][j-1].rgbtBlue*(-1);
                gyb=image[i+1][j-1].rgbtBlue+image[i+1][j].rgbtBlue*(2);
            }
            else if(i==height-1 && j==0){
                gxr=image[i][j+1].rgbtRed*2+image[i-1][j+1].rgbtRed;
                gyr=image[i-1][j].rgbtRed*(-2)+image[i-1][j+1].rgbtRed*(-1);
                gxg=image[i][j+1].rgbtGreen*2+image[i-1][j+1].rgbtGreen;
                gyg=image[i-1][j].rgbtGreen*(-2)+image[i-1][j+1].rgbtGreen*(-1);
                gxb=image[i][j+1].rgbtBlue*2+image[i-1][j+1].rgbtBlue;
                gyb=image[i-1][j].rgbtBlue*(-2)+image[i-1][j+1].rgbtBlue*(-1);
            }
            else if(i==height-1 && j==width-1){
                gxr=image[i][j-1].rgbtRed*(-2)+image[i-1][j-1].rgbtRed*(-1);
                gyr=image[i-1][j].rgbtRed*(-2)+image[i-1][j-1].rgbtRed*(-1);
                gxg=image[i][j-1].rgbtGreen*(-2)+image[i-1][j-1].rgbtGreen*(-1);
                gyg=image[i-1][j].rgbtGreen*(-2)+image[i-1][j-1].rgbtGreen*(-1);
                gxb=image[i][j-1].rgbtBlue*(-2)+image[i-1][j-1].rgbtBlue*(-1);
                gyb=image[i-1][j].rgbtBlue*(-2)+image[i-1][j-1].rgbtBlue*(-1);
            }
            else if (i==0 && j>0 && j<width-1){
                gxr=(image[i][j-1].rgbtRed*(-2))+image[i][j].rgbtRed*(0)+(image[i][j+1].rgbtRed*(2))+
                (image[i+1][j-1].rgbtRed*(-1))+image[i+1][j].rgbtRed*(0)+image[i+1][j+1].rgbtRed*(1);
                
                gyr=image[i+1][j-1].rgbtRed*(1)+(image[i+1][j].rgbtRed*(2))+image[i+1][j+1].rgbtRed*(1);
                
                gxg=(image[i][j-1].rgbtGreen*(-2))+image[i][j].rgbtGreen*(0)+(image[i][j+1].rgbtGreen*(2))+
                (image[i+1][j-1].rgbtGreen*(-1))+image[i+1][j].rgbtGreen*(0)+image[i+1][j+1].rgbtGreen*(1);
                
                gyg=image[i+1][j-1].rgbtGreen*(1)+(image[i+1][j].rgbtGreen*(2))+image[i+1][j+1].rgbtGreen*(1);
                
                gxb=(image[i][j-1].rgbtBlue*(-2))+image[i][j].rgbtBlue*(0)+(image[i][j+1].rgbtBlue*(2))+
                (image[i+1][j-1].rgbtBlue*(-1))+image[i+1][j].rgbtBlue*(0)+image[i+1][j+1].rgbtBlue*(1);
                
                gyb=image[i+1][j-1].rgbtBlue*(1)+(image[i+1][j].rgbtBlue*(2))+image[i+1][j+1].rgbtBlue*(1);
            }
            else if(i==height-1 && j>0 && j<width-1){
                gxr=image[i-1][j-1].rgbtRed*(-1)+image[i-1][j].rgbtRed*(0)+image[i-1][j+1].rgbtRed*(1)+
                image[i][j-1].rgbtRed*(-2)+image[i][j].rgbtRed*(0)+image[i][j+1].rgbtRed*(2);
                gyr=image[i-1][j-1].rgbtRed*(-1)+image[i-1][j].rgbtRed*(-2)+image[i-1][j+1].rgbtRed*(-1)+
                image[i][j-1].rgbtRed*(0)+image[i][j].rgbtRed*(0)+image[i][j+1].rgbtRed*(0);
                gxg=image[i-1][j-1].rgbtGreen*(-1)+image[i-1][j].rgbtGreen*(0)+image[i-1][j+1].rgbtGreen*(1)+
                image[i][j-1].rgbtGreen*(-2)+image[i][j].rgbtGreen*(0)+image[i][j+1].rgbtGreen*(2);
                gyg=image[i-1][j-1].rgbtGreen*(-1)+image[i-1][j].rgbtGreen*(-2)+image[i-1][j+1].rgbtGreen*(-1)+
                image[i][j-1].rgbtGreen*(0)+image[i][j].rgbtGreen*(0)+image[i][j+1].rgbtGreen*(0);
                gxb=image[i-1][j-1].rgbtBlue*(-1)+image[i-1][j].rgbtBlue*(0)+image[i-1][j+1].rgbtBlue*(1)+
                image[i][j-1].rgbtBlue*(-2)+image[i][j].rgbtBlue*(0)+image[i][j+1].rgbtBlue*(2);
                gyb=image[i-1][j-1].rgbtBlue*(-1)+image[i-1][j].rgbtBlue*(-2)+image[i-1][j+1].rgbtBlue*(-1)+
                image[i][j-1].rgbtBlue*(0)+image[i][j].rgbtBlue*(0)+image[i][j+1].rgbtBlue*(0);
            }
            else if(j==0 && i>0 && i<height-1){
                gxr=image[i-1][j].rgbtRed*(0)+image[i-1][j+1].rgbtRed*(1)+image[i][j].rgbtRed*(0)+image[i][j+1].rgbtRed*(2)+image[i+1][j].rgbtRed*(0)+image[i+1][j+1].rgbtRed*(1);
                gyr=image[i-1][j].rgbtRed*(-2)+image[i-1][j+1].rgbtRed*(-1)+image[i][j].rgbtRed*(0)+image[i][j+1].rgbtRed*(0)+image[i+1][j].rgbtRed*(2)+image[i+1][j+1].rgbtRed*(1);
                gxg=image[i-1][j].rgbtGreen*(0)+image[i-1][j+1].rgbtGreen*(1)+image[i][j].rgbtGreen*(0)+image[i][j+1].rgbtGreen*(2)+image[i+1][j].rgbtGreen*(0)+image[i+1][j+1].rgbtGreen*(1);
                gyg=image[i-1][j].rgbtGreen*(-2)+image[i-1][j+1].rgbtGreen*(-1)+image[i][j].rgbtGreen*(0)+image[i][j+1].rgbtGreen*(0)+image[i+1][j].rgbtGreen*(2)+image[i+1][j+1].rgbtGreen*(1);
                gxb=image[i-1][j].rgbtBlue*(0)+image[i-1][j+1].rgbtBlue*(1)+image[i][j].rgbtBlue*(0)+image[i][j+1].rgbtBlue*(2)+image[i+1][j].rgbtBlue*(0)+image[i+1][j+1].rgbtBlue*(1);
                gyb=image[i-1][j].rgbtBlue*(-2)+image[i-1][j+1].rgbtBlue*(-1)+image[i][j].rgbtBlue*(0)+image[i][j+1].rgbtBlue*(0)+image[i+1][j].rgbtBlue*(2)+image[i+1][j+1].rgbtBlue*(1);
            }
            else if(j==width-1 && i>0 && i<height-1){
                gxr=image[i-1][j-1].rgbtRed*(-1)+image[i-1][j].rgbtRed*(0)+
                image[i][j-1].rgbtRed*(-2)+image[i][j].rgbtRed*(0)+
                image[i+1][j-1].rgbtRed*(-1)+image[i+1][j].rgbtRed*(0);
                gyr=image[i-1][j-1].rgbtRed*(-1)+image[i-1][j].rgbtRed*(-2)+
                image[i][j-1].rgbtRed*(0)+image[i][j].rgbtRed*(0)+
                image[i+1][j-1].rgbtRed*(1)+image[i+1][j].rgbtRed*(2);
                gxg=image[i-1][j-1].rgbtGreen*(-1)+image[i-1][j].rgbtGreen*(0)+
                image[i][j-1].rgbtGreen*(-2)+image[i][j].rgbtGreen*(0)+
                image[i+1][j-1].rgbtGreen*(-1)+image[i+1][j].rgbtGreen*(0);
                gyg=image[i-1][j-1].rgbtGreen*(-1)+image[i-1][j].rgbtGreen*(-2)+
                image[i][j-1].rgbtGreen*(0)+image[i][j].rgbtGreen*(0)+
                image[i+1][j-1].rgbtGreen*(1)+image[i+1][j].rgbtGreen*(2);
                gxb=image[i-1][j-1].rgbtBlue*(-1)+image[i-1][j].rgbtBlue*(0)+
                image[i][j-1].rgbtBlue*(-2)+image[i][j].rgbtBlue*(0)+
                image[i+1][j-1].rgbtBlue*(-1)+image[i+1][j].rgbtBlue*(0);
                gyb=image[i-1][j-1].rgbtBlue*(-1)+image[i-1][j].rgbtBlue*(-2)+
                image[i][j-1].rgbtBlue*(0)+image[i][j].rgbtBlue*(0)+
                image[i+1][j-1].rgbtBlue*(1)+image[i+1][j].rgbtBlue*(2);
            }
            
            else{
            gxr=
            image[i-1][j-1].rgbtRed*(-1)+image[i-1][j].rgbtRed*(0)+image[i-1][j+1].rgbtRed*(1)+
            image[i][j-1].rgbtRed*(-2)+image[i][j].rgbtRed*(0)+image[i][j+1].rgbtRed*(2)+
            image[i+1][j-1].rgbtRed*(-1)+image[i+1][j].rgbtRed*(0)+image[i+1][j+1].rgbtRed*(1);
            gyr=
            image[i-1][j-1].rgbtRed*(-1)+image[i-1][j].rgbtRed*(-2)+image[i-1][j+1].rgbtRed*(-1)+
            image[i][j-1].rgbtRed*(0)+image[i][j].rgbtRed*(0)+image[i][j+1].rgbtRed*(0)+
            image[i+1][j-1].rgbtRed*(1)+image[i+1][j].rgbtRed*(2)+image[i+1][j+1].rgbtRed*(1);

            gxg=
            image[i-1][j-1].rgbtGreen*(-1)+image[i-1][j].rgbtGreen*(0)+image[i-1][j+1].rgbtGreen*(1)+
            image[i][j-1].rgbtGreen*(-2)+image[i][j].rgbtGreen*(0)+image[i][j+1].rgbtGreen*(2)+
            image[i+1][j-1].rgbtGreen*(-1)+image[i+1][j].rgbtGreen*(0)+image[i+1][j+1].rgbtGreen*(1);
            gyg=
            image[i-1][j-1].rgbtGreen*(-1)+image[i-1][j].rgbtGreen*(-2)+image[i-1][j+1].rgbtGreen*(-1)+
            image[i][j-1].rgbtGreen*(0)+image[i][j].rgbtGreen*(0)+image[i][j+1].rgbtGreen*(0)+
            image[i+1][j-1].rgbtGreen*(1)+image[i+1][j].rgbtGreen*(2)+image[i+1][j+1].rgbtGreen*(1);

            gxb=
            image[i-1][j-1].rgbtBlue*(-1)+image[i-1][j].rgbtBlue*(0)+image[i-1][j+1].rgbtBlue*(1)+
            image[i][j-1].rgbtBlue*(-2)+image[i][j].rgbtBlue*(0)+image[i][j+1].rgbtBlue*(2)+
            image[i+1][j-1].rgbtBlue*(-1)+image[i+1][j].rgbtBlue*(0)+image[i+1][j+1].rgbtBlue*(1);
            gyb=
            image[i-1][j-1].rgbtBlue*(-1)+image[i-1][j].rgbtBlue*(-2)+image[i-1][j+1].rgbtBlue*(-1)+
            image[i][j-1].rgbtBlue*(0)+image[i][j].rgbtBlue*(0)+image[i][j+1].rgbtBlue*(0)+
            image[i+1][j-1].rgbtBlue*(1)+image[i+1][j].rgbtBlue*(2)+image[i+1][j+1].rgbtBlue*(1);
            }
            if (gxr!=0 || gyr!=0){
                holdrgb=round(sqrt(pow((float) gxr,2)+pow((float) gyr,2)));
                if (holdrgb > 255) hold[i][j].rgbtRed=255;
                else  hold[i][j].rgbtRed=holdrgb;
            }
            if (gxg!=0 || gyg!=0){
                holdrgb=round(sqrt(pow((float) gxg,2)+pow((float) gyg,2)));
                if (holdrgb > 255) hold[i][j].rgbtGreen=255;
                else hold[i][j].rgbtGreen=holdrgb;
            }
            if (gxb!=0 || gyb!=0){
                holdrgb=round(sqrt(pow( (float) gxb,2)+pow((float) gyb,2)));
                if (holdrgb > 255) hold[i][j].rgbtBlue=255;
                else hold[i][j].rgbtBlue=holdrgb;
            }

        }
    }

    //boundary
    /*
    for (int k=-1; k<=width; k++){
        image[-1][k].rgbtRed=0;
        image[-1][k].rgbtGreen=0;
        image[-1][k].rgbtBlue=0;
        image[height][k].rgbtRed=0;
        image[height][k].rgbtGreen=0;
        image[height][k].rgbtBlue=0;
    }
    for (int k=-1; k<=width; k++){
        image[k][-1].rgbtRed=0;
        image[k][-1].rgbtGreen=0;
        image[k][-1].rgbtBlue=0;
        image[k][width].rgbtRed=0;
        image[k][width].rgbtGreen=0;
        image[k][width].rgbtBlue=0;
    }
    */

    for (int z=0; z<height; z++){
        for (int x=0; x<width; x++){
            image[z][x]= hold[z][x];
        }
     }
    return;
}
