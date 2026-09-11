#include "utils.h"

inline fixed_t inttofixed(int32_t x){
    return x << FIXED_SHIFT;
}

inline int32_t fixedtoint(fixed_t x){
    return x >> FIXED_SHIFT;
}


fixed_t ftofixed(float x){
    return (fixed_t)(x * FIXED_ONE);
}

float fixedtofloat(fixed_t x){
    return (float)x / FIXED_ONE;
}

vec3_t fxvec3tovec3(fxvec3_t d){
    return (vec3_t){
        .x = fixedtofloat(d.x),
        .y = fixedtofloat(d.y),
        .z = fixedtofloat(d.z)
    };
}

fxvec3_t vec3tofxvec3(vec3_t d){
    return (fxvec3_t){
        .x = ftofixed(d.x),
        .y = ftofixed(d.y),
        .z = ftofixed(d.z)
    };
}

fixed_t fixed_mul(fixed_t a, fixed_t b){
    return (fixed_t)(((int64_t)a * b) >> FIXED_SHIFT);
}

fixed_t fixed_div(fixed_t a, fixed_t b){
    return (fixed_t)(((int64_t)a << FIXED_SHIFT) / b);
}