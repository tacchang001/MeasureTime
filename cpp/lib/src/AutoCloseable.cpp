#include "AutoCloseable.h"

AutoCloseable::~AutoCloseable()
{
    try {
        close();
    }
    catch (...)
    {
        //なにかするとさらなる例外を生む可能性があるのでなにもしない
    }
}