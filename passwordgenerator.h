#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

//class QString;
#include <QString>
#include <random>

class PasswordGenerator
{

public:


    enum CharType{
        Upper     = 2,
        Lower     = 4,
        Special   = 8,
        Minus     = 16,
        Numbers   = 32,
        Underline = 64
    };
    static QString getPassword( int type, int length );
    static double  quality(const QString &password);
    static double  entropy(const QString &password);
private:
    static QString getUpperAlphabet();
    static QString getLowerAlphabet();
    static QString getSpecialAlphabet();
    static QString getMinusAlphabet();
    static QString getNumbersAlphabet();
    static QString getUnderlineAlphabet();

    static int countUniqueSymbols(const QString &password);
    static int countSpecialSymbols(const QString &password);
    static int countSameSymbols(const QString &password);
    static int countDifferentCase(const QString &password);

    static QString getTypeAlphabet( int type );
    static int getSymbolType( const QChar &c );
    static bool isDifferentCase( const QChar &c1, const QChar &c2);
};

#endif // PASSWORDGENERATOR_H
