#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned char byte;

long read_cmd(byte *buf);
long write_cmd(byte *buf, long len);
long read_exact(byte *buf, long len);
long write_exact(byte *buf, long len);

long read_cmd(byte *buf)
{
  long len;
  if (read_exact(buf, 4) != 4)
    return(-1);
  len = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];
  fprintf(stderr,"buff is %d %d %d %d\n\r",buf[0],buf[1],buf[2], buf[3]); 
  return read_exact(buf, len);
}
long write_cmd(byte *buf, long len)
{
  byte li;
  li = (len >> 24) & 0xff;
  write_exact(&li, 1);
  li = (len >> 16) & 0xff;
  write_exact(&li, 1);
  li = (len >> 8) & 0xff;
  write_exact(&li, 1);
  li = len & 0xff;
  write_exact(&li, 1);
  return write_exact(buf, len);
}
long read_exact(byte *buf, long len)
{
  long i, got=0;
  do {
    if ((i = read(0, buf+got, len-got)) <= 0)
      return(i);
    got += i;
  } while (got<len);
  return(len);
}
long write_exact(byte *buf, long len)
{
  long i, wrote = 0;
  do {
    if ((i = write(1, buf+wrote, len-wrote)) <= 0)
      return (i);
    wrote += i;
  } while (wrote<len);
  return (len);
}
