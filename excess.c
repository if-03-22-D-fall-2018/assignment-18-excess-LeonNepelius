//
// Created by Leon on 28.04.2019.
//

#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

void read_textfile(char* textfile);

int
main(int argc,char *argv[])
{
    char filename[256];
    printf("Please enter your filename: ");
    scanf("%s",filename);
    system("clear");
    read_textfile(filename);
    return 0;
}


void read_textfile(char* textfile)
{
    struct winsize ws;
    if (ioctl(0,TIOCGWINSZ,&ws)!=0) {
        fprintf(stderr,"TIOCGWINSZ:%s\n",strerror(errno));
        exit(-1);
    }
    //printf("row=%d, col=%d, xpixel=%d, ypixel=%d\n",
    //      ws.ws_row,ws.ws_col,ws.ws_xpixel,ws.ws_ypixel);
    char line[100000];
    char c;
    int row = 0;
    int col = 0;
    FILE* stream = fopen(textfile,"r");
    if (stream == 0)
    {
        printf("Filename doesn't exist!\n");
        return;
    }
    do {
        c = fgetc(stream);
        if (feof(stream)) {
            break;
        }
        line[col] = c;
        printf("%c",line[col]);
        col++;
        if (col == ws.ws_col)
        {
            row++;
            col = 0;
        }
        if (row == ws.ws_row-5)
        {
            char input[256];
            printf("\nEnter RETURN to go to the next page: ");
            scanf("%s",input);
            if (input[0] == '\n')
            {
                printf("Return entered!");
            }
            row = 0;
        }
    }while ( 1 );
    fclose(stream);
}