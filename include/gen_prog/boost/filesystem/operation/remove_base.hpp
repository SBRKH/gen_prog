


#include <boost/filesystem/path.hpp>



namespace gp {
namespace filesystem {

boost::filesystem::path remove_base(const boost::filesystem::path & path, const boost::filesystem::path & base)
{
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