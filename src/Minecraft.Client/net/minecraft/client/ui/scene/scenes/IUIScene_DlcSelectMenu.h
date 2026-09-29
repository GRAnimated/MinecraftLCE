class DLCPack;

enum eDLCContentType { MAP, SKIN };

class IUIScene_DlcSelectMenu {
public:
    IUIScene_DlcSelectMenu(eDLCContentType);

    bool char0;
    DLCPack* mDLCPack;
    eDLCContentType mDLCContentType;
};