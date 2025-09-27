#include "SharedConstants.h"
#include "net/minecraft/util/Calendar.h"

std::wstring SharedConstants::sVersionString = L"1.12";

void SharedConstants::staticCtor() {
    sAcceptableLetters = L" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_'abcdefghijklmnopqrstuvwxyz{|}~ ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜø£Ø×ƒáíóúñÑªº¿®¬½¼¡«»ã";

    sIsHalloweenDay = Calendar::GetMonth() == 10 && Calendar::GetDayOfMonth() == 31;

    sIsHalloween = (Calendar::GetMonth() == 10 && Calendar::GetDayOfMonth() > 19)
                || (Calendar::GetMonth() == 11 && Calendar::GetDayOfMonth() < 4);

    sIsXmas = (Calendar::GetMonth() == 12 && Calendar::GetDayOfMonth() > 23)
           || (Calendar::GetMonth() == 1 && Calendar::GetDayOfMonth() < 2);

    sIsDec17ToDec23 = Calendar::GetMonth() == 12 && Calendar::GetDayOfMonth() > 16
                   && Calendar::GetMonth() == 12 && Calendar::GetDayOfMonth() < 24;
}