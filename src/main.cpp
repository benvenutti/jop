#include <boost/spirit/home/x3.hpp>

#include <iostream>
#include <string>
#include <variant>
#include <vector>

//---------------------------------------------------------------------------------------------------------------------

namespace parser
{

namespace x3 = boost::spirit::x3;

const auto floating_point = x3::real_parser< double, x3::strict_real_policies< double > >{};
const auto integer        = x3::int_;
const auto list_numbers   = ( floating_point | integer ) % ',';

} // namespace parser

//---------------------------------------------------------------------------------------------------------------------

// TODO C++20: https://en.cppreference.com/w/cpp/utility/variant/visit
template < class... Ts >
struct overloaded : Ts...
{
    using Ts::operator()...;
};

template < class... Ts >
overloaded( Ts... ) -> overloaded< Ts... >;

//---------------------------------------------------------------------------------------------------------------------

int main()
{
    const std::string input = { "2.7, 4, 5, .9, 6.006, 2, 3, 4" };

    auto       beg = input.begin();
    const auto end = input.end();

    std::vector< std::variant< double, int > > numbers;

    const auto ok = boost::spirit::x3::phrase_parse( beg, //
                                                     end,
                                                     parser::list_numbers,
                                                     boost::spirit::x3::space,
                                                     numbers );

    if ( ok && beg == end )
    {
        for ( const auto& num : numbers )
        {
            std::visit( overloaded{
                            []( const int arg ) { std::cout << "int: " << arg << std::endl; },
                            []( const double arg ) { std::cout << "double: " << arg << std::endl; },
                        },
                        num );
        }

        return EXIT_SUCCESS;
    }
    else
    {
        std::cerr << "error parsing" << std::endl;

        return EXIT_FAILURE;
    }
}
