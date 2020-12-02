#pragma once

#include <iostream>
#include <string.h>

using namespace std;

#define ZPRED(format, ...) do\
{\
	printf("\033[1;31m");\
	printf(format, ##__VA_ARGS__);\
	printf("\033[0m");\
	fflush(stdout);\
}while(0)

#define ZPBLUE(format, ...) do\
{\
	printf("\033[1;34m");\
	printf(format, ##__VA_ARGS__);\
	printf("\033[0m");\
	fflush(stdout);\
}while(0)

#define ZPYELLOW(format, ...) do\
{\
	printf("\033[1;33m");\
	printf(format, ##__VA_ARGS__);\
	printf("\033[0m");\
	fflush(stdout);\
}while(0)

#define ZPPURPLE(format, ...) do\
{\
	printf("\033[1;35m");\
	printf(format, ##__VA_ARGS__);\
	printf("\033[0m");\
	fflush(stdout);\
}while(0)

#define ZPWHITE(format, ...) do\
{\
	printf("\033[1;37m");\
	printf(format, ##__VA_ARGS__);\
	printf("\033[0m");\
	fflush(stdout);\
}while(0)

#define ASSERT(cond, format, ...) do\
    {\
        if(cond)\
        {\
            (void)0;\
        }\
        else\
        {\
            ZPRED("%s:%d, ASSERT (%s) failed(", __FILE__, __LINE__, #cond);\
            ZPRED(format, ##__VA_ARGS__);\
            ZPRED(")\r\n");\
			printf("\033[?25h");\
            exit(1);\
        }\
    }while(0)


#define ASSERT_RETURN_VAL(cond, val, format, ...) do\
    {\
        if(cond)\
        {\
            (void)0;\
        }\
        else\
        {\
            ZPRED("%s:%d(", __FILE__, __LINE__);\
            ZPRED(format, ##__VA_ARGS__);\
            ZPRED(")\r\n");\
            return val;\
        }\
    }while(0)

#define ASSERT_RETURN(cond, format, ...) do\
    {\
        if(cond)\
        {\
            (void)0;\
        }\
        else\
        {\
            ZPRED("%s:%d(", __FILE__, __LINE__);\
            ZPRED(format, ##__VA_ARGS__);\
            ZPRED(")\r\n");\
            return;\
        }\
    }while(0)

#define SAFE_DELETE(point) do\
    {\
        if(point != NULL)\
        {\
            delete []point;\
            point = NULL;\
        }\
    }while(0)

#define NEW(point, type, size) do\
    {\
        SAFE_DELETE(point);\
        point = new (nothrow) type[size];\
        ASSERT(point != NULL, "allocate memory failed");\
    }while(0)

#define NEW0(point, type, size) do\
    {\
        SAFE_DELETE(point);\
        point = new (nothrow) type[size];\
        ASSERT(point != NULL, "allocate memory failed");\
        memset(point, 0, sizeof(type) * size);\
    }while(0)

#define CREATE_THREAD(thread_run, param, stack_size_in_byte) do\
{\
    pthread_attr_t attribute;\
    ASSERT(pthread_attr_init(&attribute) == 0, "");\
    ASSERT(pthread_attr_setstacksize(&attribute, stack_size_in_byte) == 0, "");\
    pthread_t tid;\
    ASSERT(pthread_create(&tid, &attribute, thread_run, param) == 0, "");\
    ASSERT(pthread_detach(tid) == 0, "");\
}while(0)
