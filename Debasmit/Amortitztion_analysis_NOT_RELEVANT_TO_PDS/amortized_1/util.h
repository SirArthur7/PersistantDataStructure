//
//  util.h
//  adv_DSA
//
//  Created by DEBASMIT ROY on 24/12/21.
//

#ifndef util_h
#define util_h

//
//  util1.h
//  DSA_LAB
//
//  Created by DEBASMIT ROY on 14/09/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define llu long long unsigned int
#define ll long long int


#define scan_int(a)  scanf("%d",&(a));
#define scan_llu(a)  scanf("%llu",&(a));
#define scan_ll(a)  scanf("%lld",&(a));
#define scan_fl(a)  scanf("%f",&(a));


#define print_int(a)  printf("%d",(a));
#define rep_fwd(i,init,up_limit) for(int (i)=(init);(i)<(up_limit);(i)++)
#define ENDLINE printf("\n")
#define CHECK_FLAG(flag) { if(flag!=OK) return flag; }
#define NULL_CHECK(p) { if(p==NULL) return NULL_VALUE_FLAG; }


#define INVALID_INPUT_FLAG 0
#define NULL_VALUE_FLAG -1
#define OK 1
#define INVALID_INPUT_MSG printf("Error! INVALID_INPUT")
#define NULL_VALUE_MSG printf("Error! NULL_VALUE_ALLOOCATED")
#define TITLE(name) printf("\n********************* %s *********************\n",(name))
#define TITLE2(name) printf("\n%s :\n",(name))

#endif /* util_h */
