#ifndef FIX_POINT_COMPLEX_H
#define FIX_POINT_COMPLEX_H //TODO: move this inside the header file

#ifndef Q_FORMAT_CUSTOM
#define Q_FORMAT_CUSTOM 16
#endif

#include "fix_point.h"
#include "fix_point_math.h"

struct q_complex {
    q_t real;
    q_t imag;
};
typedef struct q_complex q_complex_t;

q_complex_t q_complex_alloc(q_t real, q_t imag);

//TODO: Add complex number operations

void q_complex_free(q_complex_t* c);

#endif // FIX_POINT_COMPLEX_H
