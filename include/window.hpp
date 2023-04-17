#include <bits/c++config.h>
#include <vector>
#include <functional>

class window
{
    private:
        using floating_t = double;
        using output_container = std::vector<floating_t>;
        using function = std::function<void(floating_t&)>;

        static output_container handler(const std::size_t, const function&);

    public:
        static output_container hanning(const std::size_t);
        static output_container hamming(const std::size_t);
        static output_container blackman(const std::size_t);
        static output_container flattop(const std::size_t);
        //static output_container bartlett(const std::size_t);
        //static output_container kaiser(const std::size_t);
        //static output_container rectangular(const std::size_t);

};
