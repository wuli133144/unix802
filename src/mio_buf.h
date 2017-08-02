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


#ifndef  MIO_BUFFER__H
#define  MIO_BUFFER__H




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdarg.h>
#include <fcntl.h>
#include <string.h>






#define BUFSIZE 1024


#undef  malloc 
#undef  free



#define TEST(A)                                                                \
  do {                                                                         \
    fprintf(stdout, "%d %-60s======", __LINE__, #A);                                \
    if (A) {                                                                   \
      puts("OK");                                                              \
    } else {                                                                   \
      puts("FAILED");                                                          \
    }                                                                          \
}while (0);


#ifdef __cplusplus
extern "C"
{
#endif

typedef struct __buf__io {

  size_t capacity; /*this buf real size*/
  size_t size;     /*num*/
  char buf[BUFSIZE];
  char *send_ptr; /*send data position*/
  char *recv_ptr;
} mio_t;

typedef mio_t     bufferobject;

static mio_t *mio_object=NULL;

void init_mio();
ssize_t mio_read(int fd,mio_t *io,size_t len);
ssize_t  mio_write(int fd,mio_t *io,size_t len);

void destroy();
#ifdef __cplusplus
}
#endif


#endif