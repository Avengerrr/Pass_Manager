#include "passwordgenerator.h"

#include <cmath>
#include <QDebug>

QString PasswordGenerator::getUpperAlphabet()
{
    return QString("QWERTYUIOPASDFGHJKLZXCVBNM");
}

QString PasswordGenerator::getLowerAlphabet()
{
    return QString("qwertyuiopasdfghjklzxcvbnm");
}

QString PasswordGenerator::getSpecialAlphabet()
{
    return QString("!@#$%^&*()_+./='<>~|");
}

QString PasswordGenerator::getMinusAlphabet()
{
    return "-";
}

QString PasswordGenerator::getNumbersAlphabet()
{
    return QString("1234567890");
}

QString PasswordGenerator::getUnderlineAlphabet()
{
    return "_";
}

int PasswordGenerator::countUniqueSymbols(const QString &password)
{
    QString uniqueSymbols;
    for( QChar c : password ){
        if( uniqueSymbols.contains( c ) == false ){
            uniqueSymbols.append( c );
        }
    }

    return uniqueSymbols.length();
}

int PasswordGenerator::countSpecialSymbols(const QString &password)
{
    int count = 0;
    for(QChar c : password){
        if( getSpecialAlphabet().contains( c ) ){
            count++;
        }
    }
    return count;
}

int PasswordGenerator::countSameSymbols(const QString &password)
{
    int count = 0;
    int prevType = 0;

    for(QChar c : password){
        if( getSymbolType( c ) != prevType )
            count++;
    }

    return count;
}

int PasswordGenerator::countDifferentCase(const QString &password)
{
    int count = 0;
    QChar prevSymbol(' ');

    for(QChar c : password){
        if( isDifferentCase(prevSymbol, c) )
            count++;
    }

    return count;
}

QString PasswordGenerator::getTypeAlphabet(int type)
{
    QString alphabet;

    if( type & CharType::Upper )
        alphabet += getUpperAlphabet();
    if( type & CharType::Lower )
        alphabet += getLowerAlphabet();
    if( type & CharType::Underline )
        alphabet += getUnderlineAlphabet();
    if( type & CharType::Special )
        alphabet += getSpecialAlphabet();
    if( type & CharType::Numbers )
        alphabet += getNumbersAlphabet();
    if( type & CharType::Minus )
        alphabet += getMinusAlphabet();

    return alphabet;
}

int PasswordGenerator::getSymbolType(const QChar &c)
{
    if( getLowerAlphabet().contains( c ) )
        return CharType::Lower;
    if( getUpperAlphabet().contains( c ) )
        return CharType::Upper;
    if( getUnderlineAlphabet().contains( c ) )
        return CharType::Underline;
    if( getMinusAlphabet().contains( c ) )
        return CharType::Minus;
    if( getNumbersAlphabet().contains( c ) )
        return CharType::Numbers;
    if( getSpecialAlphabet().contains( c ) )
        return CharType::Special;

    return -1;
}

bool PasswordGenerator::isDifferentCase(const QChar &c1, const QChar &c2)
{
    if( c1.isLetter() && c2.isLetter() ){
        if( c1.isLower() && c2.isLower() )
            return false;
        if( c1.isUpper() && c2.isUpper() )
            return false;

        return true;
    }else{
        return c1.category() != c2.category();
    }
}

double PasswordGenerator::quality(const QString &password)
{
    int N  = password.length();
    int Nu = countUniqueSymbols(password);
    int Ns = countSpecialSymbols(password);
    int Nr = countDifferentCase(password);
    int Nc = countSameSymbols(password);

    double logN = log( log( Nu ) / log( N ) );
    double quality = N + sqrt( 0.5 * Ns + Nr ) - sqrt( Nc ) * logN;

    qDebug() << quality;

    return quality;
}

double PasswordGenerator::entropy(const QString &password)
{
    int N = countUniqueSymbols(password);
    int L = password.length();

    double entropy = log2( pow(N,L) );
    qDebug() << entropy;

    return entropy;
}

QString PasswordGenerator::getPassword(int type, int length)
{
    QString alphabet = getTypeAlphabet( type );
    QString password;

    for(int i = 0; i < length; ++i){
        password += alphabet.at( qrand() % alphabet.length() );
    }

    return password;
}











