//
// Created by eb on 04/04/25.
//

//#include "wasm_app.h"

#include <iostream>
#include <cstdint>

// External function declarations
extern "C" {
    int intToStr(int x, char *str, int str_len, int digit);
    int32_t get_pow(int x, int y);
    int32_t calculate_native(int32_t n, int32_t func1, int32_t func2);
}

// wasm doesn't support cout? 
extern "C" int32_t mul7(int32_t n) {
    printf("calling into WASM function: %s,", __FUNCTION__);
    n = n * 7;
    printf("    %s return %d \n", __FUNCTION__, n);
    return n;
}

extern "C" int32_t mul5(int32_t n) {
    printf("calling into WASM function: %s,", __FUNCTION__);
    n = n * 5;
    printf("    %s return %d \n", __FUNCTION__, n);
    return n;
}

extern "C" int32_t mul(int32_t n, int32_t m) {
    printf("calling into WASM function: %s,", __FUNCTION__);
    n = n * m;
    printf("    %s return %d \n", __FUNCTION__, n);
    return n;
}

extern "C" int32_t power(int32_t n, int32_t m) {
    printf("calling into WASM function: %s,", __FUNCTION__);
    n = get_pow(n, m);
    printf("    %s return %d \n", __FUNCTION__, n);
    return n;
}

 extern "C" int32_t calculate(int32_t n) {
     printf("calling into WASM function: %s\n", __FUNCTION__);
     // Using function pointers
     int32_t (*f1)(int32_t) = &mul5;
     int32_t (*f2)(int32_t) = &mul7;
     return calculate_native(n, (uintptr_t)f1, (uintptr_t)f2);
 }

extern "C" float generate_float(int iteration, double seed1, float seed2)
{
    float ret;

    printf("calling into WASM function: %s\n", __FUNCTION__);

    for (int i = 0; i < iteration; i++) {
        ret += 1.0f / seed1 + seed2;
    }

    return ret;
}

// Converts a floating-point/double number to a string.
// intToStr() is implemented outside wasm app
extern "C" void float_to_string(float n, char *res, int res_size, int afterpoint)
{

    printf("calling into WASM function: %s\n", __FUNCTION__);

    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, res_size, 0);

    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot

        // Get the value of fraction part upto given no.
        // of points after dot.
        fpart = fpart * get_pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, res_size - i - 1, afterpoint);
    }
}

