/**
Copyright notice:

 (C) 2014 Arnau Prat-Perez

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
**/

#include "../../Include/MPPriorityQueue.h"
#include <stdlib.h>
#include <CUnit/Basic.h>


static mpPriorityQueue* pq;

static int mpCompareInt( void* a, void* b) {
  return *(int*)a - *(int*)b <= 0;
}

static int values[10] = {1,2,3,4,5,6,7,8,9,10};
static int size = 4;

void mpAllocatePQTest() {
  pq = mpAllocatePQ( size, mpCompareInt ); 
  CU_ASSERT( pq != NULL );
}



void mpPushPQTest() {
  int i = 0;
  for( i = 0; i < size; ++i ) {
    mpPushPQ( pq, &values[i] ); 
    CU_ASSERT( pq->m_Size == i+1 );
  }
}

void mpPeekPQTest() {
  int value = *(int*)mpPeekPQ( pq ); 
  CU_ASSERT( pq->m_Size == 10 );
  CU_ASSERT( value == 1 );
}

void mpPopPQTest() {
  int i = 0;
  for( i = 0; i < size; ++i ) {
    int value = *(int*)mpPopPQ( pq ); 
    CU_ASSERT(pq->m_Size == (size - (i+1)));
    CU_ASSERT(value == values[i]);
  }
}

void mpFreePQTest() {
  mpFreePQ( pq ); 
  CU_ASSERT( 1 );
}


int main( int argc, char** argv ) {
      CU_pSuite pSuite = NULL;
      pq = NULL;
 
        /* initialize the CUnit test registry */ 
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();
 
   /* add a suite to the registry */ 
   pSuite = CU_add_suite("PQTest", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
 
   /* add the tests to the suite */ 
   if (NULL == CU_add_test(pSuite, "MPPriorityQueue.h: mpAllocatePQ()", mpAllocatePQTest )) {
      CU_cleanup_registry();
      return CU_get_error();
   }


   if (NULL == CU_add_test(pSuite, "MPPriorityQueue.h: mpPushPQ()", mpPushPQTest )) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if (NULL == CU_add_test(pSuite, "MPPriorityQueue.h: mpPopPQ()", mpPopPQTest )) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if (NULL == CU_add_test(pSuite, "MPPriorityQueue.h: mpFreePQ()", mpFreePQTest )) {
      CU_cleanup_registry();
      return CU_get_error();
   }
 
   /* Run all tests using the CUnit Basic interface */ 
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
  return 0;
}


