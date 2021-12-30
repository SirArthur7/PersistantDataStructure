#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include "src/lib/headers_preprocessors.h"
#include "src/lib/PPDS_LinkedList.h"
#include "src/lib/test_with_Vector_and_PDSLL.h"

using namespace std;

const int max_mod = 3;
const int max_size = 3000;

TEST(VECT_AND_PDSLL_VALIDATION_TEST, COMPARE_VECTOR_VS_PDSLL) {
  
    vector<int>vect(max_size,SENTINEL);
    PPDS_LINKED_LIST<int>list(max_mod);
    VECT_AND_PDSLL vp_test(max_mod,max_size);
    vector<int>actualResult,expectedResult;

    
    vp_test.randomized_Insert(list,vect);
    expectedResult = vp_test.trimVect(vect);
    actualResult = list.iterate_and_print_F1_at_ver_Vect(list.getCurTime());
    
    EXPECT_EQ(expectedResult, actualResult);  // random insert
    expectedResult.clear(); actualResult.clear();

    
    vp_test.randomized_Update(list,vect);
    expectedResult = vp_test.trimVect(vect);
    actualResult = list.iterate_and_print_F1_at_ver_Vect(list.getCurTime());

    EXPECT_EQ(expectedResult, actualResult); // random update

}
