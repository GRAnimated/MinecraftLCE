#include <memory>
#include <string>
class UIString{
public:
    class UIStringCore{
    public:
        UIStringCore(const std::wstring&);
    };

    std::shared_ptr<std::wstring> text;
};