#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>


class printer
{
public:
    explicit printer(boost::asio::io_context& io)
        : strand_(io)
        , timer1_(io, boost::asio::chrono::seconds(1))
        , timer2_(io, boost::asio::chrono::seconds(1))
        , count_(0)
    {
        timer1_.async_wait(boost::asio::bind_executor(strand_,
                                                      boost::bind(&printer::print1, this)));

        timer2_.async_wait(boost::asio::bind_executor(strand_,
                                                      boost::bind(&printer::print2, this)));
    }

    ~printer()
    {
        std::cout << "Final count is " << count_ << std::endl;
    }

    void print1()
    {
        if (count_ < 10)
        {
            std::cout << "Timer1: " << count_ << std::endl;
            ++count_;
            timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(1));
            timer1_.async_wait(boost::asio::bind_executor(strand_,
                                                          boost::bind(&printer::print1,
                                                                      this)));
        }
    }

    void print2()
    {
        if (count_ < 10)
        {
            std::cout << "Timer2: " << count_ << std::endl;
            ++count_;
            timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));
            timer2_.async_wait(boost::asio::bind_executor(strand_,
                                                          boost::bind(&printer::print2,
                                                                      this)));
        }
    }

private:
    boost::asio::io_context::strand strand_;
    boost::asio::steady_timer timer1_;
    boost::asio::steady_timer timer2_;
    int count_;
};


int main()
{
    boost::asio::io_context io;
    printer p(io);
    boost::thread t(boost::bind(&boost::asio::io_context::run, &io));
    io.run();
    t.join();

    return 0;
}