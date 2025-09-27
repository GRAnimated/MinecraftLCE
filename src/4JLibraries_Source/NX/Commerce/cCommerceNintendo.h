#pragma once

#include "Commerce/cCommerce.h"

class cCommerceNintendo : public cCommerce {
public:
    // directly ported from Wii U
    virtual bool LogIn() = 0;
    virtual void GetShoppingCatalog() = 0;
    virtual bool GetCommerceInfo() = 0;
    virtual bool tick() = 0;
    virtual bool PurchaseBedrock();
};
