#pragma once
/// @brief An inline macro for object getters.
/// @param member The member variable to get.
/// @param displayName The name of the member variable for the function. Should start with a capital letter.
#define TP_OBJ_GETTER(member, displayName) [[nodiscard]] auto Get##displayName() const { return member; }
#define TP_OBJ_GETTER_REF(member, displayName) [[nodiscard]] const auto& Get##displayName() const { return member; }

#define TP_OBJ_UNDEFINED_SETTER(member, displayName) void Set##displayName(auto new##displayName)

#define TP_OBJ_GETTER_UNDEF_SETTER(member, displayName) \
    TP_OBJ_GETTER(member, displayName) \
    TP_OBJ_UNDEFINED_SETTER(member, displayName)

#define TP_OBJ_GETTER_REF_UNDEF_SETTER(member, displayName) \
    TP_OBJ_GETTER_REF(member, displayName) \
    TP_OBJ_UNDEFINED_SETTER(member, displayName)

#define TP_OBJ_MOVE_NO_COPY(className) \
className(const className& other) = delete; \
className& operator=(const className& other) = delete; \
className(className&& other) noexcept; \
className& operator=(className&& other) noexcept;

#define TP_OBJ_IMPL_MOVE_DEFAULT(className) \
    className::className(className&& other) noexcept = default; \
    className& className::operator=(className&& other) noexcept = default

#define TP_OBJ_IMPL_DESTRUCTOR_MOVE_DEFAULT(className) \
    className::~className() = default; \
    TP_OBJ_IMPL_MOVE_DEFAULT(className)
