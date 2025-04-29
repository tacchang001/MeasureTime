
class AutoCloseable
{
public:
    virtual ~AutoCloseable();
    virtual void Close() {}
};
