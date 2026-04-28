//
//  Value.hpp
//  forgecss
//
//  Created by Chidume Nnamdi on 21/04/2026.
//

#ifndef Value_hpp
#define Value_hpp

#include <stdio.h>

class Value {
    
};

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

#endif /* Value_hpp */
