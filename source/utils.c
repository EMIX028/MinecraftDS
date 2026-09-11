#include "utils.h"

inline fixed_t inttofixed(int32_t x){
    return x << FIXED_SHIFT;
}

inline int32_t fixedtoint(fixed_t x){
    return x >> FIXED_SHIFT;
}

fixed_t fixed_mul(fixed_t a, fixed_t b){
    return (fixed_t)(((int64_t)a * b) >> FIXED_SHIFT);
}

fixed_t fixed_div(fixed_t a, fixed_t b){
    return (fixed_t)(((int64_t)a << FIXED_SHIFT) / b);
}