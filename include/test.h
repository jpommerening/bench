/* -*- Mode: C; tab-width: 2; c-basic-offset: 2 -*- */
/* vim:set softtabstop=2 shiftwidth=2: */
/* 
 * Copyright (c) 2013, Jonas Pommerening <jonas.pommerening@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _TEST_H_
#define _TEST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <stddef.h>

#define TEST_EXTERN extern

typedef enum {
  TEST_UNKNOWN,
  TEST_PASS,
  TEST_WARN,
  TEST_SKIP,
  TEST_FAIL,
  TEST_ERROR,
  TEST_RESULT_MAX
} test_result_t;

typedef struct test_s test_t;
typedef struct suite_s suite_t;
typedef struct test_api_s test_api_t;

typedef void (*test_any_cb)();
typedef void (*test_void_cb)( const test_api_t* __api );
typedef void (*test_data_cb)( const test_api_t* __api, const void* );

/* from gen-tests.sh -> gen-tests.c */
TEST_EXTERN const test_t* tests[];

typedef union {
  test_any_cb  any_cb;
  test_void_cb void_cb;
  test_data_cb data_cb;
} test_cb;

struct test_s {
  const char* name;
  const char* description;
  const char* date;
  const char* time;
  test_cb callback;
  ptrdiff_t datastep;
  size_t    datalength;
  const void* data;
};

struct suite_s {
  const char* name;
  const char* description;
  const char* date;
  const char* time;
  const test_t** tests;
};

struct test_api_s {
  void* data;
  void (*log)( void* data, const char* file, int line, const char* fmt, ... );
  void (*result)( void* data, test_result_t result );
  void (*exit)( void* data );
};

#define TEST_UID(name) test__ ## name
#define TEST_STRUCT(name) \
  const test_t TEST_UID(name)

/* Crazy preprocessor macros ahead:
 *   We trick the preprocessor into telling us if TEST() was supplied
 *   with additional parameters.
 *   Depending on that, we place different stuff into the struct.
 */

/* If additional parameters are given in `...' expand them
 * using the function-like macro `a', otherwise insert `b'. */
#define IF_ARGS(a,b,...) _IF_ARGS(__VA_ARGS__) ? b : a(__VA_ARGS__ ((void*)0)) /* dummy arg*/
#define _IF_ARGS(...)    (sizeof(#__VA_ARGS__) == 1)

/* Initializers for test structs with test data. */
#define _TEST_DATASTEP(data, ...) \
  sizeof(data[0])
#define _TEST_DATALENGTH(data, ...) \
  sizeof(data)/sizeof(data[0])
#define _TEST_DATAPTR(data, ...) \
  &(data[0])

/* Generate the signature of a test function.
 * Skip the first variadic parameter and use the rest inside the declaration. */
#define TEST_SIGN(name,...) \
  _TEST_SIGN(name,__VA_ARGS__)
#define _TEST_SIGN(name,d,...) \
  static void name( test_api_t* __api, ## __VA_ARGS__ )

/**
 * Declare test functions with this macro.
 * @param name the name of the function to declare.
 * @param [data] an array containing test data to drive the test.
 * @param [arg] the parameter that is used by the function to accept data.
 */
#define TEST(name,...) \
  TEST_SIGN(name,## __VA_ARGS__); \
  TEST_STRUCT(name) = { \
    #name, "", __DATE__, __TIME__, \
    &name, \
    IF_ARGS(_TEST_DATASTEP,0,## __VA_ARGS__), \
    IF_ARGS(_TEST_DATALENGTH,1,## __VA_ARGS__), \
    IF_ARGS(_TEST_DATAPTR,NULL,## __VA_ARGS__), \
  }; \
  TEST_SIGN(name,## __VA_ARGS__)

#define MSG(...) (__api->log)(__api->data, __FILE__, __LINE__, "" __VA_ARGS__)
#define RESULT(x) (__api->result)(__api->data, x)
#define EXIT (__api->exit)(__api->data)

#define WARN(...) do { MSG(__VA_ARGS__); RESULT(TEST_WARN); } while( 0 )
#define SKIP(...) do { MSG(__VA_ARGS__); RESULT(TEST_SKIP); EXIT; } while( 0 )
#define FAIL(...) do { MSG(__VA_ARGS__); RESULT(TEST_FAIL); EXIT; } while( 0 )
#define ERROR(...) do { MSG(__VA_ARGS__); RESULT(TEST_ERROR); abort(); } while( 0 )

#define ASSERTBASE(x,...) do if( !(x) ) { FAIL(__VA_ARGS__); } while( 0 )
#define ASSERT(x,...) ASSERTBASE(x,"`" #x "' is not true!\n" __VA_ARGS__)
#define ASSERTEQ(a,b,...) ASSERTBASE((a) == (b),"`" #a "' does not equal `" #b "'!\n" __VA_ARGS__)
#define ASSERTLT(a,b,...) ASSERTBASE((a) < (b),"`" #a "' is not less than `" #b "'!\n" __VA_ARGS__)
#define ASSERTGT(a,b,...) ASSERTBASE((a) > (b),"`" #a "' is not greater than`" #b "'!\n" __VA_ARGS__)
#define ASSERTSTRCMP(a,op,b) ((a==b) || (a!=NULL) && (b!=NULL) && strcmp(a,b) op 0)
#define ASSERTSTREQ(a,b,...) ASSERTBASE(ASSERTSTRCMP(a,==,b),"Strings `" #a "' and `" #b "' are not equal!\n" __VA_ARGS__)
#define ASSERTSTRLT(a,b,...) ASSERTBASE(ASSERTSTRCMP(a,<,b),"String `" #a "' is not `less than' string `" #b "'!\n" __VA_ARGS__)
#define ASSERTSTRGT(a,b,...) ASSERTBASE(ASSERTSTRCMP(a,>,b),"String `" #a "' is not `greater than' string `" #b "'!\n" __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif
