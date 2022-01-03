// Signals2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <boost/signals2.hpp>
#include <memory_resource>
#include <boost/function.hpp>
#include <boost/bind.hpp>

void g(int i) { std::cout << "nice" << i << std::endl; }

class server
{
public:
    void attach(const boost::function<void()>& cb)
    {
        cb_ = cb;
    }
    void notify() { cb_(); }
private:
    boost::function<void()> cb_;
};

class client
{
public:
    client(server& s)
    {
        s.attach(boost::bind(&client::update, this));
    }
    void update() { std::cout << "the world is not enough" << std::endl; }
};

int main()
{
    boost::function<void (int)> fn = g;
    g(1);

    server server1 = server();

    client client1 = client(server1);

    server1.notify();
}

/* signals
struct Hello
{
    void operator () () const
    {
        std::cout << "Hello";
    }
};

void f()
{
    std::cout << "nice one" << std::endl;
};
int main()
{
    boost::signals2::signal<void()> sig;

    sig.connect(&f);
    sig();
    std::cout << "Hello World!\n";
}
*/


/* used to nothing

typedef void (*callback) (void*);

class server
{
public:
    void attach(callback cb, void* pvData)
    {
        cb_ = cb;
        pvData_ = pvData;
    }
    void notify() { cb_(pvData_); }
private:
    callback cb_;
    void* pvData_;
};

class client
{
public:
    client(server& s) { s.attach(cbStub, this); }

    static void update() { std::cout << "nice one" << std::endl; }

private:
    static void cbStub(void* data)
    {
        client* c = static_cast<client*>(data);
        c->update();
    }
};

int main()
{

}
*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
