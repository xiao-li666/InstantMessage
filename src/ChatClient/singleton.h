#ifndef SINGLETON_H
#define SINGLETON_H
#include "global.h"

template<class T>
class Singleton{
protected:
    Singleton() = default;
    Singleton(const Singleton<T>& st) = delete;
    Singleton& operator=(const Singleton<T>&st) = delete;

    //可以选择使用静态局部变量
    static std::shared_ptr<T> _instance;

public:
    ~Singleton(){
        std::cout << "this is singleton destruct!" <<std::endl;
    }

    static std::shared_ptr<T> GetInstance(){
        static std::once_flag s_flag;
        std::call_once(s_flag,[](){
            _instance = std::shared_ptr<T>(new T());
        });
        return _instance;
    }

    void PrintAddress(){
        std::cout << _instance.get() << std::endl;
    }

};

template<class T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;
// template<class T>
// class Singleton{
// protected:
//     Singleton() = default;
//     Singleton(const Singleton<T>& st) = delete;
//     Singleton& operator=(const Singleton<T>&st) = delete;

//     //可以选择使用静态局部变量

// public:
//     ~Singleton(){}

//     static std::shared_ptr<T> GetInstance(){
//         static std::shared_ptr<T> _instance = std::make_shared<T>();
//         return _instance;
//     }

// };
#endif // SINGLETON_H

