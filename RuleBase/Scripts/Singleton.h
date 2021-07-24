#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>

namespace utility {
    template<class T>
    class Singleton {
       protected:
        Singleton() {}

        virtual ~Singleton() {}

       public:
        // インスタンスを取得する
        static std::weak_ptr<T> Instance() {
            if ( instance == nullptr ) instance.reset( new T() );
            return instance;
        }

       private:
        static std::shared_ptr<T> instance;
    };

    template<class T>
    std::shared_ptr<T> Singleton<T>::instance = nullptr;
}  // namespace utility

#endif  // !SINGLETON_H
