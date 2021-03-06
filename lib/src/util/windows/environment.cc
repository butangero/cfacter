#include <facter/util/environment.hpp>
#include <boost/algorithm/string.hpp>
#include <functional>

using namespace std;

namespace facter { namespace util {

    struct search_path_helper
    {
        search_path_helper()
        {
            string paths;
            if (environment::get("PATH", paths)) {
                auto is_sep = bind(equal_to<char>(), placeholders::_1, environment::get_path_separator());
                boost::trim_if(paths, is_sep);
                boost::split(_paths, paths, is_sep, boost::token_compress_on);
            }
        }

        vector<string> const& search_paths() const
        {
            return _paths;
        }

     private:
         vector<string> _paths;
    };

    char environment::get_path_separator()
    {
        return ';';
    }

    static search_path_helper helper;

    vector<string> const& environment::search_paths()
    {
        return helper.search_paths();
    }

    void environment::reload_search_paths()
    {
        helper = search_path_helper();
    }

}}  // namespace facter::util
