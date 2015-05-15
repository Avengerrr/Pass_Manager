#include "passwordgenerator.h"

#include <cmath>
#include <QDebug>

/*!
 * \brief Метод для получения алфавита символов в верхнем регистре
 * \return QString - алфавит
 */
QString PasswordGenerator::getUpperAlphabet()
{
    return QString("QWERTYUIOPASDFGHJKLZXCVBNM");
}

/*!
 * \brief Метод для получения алфавита символов в нижнем регистре
 * \return QString - алфавит
 */
QString PasswordGenerator::getLowerAlphabet()
{
    return QString("qwertyuiopasdfghjklzxcvbnm");
}

/*!
 * \brief Метод для получения алфавита специальных символов
 * \return QString - алфавит
 */
QString PasswordGenerator::getSpecialAlphabet()
{
    return QString("!@#$%^&*()_+./='<>~|");
}

/*!
 * \brief Метод для получения алфавита минусов
 * \return QString - алфавит
 */
QString PasswordGenerator::getMinusAlphabet()
{
    return "-";
}

/*!
 * \brief Метод для получения алфавита символов-цифр
 * \return QString - алфавит
 */
QString PasswordGenerator::getNumbersAlphabet()
{
    return QString("1234567890");
}

/*!
 * \brief Метод для получения алфавита символов подчёркивания
 * \return QString - алфавит
 */
QString PasswordGenerator::getUnderlineAlphabet()
{
    return "_";
}

/*!
 * \brief Метод для подсчёта количества уникальных символов в строке
 * \param password - строка
 * \return int - количество уникальных символов
 */
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

/*!
 * \brief Метод для подсчёта количества специ-символов в строке
 * \param password - строка
 * \return количество специальных символов в строке
 */
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

/*!
 * \brief Метод для подсчёта количества символов типы которых различаются
 * \param password - строка
 * \return количество чередований типа символов в строке
 */
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

/*!
 * \brief Метод для подсчёта количества различных регистров символов в строке
 * \param password - строка
 * \return количесвто чередований регистров символов в строке
 */
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

/*!
 * \brief Метод для получения составного алфавита символов из разных групп
 * \param type - тип
 * \return QString - алфавит символов в соответвии с типом
 */
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

/*!
 * \brief Метод для получения типа в который входит указанный символ
 * \param c - символ тип которого нужно определить
 * \return int - тип символа
 */
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

/*!
 * \brief Метод для сравнения регистра символов
 * \param c1 - символ 1
 * \param c2 - символ 2
 * \return true - если регист символов разный, false - если символы в разном регистре
 */
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

/*!
 * \brief Метод для подсчёта качества пароля
 * \param password - параль
 * \return double - качество пароля
 * \warning работает не корректно
 */
double PasswordGenerator::quality(const QString &password)
{
    int N  = password.length();
    int Nu = countUniqueSymbols(password);
    int Ns = countSpecialSymbols(password);
    int Nr = countDifferentCase(password);
    int Nc = countSameSymbols(password);

    double logN = log( log( Nu ) / log( N ) );
    double quality = N + sqrt( 0.5 * Ns + Nr ) - sqrt( Nc ) * logN;

//    qDebug() << quality; /// \debug

    return quality;
}

/*!
 * \brief Метод для подсчёта энтропии символов в строке
 * \param password - строка
 * \return double - энтропия символов в строке
 */
double PasswordGenerator::entropy(const QString &password)
{
    int N = countUniqueSymbols(password);
    int L = password.length();

    double entropy = log2( pow(N,L) );
    qDebug() << entropy;

    return entropy;
}

/*!
 * \brief Метод для генерации пароля
 * \param type - тип символов в пароле
 * \param length - длина пароля
 * \return QString - сгенерированный пароль
 */
QString PasswordGenerator::getPassword(int type, int length)
{
    QString alphabet = getTypeAlphabet( type );
    QString password;

    for(int i = 0; i < length; ++i){
        password += alphabet.at( qrand() % alphabet.length() );
    }

    return password;
}











