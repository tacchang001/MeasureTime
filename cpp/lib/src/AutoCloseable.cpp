#include "AutoCloseable.h"

AutoCloseable::~AutoCloseable()
{
    try {
        Close();
    }
    catch (...)
    {
        //なにかするとさらなる例外を生む可能性があるのでなにもしない
    }
}