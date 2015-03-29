#ifndef _LOGGER_H_
#define _LOGGER_H_ 1

#include <iostream>

#define LOG_DEBUG(msg) std::cout << "DEBUG: " << msg << std::endl;
#define LOG_WARNING(msg) std::cout << "WARNING: " << msg << std::endl;
#define LOG_ERROR(msg) std::cout << "ERROR: " << msg << std::endl;
#define LOG_CALLED std::cout << "CALLED" << std::endl;

#endif
