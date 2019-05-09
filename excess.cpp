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
        if (col == ((ws.ws_row-3)*(ws.ws_col))-1)
        {
            memcpy(pages[page], line, sizeof(line));
            page++;
            col = 0;
        }
    }while ( 1 );
    int sum_pages = page;
    page = 0;
    printf("%s",pages[page]);
    char input[256];
    printf("\nEnter n to go to the next page or b for the previous page: ");
    scanf("%s",input);
    while (page < sum_pages) {
        system("clear");
        if (strcmp(input,"n")==0)
        {
            page++;
            printf("%s",pages[page]);
            printf("\nEnter n to go to the next page or b for the previous page: ");
            scanf("%s",input);
        }
        else if (strcmp(input,"b")==0)
        {
            page--;
            printf("%s",pages[page]);
            printf("\nEnter n to go to the next page or b for the previous page: ");
            scanf("%s",input);
        }
    }
    fclose(stream);
}
