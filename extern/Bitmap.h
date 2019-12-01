#ifndef __BITMAP_H__
#define __BITMAP_H__
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

class Bitmap { 
private:
   char* M; int N; //
protected:
   void init ( int n ) { M = new char[N = ( n + 7 ) / 8]; memset ( M, 0, N ); }
public:
   Bitmap ( int n = 8 ) { init ( n ); } //
   ~Bitmap() { delete [] M; M = NULL; } //

   void set   ( int k ) { expand ( k );        M[k >> 3] |=   ( 0x80 >> ( k & 0x07 ) ); }
   void clear ( int k ) { expand ( k );        M[k >> 3] &= ~ ( 0x80 >> ( k & 0x07 ) ); }
   bool test  ( int k ) { expand ( k ); return M[k >> 3] &    ( 0x80 >> ( k & 0x07 ) ); }

   void expand ( int k ) { //
      if ( k < 8 * N ) return; //
      int oldN = N; char* oldM = M;
      init ( 2 * k ); //
      memcpy_s ( M, N, oldM, oldN ); delete [] oldM; //
   }
};

#endif
