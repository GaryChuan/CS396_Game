#pragma once

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...)->overload<Ts...>;

template <typename T>
struct CRTP
{
public:
    T& underlying() noexcept
    { 
        return static_cast<T&>(*this); 
    }

    const T& underlying() const noexcept 
    { 
        return static_cast<const T&>(*this); 
    }

protected:
    CRTP() = default;
    friend T;
};