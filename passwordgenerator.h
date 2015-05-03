#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

//class QString;
#include <QString>
#include <random>

/*!
 * \brief Статический класс PasswordGenerator предназначен для операций с паролем
 * таких как вычисление сложности, энтропии и генерации пароля
 */
class PasswordGenerator
{

public:


    enum CharType{
        Upper     = 2,   /// < Тип для символов в верхнем регистре
        Lower     = 4,   /// < Тип для символов в нижнем регистре
        Special   = 8,   /// < Тип для спец символов
        Minus     = 16,  /// < Тип для символов знака минус
        Numbers   = 32,  /// < Тип для символов-цифр
        Underline = 64   /// < Тип для символов подчёркивания
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
