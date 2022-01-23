//
//  util.h
//  CM_SIR_PROJECT
//
//  Created by DEBASMIT ROY on 24/12/21.
//

#ifndef headers_preprocessors_h
#define headers_preprocessors_h

// 17.4.1.2 Headers
  
// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
  
#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif
  
// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
  
#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

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
#define NULL_CHECK_WRAPPER(p) if(p!=nullptr)


#define INVALID_INPUT_FLAG 0
#define NULL_VALUE_FLAG -1
#define OK 1
#define INVALID_INPUT_MSG printf("Error! INVALID_INPUT")
#define NULL_VALUE_MSG printf("Error! NULL_VALUE_ALLOOCATED")
#define TITLE(name) printf("\n********************* %s *********************\n",(name))
#define TITLE2(name) printf("\n%s :\n",(name))
#define DIVIDER printf("\n.........................................................................................\n")
#define SENTINEL -999
using namespace std;

template<typename t>
void scanVect(vector<t> &arr,t n)  {  for(int i=0;i<n;i++) cin>>arr[i]; }
template<typename t>
void printArr(t *arr,int n) {for(int i=0;i<n;i++) cout<<arr[i]<<" "; printf("\n");}
template<typename t>
void printVect(vector<t> &arr){for(auto x:arr) cout<<x<<" "<<endl; cout<<endl;}

#endif /* util_h */
