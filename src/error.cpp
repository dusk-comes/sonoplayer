#include "error.hpp"

error::error(const char *msg) : message{msg} {}

const char *error::what() const throw() {return message;}

