#ifndef gen_prog__boost__filesystem__remove_base_hpp
#define gen_prog__boost__filesystem__remove_base_hpp



#include <boost/filesystem/path.hpp>



namespace gp {
namespace filesystem {

inline boost::filesystem::path remove_base(const boost::filesystem::path & pathIn, const boost::filesystem::path & baseIn)
{
    boost::filesystem::path path = pathIn.generic_string();
    boost::filesystem::path base = baseIn.generic_string();

    boost::filesystem::path::iterator itPath = path.begin();
    boost::filesystem::path::iterator itBase = base.begin();
    while ((path.end() != itPath) && (base.end() != itBase) && (*itPath == *itBase))
    {
        ++itPath;
        ++itBase;
    }

    boost::filesystem::path relativePath;
    while(path.end() != itPath)
    {
        relativePath /= *itPath;
        ++itPath;
    }

    return relativePath;
}

} // namespace filesystem
} // namespace gp

#endif // ** gen_prog__boost__filesystem__remove_base_hpp ** //
