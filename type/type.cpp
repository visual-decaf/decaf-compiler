#include "type.h"

static const std::map<decaf::Type::Classification, std::string> type_name_of{
    {decaf::Type::Classification::INVALID, "INVALID"},
    {decaf::Type::Classification::INT, "INT"},
    {decaf::Type::Classification::DOUBLE, "DOUBLE"},
    {decaf::Type::Classification::BOOL, "BOOL"},
};