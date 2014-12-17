/****************************************************************************
** Pokemon XY Save Decrypter
** Spiffy
** Special thanks to Monsi Terdex, and his program demonstrating XOR encryption:
** http://monsiterdex.wordpress.com/2013/05/17/simple-file-encryption-in-c-rivest-cipher-4-rc4-byte-inversion-cycling-and-xor/
****************************************************************************/

#include <QtGui>
#include "decrypter.h"
//typedef char BYTE;
//! [0]
Decrypter::Decrypter()
{
    keystreamfilename="";
    savefilename="";

    QDesktopWidget desk;
    qreal px_width = desk.width() / 2;
    //qreal px_height = desk.height() / 2;

    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *keyBox = new QHBoxLayout;
    QPushButton *keystreamButton=new QPushButton("Load Keystream");
    connect(keystreamButton, SIGNAL(clicked()), this, SLOT(on_keystreamButton_clicked()));
    keystreamPathDisplay=new QLineEdit;
    keystreamPathDisplay->setReadOnly(true);
    keystreamPathDisplay->setMinimumWidth(px_width);
    keyBox->addWidget(keystreamPathDisplay);
    keyBox->addWidget(keystreamButton);

    QHBoxLayout *saveBox = new QHBoxLayout;

    QPushButton *saveButton=new QPushButton("Load Save");
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));
    savePathDisplay=new QLineEdit;
    savePathDisplay->setReadOnly(true);
    savePathDisplay->setMinimumWidth(px_width);
    saveBox->addWidget(savePathDisplay);
    saveBox->addWidget(saveButton);

    //disable this until we have both a keystream and save path
    decryptButton=new QPushButton("Decrypt Save");
    connect(decryptButton, SIGNAL(clicked()), this, SLOT(on_decryptButton_clicked()));
    decryptButton->setEnabled(false);

    QPushButton *quitButton=new QPushButton("Quit");
    connect(quitButton, SIGNAL(clicked()), this, SLOT(on_quitButton_clicked()));

    layout->addLayout(keyBox);
    layout->addLayout(saveBox);
    layout->addWidget(decryptButton);
    layout->addWidget(quitButton);
    this->setLayout(layout);
//! [2]

//! [3] //! [4]
    //mainLayout->addWidget(verticalGroupBox);
//! [4] //! [5]
    //setLayout(mainLayout);
    setWindowTitle(tr("Pokemon XY Save Decrypter"));
}
//! [5]

//! [7]

void Decrypter::on_keystreamButton_clicked()
{
    QString temp=openBin();
    if (temp.length()){
        keystreamfilename=temp.toUtf8().constData();
        std::cout << keystreamfilename << std::endl;
        keystreamPathDisplay->setText(temp);
        if (savefilename!="" && keystreamfilename!=""){
            this->decryptButton->setEnabled(true);
            //if we got both, ungray
        }
    }
}

void Decrypter::on_saveButton_clicked(){
    QString temp=openBin();
    if (temp.length()){
        savefilename=temp.toUtf8().constData();
        savePathDisplay->setText(temp);
        if (savefilename!="" && keystreamfilename!=""){
            this->decryptButton->setEnabled(true);
            //if we got both, ungray
        }
    }
}

void Decrypter::on_decryptButton_clicked(){
    //std::cout << savefilename << std::endl;
    //std::cout << keystreamfilename << std::endl;
    if (savefilename!="" && keystreamfilename!=""){
        int keystreamSize=0;
        int saveSize=0;
        std::ifstream saveStream; // using fstream for binary i/o for target file
        std::ifstream keyStream; // using fstream for binary i/o for key file
        std::ofstream decryptedsaveStream; // using fstream for binary i/o for key file
        saveStream.open (savefilename.c_str(), std::ios::binary);
        keyStream.open(keystreamfilename.c_str(), std::ios::binary);
        //std::string decryptedsavefilename="decrypted"+savefilename;
        //std::string decryptedsavefilenamepath=boost::filesystem::path(savefilename).stem();
        //std::string decryptedsavefilename=boost::filesystem::path(savefilename).leaf();
        std::string decryptedsavefilename;
        time_t rawtime;
        struct tm * timeinfo;
        char buffer2 [100];
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        strftime (buffer2,100,"Decrypted Save (%Y-%m-%d %H%M%S).bin",timeinfo);
        decryptedsavefilename= buffer2;

        QString filename = QFileDialog::getSaveFileName(
            this,
            tr("Save Save"),
            tr(decryptedsavefilename.c_str()),
            tr("Save files (*.bin)") );
        if( !filename.isNull() ){
            qDebug( filename.toUtf8() );
        }
        decryptedsavefilename=filename.toUtf8().constData();
        decryptedsaveStream.open (decryptedsavefilename.c_str(), std::ios::binary);
        delete timeinfo;
        // setting the reading position of the target file stream to the end
        saveStream.seekg (0, std::ios::end);
        // getting the position of the reading pointer, thereby retrieving target file size
        saveSize = saveStream.tellg();
        // setting position of the reading pointer to the start of the file


        keyStream.seekg (0, std::ios::end);
        keystreamSize = keyStream.tellg();

        if (keystreamSize==1048732 && saveSize==1048732){

            char fruitBuffer[415232];

            char buffer[415232];

            char keyBuffer[415232];

            saveStream.seekg (21660, std::ios::beg);
            saveStream.read (buffer, 415232);
            keyStream.seekg (21660, std::ios::beg);
            keyStream.read (keyBuffer, 415232);

            for (int i=0; i<415232; i++){

                // inverting every byte in the buffer

                fruitBuffer[i]=buffer[i] ^ keyBuffer[i];

            }

            // incrementing current file pointer by the amount of buffer

            // setting writing pointer to the current location
            // writing the inverted file
            //std::copy(fruitBuffer.begin(), fruitBuffer.end(), std::ostreambuf_iterator<char>(decryptedsaveStream));
            decryptedsaveStream.write (fruitBuffer, 415232);
            saveStream.close();
            keyStream.close();
            decryptedsaveStream.close();
            QMessageBox::information(
            this,
            tr("Pokemon XY Save Decrypter"),
            tr("Save decrypted!") );
        }
//HEAP[PokemonXYSaveDecrypter.exe]:
//Heap block at 13957FE0 modified at 139BD5E8 past requested size of 65600
//so I dropped pointers and picked up vectors, until they made my outputs double the size

/*The inferior stopped because it received a signal from the Operating System.

        Signal name :
        SIGSEGV
        Signal meaning :
        Segmentation fault
*/
    }
}

QString Decrypter::openBin()
{
    QString filename = QFileDialog::getOpenFileName(
    this,
    tr("Open File"),
    QDir::currentPath(),
    "Binary files (*.bin);;All files (*.*)" );
    if( !filename.isNull() )
    {
        qDebug( filename.toUtf8() );
    }
    return filename;//.toUtf8().constData();
}

void Decrypter::on_quitButton_clicked(){
    //ask for confirmation, then exit

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Quit?", "Do you really want to quit?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        //qDebug() << "Yes was clicked";

//        QApplication::quit();
        close();
        qApp->quit();
      }
    /*else {
        qDebug() << "Yes was *not* clicked";
    }*/


}

