
/*
 MIO_BUFFER ( https://github.com/wuli133144/unix802)
 Copyright (c)2017-2020

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/



#ifndef     __CIRCLE_QUEUE_____CHAR_____H
#define     __CIRCLE_QUEUE_____CHAR_____H

#ifdef _MSC_VER
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif /* _CRT_SECURE_NO_WARNINGS */
#endif /* _MSC_VER */

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>



#define TEST(A)                                                                \
  do {                                                                         \
    fprintf(stdout, "%d %-60s======", __LINE__, #A);                                \
    if (A) {                                                                   \
      puts("OK");                                                              \
    } else {                                                                   \
      puts("FAILED");                                                          \
    }                                                                          \
}while (0);

#define   BUFSIZE     1024

#define type       char

typedef  enum {false,true} boolean;

typedef struct __queue__circle circle_queue_t;

typedef  boolean (*is_t)(circle_queue_t *);
typedef  int     (*push_t)(circle_queue_t *,char );
typedef  int     (*pull_t)(circle_queue_t *,char *);


typedef   struct __queue__circle{
      type buf[BUFSIZE];
      int tail;
      int head;
      /*operation start*/
      /*operation end*/
}circle_queue_t;




/*@ isempty start@*/
boolean isempty(circle_queue_t *queue){
                return (queue->tail==(queue->head)%BUFSIZE)? true:false;
}
/*@ isempty end@*/

boolean isfull(circle_queue_t *queue){
    return ((queue->tail+1)%BUFSIZE==queue->head)?true:false;
}

int push(circle_queue_t *queue,char c){
                     if(isfull(queue)){
                       // TEST(queue->tail==0);
                        printf("isfull\n");
                        return (-1);
                     }
                     TEST(queue->tail==0);
                     queue->buf[(queue->tail=(queue->tail+1)%BUFSIZE)]=c;
                     TEST(queue->tail==1);
                     return 0;
}

int peek(circle_queue_t *queue,char *c){
     if(isempty(queue)){//note :empty
         return (-1);
     }
     (*c)=queue->buf[(queue->head+1)%BUFSIZE];
     return 0;//success
}

int pull(circle_queue_t *queue,char *c){
     if(isempty(queue)){//note :empty
         return (-1);
     }
     *c=queue->buf[(queue->head=(queue->head+1)%BUFSIZE)];
     return (0);//success
}


ssize_t getsize(circle_queue_t *queue){
    return (queue->tail-queue->head+BUFSIZE+1)%BUFSIZE;
}
void init(circle_queue_t *queue){
    queue->tail=queue->head=0;
  
}

// void show(circle_queue_t *que){
//     printf("%s %d",que->buf[que->head],que->head);
// }
#endif