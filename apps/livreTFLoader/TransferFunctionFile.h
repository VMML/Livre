/**
 * Adapted from:
 *
 * ivs - interactive volume splatter
 *       by @author Philipp Schlegel (schlegel@ifi.uzh.ch)
 **/

#ifndef TRANSFER_FUNCTION_FILE_H
#define TRANSFER_FUNCTION_FILE_H

#include <string>
#include <vector>
#include <fstream>

namespace livre
{

/**
 * Transfer function file.
 **/
class TransferFunctionFile
{
public:
    enum Mode
    {
        READ  = 1,
        WRITE = 2
    };

    struct Item
    {
        float r, g, b, a; //, s, d, am;
    };

    typedef std::vector<Item> ItemVector;


    TransferFunctionFile(const std::string& _filename, Mode _mode = READ);

    virtual ~TransferFunctionFile();

    // returns the filename
    virtual const std::string &getFilename() const;

    // True if the file exists, false else.
    virtual bool exists();

    // Open the file. Throw an exception in case of failure.
    virtual void open();

    // Close the file. No status is returned.
    virtual void close();

    ItemVector readTransferFunction();
    void writeTransferFunction(const ItemVector &_data);

protected:
    // filename
    std::string filename_;

    // mode
    Mode mode_;

    // file
    std::fstream file_;
};

inline const std::string &TransferFunctionFile::getFilename() const
{
    return filename_;
}


} // namespace

#endif
