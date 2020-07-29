/*
 * Netero sources under BSD-3-Clause
 * see LICENSE.txt
 */

#pragma once

#include <memory>

namespace netero::patterns {

#define DECLARE_SINGLETON(type) friend netero::patterns::ISingleton<type>

template<class T>
class ISingleton {
    public:
    virtual ~ISingleton() = 0;

    static T& GetInstance()
    {
        static T staticInstance;
        return staticInstance;
    }
};

template<class T>
ISingleton<T>::~ISingleton() = default;

} // namespace netero::patterns
