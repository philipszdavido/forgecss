//
//  Value.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef Value_hpp
#define Value_hpp

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

struct Value {
    virtual ~Value() = default;
};

struct DimensionValue : Value {
    double value;
    string unit;
};

struct ColorValue : Value {
    string value;
};

struct KeywordValue : Value {
    string value;
};

struct FunctionValue : Value {
    string name;
    vector<shared_ptr<Value>> args;
};

struct NumberValue     : Value { double value; };
struct PercentageValue : Value { double value; };
struct StringValue     : Value { std::string value; };

#endif /* Value_hpp */
