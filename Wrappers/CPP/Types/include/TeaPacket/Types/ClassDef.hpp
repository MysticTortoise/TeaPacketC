#pragma once

#define TP_ClassWrapperDefP(Name, Prefix, ParamName) \
Prefix##_##Name* p;\
\
    Name(const Name& other) = delete;\
    Name& operator=(const Name& other) = default;\
    Name(Name&& other) noexcept:\
    p(other.p)\
    {\
        other.p = nullptr;\
    }\
    Name& operator=(Name&& other) noexcept\
    {\
        if (this != &other)\
        {\
            Prefix##_##Name##_Destroy(p);\
            p = other.p;\
            other.p = nullptr;\
        }\
        return *this;\
    }\
    \
    explicit Name(const ParamName& params):\
    p(Prefix##_##Name##_Create(&params))\
    {}\
    \
    ~Name()\
    {\
        Prefix##_##Name##_Destroy(p);\
    }

#define TP_ClassWrapperDef(Name, Prefix) TP_ClassWrapperDefP(Name, Prefix, Prefix##_##Name##Params)