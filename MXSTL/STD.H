#ifndef _std_h
#define _std_h

// include files that std namespace needs (files STL will suck in)
extern "C"
{
    #include <stddef.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include <stdlib.h>
    #include <limits.h>
    #include <assert.h>
}

#include <new.h> 
#include <iostream.h>

#if defined(min)
#if defined(_WINDEF_) && !defined(NOMINMAX)
#error std.h requires NOMINMAX to be defined before including WINDOWS header files
#endif
#error min already defined
#endif

#if defined(max)
#if defined(_WINDEF_) && !defined(NOMINMAX)
#error std.h requires NOMINMAX to be defined before including WINDOWS header files
#endif
#error max already defined
#endif

// std namespace
namespace std
{
    #include <algo.h>    
    #include <algobase.h>
    #include <bool.h>    
    // #include <bstring.h>     // not really part of STL
    // #include <bvector.h>     // ??? caused link problems
    #include <defalloc.h>
    #include <deque.h>   
    #include <function.h>
    #include <heap.h>    
    #include <iterator.h>
    #include <list.h>    
    #include <map.h>     
    #include <multimap.h>
    #include <multiset.h>
    #include <pair.h>    
    #include <projectn.h>
    #include <set.h>     
    #include <stack.h>   
    #include <tempbuf.h> 
    #include <tree.h>    
    #include <vector.h>  
}

#endif /* _std_h */
