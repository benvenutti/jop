#include <jvp/Parser.hpp>

#include <boost/spirit/home/x3.hpp>

#include <catch2/catch.hpp>

#include <iomanip>
#include <string>
#include <vector>

SCENARIO( "Valid identifier", "[identifier]" )
{
    const std::vector< std::string > str = { "n",     //
                                             "n1",    //
                                             "n1n",   //
                                             "n1n1",  //
                                             "n_",    //
                                             "n.",    //
                                             "n:",    //
                                             "n1_",   //
                                             "n1.",   //
                                             "n1:",   //
                                             "n_n",   //
                                             "n.n",   //
                                             "n:n"    //
                                             "n1_n",  //
                                             "n1.n",  //
                                             "n1:n"   //
                                             "n_n1",  //
                                             "n.n1",  //
                                             "n:n1"   //
                                             "n1_n1", //
                                             "n1.n1", //
                                             "n1:n1" };

    for ( const auto& id : str )
    {
        INFO( std::string{ "id: " } << std::quoted( id ) );

        auto       beg = id.begin();
        const auto end = id.end();

        std::string result;

        const auto ok = boost::spirit::x3::phrase_parse( beg, //
                                                         end,
                                                         Parser::identifier,
                                                         boost::spirit::x3::ascii::space,
                                                         result );

        REQUIRE( ok );
        REQUIRE( beg == end );
        REQUIRE( result == id );
    }
}

SCENARIO( "Invalid identifier", "[identifier]" )
{
    const std::vector< std::string > str = { "1",  //
                                             "1n", //
                                             "1_", //
                                             "1.", //
                                             "1:", //
                                             "1$", //
                                             "1#", //
                                             "1@", //
                                             "1!" };

    for ( const auto& id : str )
    {
        INFO( std::string{ "id: " } << std::quoted( id ) );

        auto       beg = id.begin();
        const auto end = id.end();

        std::string result;

        const auto ok = boost::spirit::x3::phrase_parse( beg, //
                                                         end,
                                                         Parser::identifier,
                                                         boost::spirit::x3::ascii::space,
                                                         result );

        REQUIRE_FALSE( ok );
        REQUIRE( beg != end );
        REQUIRE( result.empty() );
    }
}
