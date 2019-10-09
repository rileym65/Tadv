#include <stdio.h>
#include <string.h>
#include "header.h"

RC4_DATA rc4_init(byte* key,int keylen) {
  int      i;
  int      j;
  byte     t;
  RC4_DATA ret;
  j = 0;
  for (i=0; i<256; i++) {
    ret.s[i] = i;
    ret.k[i] = key[j++];
    if (j >= keylen) j = 0;
    }
  j = 0;
  for (i=0; i<256; i++) {
    j = (j + ret.s[i] + ret.k[i]) & 0xff;
    t = ret.s[i]; ret.s[i] = ret.s[j]; ret.s[j] = t;
    }
  ret.i = 0;
  ret.j = 0;
  return ret;
  }

void     rc4(byte* buffer,int len,RC4_DATA* key) {
  int  i;
  int  t;
  byte k;
  for (i=0; i<len; i++) {
    key->i = (key->i + 1) & 0xff;
    key->j = (key->j + key->s[key->i]) & 0xff;
    k = key->s[key->i]; key->s[key->i] = key->s[key->j]; key->s[key->j] = k;
    t = (key->s[key->i] + key->s[key->j]) & 0xff;
    buffer[i] ^= key->s[t];
    }
  }

unsigned char shift(unsigned char in) {
  return (in<26) ? in + 'A' :
         (in<52) ? (in-26) + 'a' :
         (in<62) ? (in-52) + '0' :
         (in==62) ? '_' : '-';
  }

unsigned char unshift(unsigned char in) {
  return (in >= 'A' && in <= 'Z') ? in - 'A' :
         (in >= 'a' && in <= 'z') ? in - 'a' + 26 :
         (in >= '0' && in <= '9') ? in - '0' + 52 :
         (in == '_') ? 62 : 63;
  }

void encode(byte* inBuffer,byte* outBuffer,int len) {
  int     i,oi;
  byte    b1,b2,b3;
  i=0;
  oi = 0;
  while (i<len) {
    b1 = inBuffer[i] & 0x3f;
    b2 = ((inBuffer[i] >> 6) & 0x3) | ((inBuffer[i+1] & 0xf) << 2);
    b3 = (inBuffer[i+1] >> 4);
    outBuffer[oi++] = shift(b1);
    outBuffer[oi++] = shift(b2);
    outBuffer[oi++] = shift(b3);
    i+=2;
    }
  outBuffer[oi]=0;
  }

void decode(byte* inBuffer,byte* outBuffer,int len) {
  int     i,j;
  byte b1,b2,b3;
  j = 0;
  i = 0;
  while (i < len) {
    b1 = unshift(inBuffer[j++]);
    b2 = unshift(inBuffer[j++]);
    b3 = unshift(inBuffer[j++]);
    outBuffer[i++] = b1 | ((b2 & 0x3) << 6);
    outBuffer[i++] = (b2 >> 2) | (b3 << 4);
    }
  outBuffer[i]=0;
  }

void encrypt(byte* inBuffer,byte* outBuffer,RC4_DATA* key) {
  int len;
  byte temp[1024];
  len = strlen(inBuffer);
  rc4(inBuffer,len,key);
  encode(inBuffer,temp,len);
  sprintf(outBuffer,"%d:",len);
  strcat(outBuffer,temp);
  }

void decrypt(byte* inBuffer,byte* outBuffer,RC4_DATA* key) {
  int len;
  len = atoi(inBuffer);
  if (len == 0) {
    *outBuffer = 0;
    return;
    }
  while (*inBuffer != ':') inBuffer++;
  inBuffer++;
  decode(inBuffer,outBuffer,len);
  rc4(outBuffer,len,key);
  }

