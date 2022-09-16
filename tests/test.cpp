#include <cstdio>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
using namespace std::chrono_literals;

class Test{
    std::string name;
  public:
    Test(const std::string && str): name{str}{}
    ~Test(){
        std::cout<< "Destroy: "<< name<<'\n';
    }
};


int main(){
    std::unique_ptr<Test> t2;
    t2.
    std::string t {"primero"};
    std::cout << & t<<'\n';
    std::cin.get();
    std::cout << & t<<'\n';
    std::cin.get();
}