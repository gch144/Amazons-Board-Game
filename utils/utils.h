#ifndef UTILS_H
#define UTILS_H

//used in screen clearing
#ifdef __unix__         
#define OS_LINUX
#elif defined(_WIN32) || defined(WIN32) 
#define OS_Windows
#endif

void clrscr();

#endif // !UTILS_H
