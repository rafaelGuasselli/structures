#include "../presets/base.cpp"
#define md 1000000007
int fast_pow(int a, int b){ 
   int res = 1;
   while(b){
     if(b & 1){
       res = (res*a)%md;
     }
     a = (a*a)%md;
     b >>=1;
   }
   return res;
 }
