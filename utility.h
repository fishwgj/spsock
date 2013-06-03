//
//  utility.h
//  simple_sock
//
//  Created by wgj on 13-6-3.
//  Copyright (c) 2013年 wgj. All rights reserved.
//

#ifndef simple_sock_utility_h
#define simple_sock_utility_h


#define VERIFY_FATAL(x, v, msg) \
do { \
if ((x) == (v)) \
{ perror((msg)); exit(0);} \
} while (0)




#endif
