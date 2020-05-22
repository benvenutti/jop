#pragma once

#include <boost/spirit/home/x3.hpp>

#include <string>

namespace Parser
{

namespace x3 = boost::spirit::x3;

struct identifier_class
{
};

const x3::rule< identifier_class, std::string > identifier = "identifier";

const auto identifier_def =
    x3::lexeme[x3::alpha >> *( x3::alnum | x3::char_( '_' ) | x3::char_( '.' ) | x3::char_( ':' ) )];

BOOST_SPIRIT_DEFINE( identifier )

} // namespace Parser
