#include "Commerce/cCommerce.h"

bool cCommerce::PurchaseDLCByIndex(unsigned int, int) {
    return false;
}

bool cCommerce::PurchaseDLCByPackID(unsigned int) {
    return false;
}

bool cCommerce::GetDLCProductInfo(cProductInfo**, unsigned int*, unsigned int, bool) {
    return false;
}

bool cCommerce::CheckForEmptyStore(int) {
    return false;
}

bool cCommerce::ProductListAvailable() {
    return false;
}

void cCommerce::GetProductTextureName(std::wstring&, char*) {}
void cCommerce::ShowStoreIcon() {}
void cCommerce::HideStoreIcon() {}

bool cCommerce::GetDLCCatalogListRetrieved() {
    return sCatalogListInfoRetrieved;
}

bool cCommerce::GetDLCCatalogListInfoRetrieved() {
    return sCatalogListInfoRetrieved;
}

void cCommerce::SetDLCCatalogState(eDLCCatalogState state) {
    sDLCCatalogState = state;
}

bool cCommerce::AttemptLogIn() {
    return true;
}
