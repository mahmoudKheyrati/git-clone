#pragma once

typedef char* String;
#define loop(i,n) for (int i = 0 ; i<n;i++)
#define print printf
#define foreach(item, array) \
    for(int keep=1, \
            count=0,\
            size=sizeof (array)/sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array)+count; keep; keep = !keep)
#define swap(x, y, T) do { T tmp = (x); (x) = (y); (y) = tmp; } while(0)
enum Boolean {False,True};