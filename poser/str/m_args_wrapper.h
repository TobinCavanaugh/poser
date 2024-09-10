//
// Created by tobin on 2024-08-11.
//

//TODO Remove redundant spaces
/*IT IS HIGHLY RECOMMENDED YOU OVERRIDE THE FILE TYPE OF THIS IN YOUR IDE TO
BE PLAIN TEXT TO AVOID TERRIBLE INDEXING TIMES*/

//Thanks to Daniel Hardman / dhh1128  : https://gist.github.com/dhh1128/36bc220b10f6dafefa33#file-macros_overridden_by_arg_count


#ifndef POSER_ARG_INF
#define POSER_ARG_INF

#include "m_to_str.h"

//Don't worry, i used a C# script to generate this
//This used to be set to 128 total args. I'm ok with only supporting 16
#define _WS16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) to_str(_0), to_str(_1), to_str(_2), to_str(_3), to_str(_4), to_str(_5), to_str(_6), to_str(_7), to_str(_8), to_str(_9), to_str(_10), to_str(_11), to_str(_12), to_str(_13), to_str(_14), to_str(_15)
#define _WS15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) to_str(_0), to_str(_1), to_str(_2), to_str(_3), to_str(_4), to_str(_5), to_str(_6), to_str(_7), to_str(_8), to_str(_9), to_str(_10), to_str(_11), to_str(_12), to_str(_13), to_str(_14)
#define _WS14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) to_str(_0), to_str(_1), to_str(_2), to_str(_3), to_str(_4), to_str(_5), to_str(_6), to_str(_7), to_str(_8), to_str(_9), to_str(_10), to_str(_11), to_str(_12), to_str(_13)
#define _WS13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) to_str(_0), to_str(_1), to_str(_2), to_str(_3), to_str(_4), to_str(_5), to_str(_6), to_str(_7), to_str(_8), to_str(_9), to_str(_10), to_str(_11), to_str(_12)
#define _WS12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) to_str(_0), to_str(_1), to_str(_2), to_str(_3), to_str(_4), to_str(_5), to_str(_6), to_str(_7), to_str(_8), to_str(_9), to_str(_10), to_str(_11)
#define _WS11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) to_str(_0), to_str(_1), to_str(_2), to_str(_3), to_str(_4), to_str(_5), to_str(_6), to_str(_7), to_str(_8), to_str(_9), to_str(_10)
#define _WS10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) to_str(_0), to_str(_1), to_str(_2), to_str(_3), to_str(_4), to_str(_5), to_str(_6), to_str(_7), to_str(_8), to_str(_9)
#define _WS9(_0, _1, _2, _3, _4, _5, _6, _7, _8) to_str(_0), to_str(_1), to_str(_2), to_str(_3), to_str(_4), to_str(_5), to_str(_6), to_str(_7), to_str(_8)
#define _WS8(_0, _1, _2, _3, _4, _5, _6, _7) to_str(_0), to_str(_1), to_str(_2), to_str(_3), to_str(_4), to_str(_5), to_str(_6), to_str(_7)
#define _WS7(_0, _1, _2, _3, _4, _5, _6) to_str(_0), to_str(_1), to_str(_2), to_str(_3), to_str(_4), to_str(_5), to_str(_6)
#define _WS6(_0, _1, _2, _3, _4, _5) to_str(_0), to_str(_1), to_str(_2), to_str(_3), to_str(_4), to_str(_5)
#define _WS5(_0, _1, _2, _3, _4) to_str(_0), to_str(_1), to_str(_2), to_str(_3), to_str(_4)
#define _WS4(_0, _1, _2, _3) to_str(_0), to_str(_1), to_str(_2), to_str(_3)
#define _WS3(_0, _1, _2) to_str(_0), to_str(_1), to_str(_2)
#define _WS2(_0, _1) to_str(_0), to_str(_1)
#define _WS1(_0) to_str(_0)


#define _GET_OVERRIDE_S(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, NAME, ...) NAME

#define WRAP_S(...) _GET_OVERRIDE_S(__VA_ARGS__, _WS16, _WS15, _WS14, _WS13, _WS12, _WS11, _WS10, _WS9, _WS8, _WS7, _WS6, _WS5, _WS4, _WS3, _WS2, _WS1 )(__VA_ARGS__)


#endif //POSER_ARG_INF
