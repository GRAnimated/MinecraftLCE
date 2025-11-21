#pragma once

#include "Commerce/cCommerce.h"
#include "cCommerceNintendo.h"

class cCommerceNintendoNX : public cCommerceNintendo {
    // ORDER MAY BE WRONG
    bool PurchaseDLCByIndex(unsigned int, int) override;
    bool PurchaseDLCByPackID(unsigned int) override;
    bool GetDLCProductInfo(cProductInfo**, unsigned int*, unsigned int, bool) override;
    void SetDLCCatalogState(eDLCCatalogState state) override;
    bool AttemptLogIn() override;
    bool LogIn() override;
    void GetShoppingCatalog() override;  // hmmm this is a nullsub on nx
    bool GetCommerceInfo() override;
    bool PurchaseBedrock() override;
    bool tick() override;  // might be wrong???
};
