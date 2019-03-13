#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>


class printer
{
public:
    explicit printer(boost::asio::io_context& io)
        :timer_(io, boost::asio::chrono::seconds(1))
        , count_(0)
    {
        timer_.async_wait(boost::bind(&printer::print, this));
    }

    void print()
    {
        if (count_ < 5)
        {
            std::cout << count_ << std::endl;
            ++count_;
            timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(1));
            timer_.async_wait(boost::bind(&printer::print, this));
        }
        std::cout << "Hello, World!" << std::endl;
    }

private:
    boost::asio::steady_timer timer_;
    int count_;
};


int main()
{
    boost::asio::io_context io;
    printer p(io);
    io.run();

    return 0;
}