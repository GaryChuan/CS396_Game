/******************************************************************************
filename: crtp.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the defintion of the CRTP helper class.
  CRTP - Curiously Recurring Template Pattern.

  It also contains the helper overload for overloading lambdas when visiting
  variants.
******************************************************************************/
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