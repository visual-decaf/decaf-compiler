#include "type.h"

const std::map<decaf::Type::Classification, std::string> decaf::Type::type_name_of{
    {decaf::Type::Classification::INVALID, "INVALID"},
    {decaf::Type::Classification::INT, "INT"},
    {decaf::Type::Classification::DOUBLE, "DOUBLE"},
    {decaf::Type::Classification::BOOL, "BOOL"},
};
boost::json::value decaf::Type::to_json() {
    boost::json::string result{type_name_of.at(this->classification)};
    return result;
}
