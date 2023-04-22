#ifndef ERROR_HPP
#define ERROR_HPP

#include <exception>

class error : public std::exception
{
    private:
        const char *message;

    public:
        error(const char*);
        
        const char *what() const throw();
};

#endif /* ERROR_HPP */
