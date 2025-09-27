#pragma once

#include "Commerce/cProductInfo.h"
#include "string"

class cCommerce {
public:
    // Directly ported from Wii U
    enum eDLCCatalogState {};

    static eDLCCatalogState sDLCCatalogState;
    static bool sCatalogListRetrieved;
    static bool sCatalogListInfoRetrieved;

    virtual void nullsub_688();
    virtual ~cCommerce();
    virtual void ClearProductInfo();
    virtual bool PurchaseDLCByIndex(unsigned int, int);
    virtual bool OwnsBundleContainingPack(unsigned int);
    virtual bool PurchaseDLCByPackID(unsigned int);
    virtual bool HasPurchased(unsigned int, bool*, bool*);
    virtual bool GetDLCProductInfo(cProductInfo**, unsigned int*, unsigned int, bool);  // unk return type
    virtual bool CheckForEmptyStore(int);
    virtual bool ProductListAvailable();
    virtual void GetProductTextureName(std::wstring&, char*);
    virtual void ShowStoreIcon();
    virtual void HideStoreIcon();
    virtual bool GetDLCCatalogListRetrieved();
    virtual bool GetDLCCatalogListInfoRetrieved();
    virtual void SetDLCCatalogState(eDLCCatalogState state);
    virtual bool AttemptLogIn();
};
