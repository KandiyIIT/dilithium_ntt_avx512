#ifndef _align64_h
#define _align64_h
#if !defined (ALIGN64)
# if defined (__GNUC__)
# define ALIGN64 __attribute__ ( (aligned (64)))
# else
# define ALIGN64 __declspec (align (64))
# endif
#endif 

#endif