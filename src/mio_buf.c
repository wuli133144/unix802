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

#ifdef _MSC_VER
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif /* _CRT_SECURE_NO_WARNINGS */
#endif /* _MSC_VER */

#include "mio_buf.h"
#include <errno.h>


#define mio_alloc()     (mio_t *)malloc(sizeof(mio_t))
#define mio_free(x)          free(x) 

#define MAX(x,y)         ((x)>(y)?(x):(y))
#define MIN(x,y)         ((x)<(y)?(x):(y))
#define OFFSET1(X)        ((X)->recv_ptr)-((X)->buf)
#define OFFSET2(X)        ((X)->send_ptr)-((X)->buf)


/*@init miobuffer @*/
 void init_mio(){
      mio_object=mio_alloc();
      TEST(mio_object==NULL);
      mio_object->send_ptr=mio_object->buf;
      mio_object->recv_ptr=mio_object->buf;
      TEST(mio_object->recv_ptr==mio_object->buf);
      mio_object->capacity=BUFSIZE;
      mio_object->size=0;
}

void destroy(){
    mio_free(mio_object);
    mio_object=NULL;
}

/*
ssize_t mio_read(int fd,mio_t *io,size_t len);
ssize_t  mio_write(int fd,mio_t *io,size_t len);
*/


ssize_t mio_read(int fd,mio_t *io,size_t len){
       
       char buffer[BUFSIZE];
       size_t nread;
       size_t nleft=len;
       TEST(nleft<0);
       while(nleft>0){
                 if((nread=read(fd,buffer,nleft))<0){
                       if(errno==EINTR){
                           nread=0;
                           continue;
                       }else if(errno==EAGAIN||errno==EWOULDBLOCK){
                            break;
                       }
                       errno=(-1);
                       goto err_seg;
                 }else if(nread==0){
                             break;
                 }

                 nleft-=nread;
                 TEST(nleft<0);
                /* //printf("%s %d\n",buffer,nread);
                 //memcpy(io->buf,buffer,nread);
                 */
                 printf("%x",io->recv_ptr);
                 strcat(io->recv_ptr,buffer);
                 TEST(nleft<0);
                 TEST(nleft>0);
               /*io->recv_ptr=io->buf+(OFFSET1(io)+nread)%(BUFSIZE);*/
       }
       
        io->size=(io->recv_ptr-io->send_ptr+BUFSIZE)%(BUFSIZE);
        if(io->size >BUFSIZE){
            errno=(-2);
            goto err_seg;
        }
       return (len-nleft);
        err_seg:
            
            return errno;

}

ssize_t mio_write(int fd,mio_t *io,size_t len){
       
       size_t nwrite;
       size_t nleft=len;
      
       nleft=MIN(len,io->size);
       while(nleft>0){
                 if((nwrite=write(fd,io->send_ptr,nleft))<0){
                       if(errno==EAGAIN||errno==EWOULDBLOCK){
                           break;
                       }else if(errno==EINTR||errno==EPIPE){
                           break;
                       }
                       goto err;
                 }
                 nleft-=nwrite;
                 
                 io->send_ptr=io->buf+(OFFSET2(io)+nwrite)%(BUFSIZE);
                 io->size-=nwrite;
       }
       return len-nleft;
       err:
          errno=(-1);
          return errno;
       
}




