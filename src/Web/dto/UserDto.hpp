#ifndef _USERDTO_HPP
#define _USERDTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class MessageDto : public oatpp::DTO
{

    DTO_INIT(MessageDto, DTO)

    DTO_FIELD(Int32, statusCode);
    DTO_FIELD(String, message);
};

class UserDto : public oatpp::DTO
{

    DTO_INIT(UserDto, DTO)

    DTO_FIELD(Int64, id);
    DTO_FIELD(String, name, "user_name");

public:
    UserDto() = default;

    UserDto(v_int64 pId, const String &pName) : id(pId), name(pName) {}
};

#include OATPP_CODEGEN_END(DTO)

#endif