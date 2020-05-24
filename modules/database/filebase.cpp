#include "filebase.h"

FileBase::FileBase()
{

}

bool FileBase::open(QString path, bool mk)
{
    QString extensions = FILE_EXTENSIONS;
    //return dir.openDir(path, extensions, mk);
    return mk;
}
