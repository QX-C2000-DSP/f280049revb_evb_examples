#ifndef DEBUG_H
#define DEBUG_H

//*****************************************************************************
//
// Prototype for the function that is called when an invalid argument is passed
// to an API.  This is only used when doing a DEBUG build. It is the
// application's responsibility to define the __error__ function.
//
//*****************************************************************************
extern void __error__(const char *filename, uint32_t line);

//*****************************************************************************
//
// The ASSERT macro, which does the actual assertion checking.  Typically, this
// will be for procedure arguments.
//
//*****************************************************************************
// #define DEBUG
#ifdef DEBUG
//
// When called from C28x application
//
#define ASSERT(expr)                       \
    do                                     \
    {                                      \
        if (!(expr))                       \
        {                                  \
            __error__(__FILE__, __LINE__); \
        }                                  \
    } while ((_Bool)0)
#else
#define ASSERT(expr)
#endif

#endif // DEBUG_H
