//
//  EnumToString.h
//  ComputerGraphicsWithOpenGL
//
//  Created by GEORGE QUENTIN on 07/02/2019.
//  Copyright © 2019 GEORGE QUENTIN. All rights reserved.
//

#ifndef EnumToString_h
#define EnumToString_h

// https://codereview.stackexchange.com/questions/14309/conversion-between-enum-and-string-in-c-class-header
// This is the type that will hold all the strings.
// Each enumeration type will declare its own specialization.
// Any enum that does not have a specialization will generate a compiler error
// indicating that there is no definition of this variable (as there should be
// be no definition of a generic version).
template<typename T>
struct enumStrings
{
    static char const* data[];
};

// This is a utility type.
// Created automatically. Should not be used directly.
template<typename T>
struct enumRefHolder
{
    T& enumVal;
    enumRefHolder(T& enumVal): enumVal(enumVal) {}
};
template<typename T>
struct enumConstRefHolder
{
    T const& enumVal;
    enumConstRefHolder(T const& enumVal): enumVal(enumVal) {}
};

// The next two functions do the actual work of reading/writing an
// enum as a string.
template<typename T>
std::ostream& operator<<(std::ostream& str, enumConstRefHolder<T> const& data)
{
    return str << enumStrings<T>::data[(int)data.enumVal];
}

template<typename T>
std::istream& operator>>(std::istream& str, enumRefHolder<T> const& data)
{
    std::string value;
    str >> value;
    
    // These two can be made easier to read in C++11
    // using std::begin() and std::end()
    //
    static auto begin  = std::begin(enumStrings<T>::data);
    static auto end    = std::end(enumStrings<T>::data);
    
    auto find   = std::find(begin, end, value);
    if (find != end)
    {
        data.enumVal = static_cast<T>(std::distance(begin, find));
    }
    return str;
}


// This is the public interface:
// use the ability of function to deduce their template type without
// being explicitly told to create the correct type of enumRefHolder<T>
template<typename T>
enumConstRefHolder<T>  enumToString(T const& e) {return enumConstRefHolder<T>(e);}

template<typename T>
enumRefHolder<T>       enumFromString(T& e)     {return enumRefHolder<T>(e);}


#endif /* EnumToString_h */
