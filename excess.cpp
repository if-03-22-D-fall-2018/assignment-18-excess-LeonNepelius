//
// Created by Leon on 29.04.2019.
//

#include "excess.h"
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

static char filename[256];

int
main(int argc,char *argv[])
{
    printf("Please enter your filename: ");
    scanf("%s",filename);
    system("clear");
    read_textfile();
    return 0;
}


void read_textfile()
{
    struct winsize ws;
    if (ioctl(0,TIOCGWINSZ,&ws)!=0) {
        fprintf(stderr,"TIOCGWINSZ:%s\n",strerror(errno));
        exit(-1);
    }
    //printf("row=%d, col=%d, xpixel=%d, ypixel=%d\n",
    //      ws.ws_row,ws.ws_col,ws.ws_xpixel,ws.ws_ypixel);
    char line[ws.ws_row*ws.ws_col];
    char pages[100][ws.ws_row*ws.ws_col];
    char c;
    int row = 0;
    int col = 0;
    int page = 0;
    FILE* stream = fopen(filename,"r");
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
        col++;
        if ((col % ws.ws_col) == 0)
        {
            row++;
        }
        if (row == ws.ws_row-5)
        {
            memcpy(pages[page], line, sizeof(line));
            printf("%s",pages[page]);
            page++;
            char input[256];
            printf("\nEnter n to go to the next page or b for the previous page: ");
            scanf("%s",input);
            while (strcmp(input,"b") == 0)
            {
                system("clear");
                page--;
                if (page < 0)
                {
                    page++;
                }
                else
                {
                    printf("%s",pages[page]);
                    printf("\nEnter n to go to the next page or b for the previous page: ");
                    scanf("%s",input);
                }
            }
            system("clear");
            row = 0;
            col = 0;
        }
    }while ( 1 );
    fclose(stream);
}