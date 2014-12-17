/****************************************************************************
** Pokemon XY Save Decrypter
** Spiffy
** Special thanks to Monsi Terdex, and his program demonstrating XOR encryption:
** http://monsiterdex.wordpress.com/2013/05/17/simple-file-encryption-in-c-rivest-cipher-4-rc4-byte-inversion-cycling-and-xor/
****************************************************************************/

#include <QApplication>

#include "decrypter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Decrypter decrypter;
    decrypter.show();
    return app.exec();
}
