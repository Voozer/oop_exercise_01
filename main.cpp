//Ильминский Никита М80-207Б-18
/*Создать класс Money для работы с денежными суммами. Сумма денег должна быть представлено двумя
полями: типа unsigned long long для рублей и типа unsigned char – для копеек. Дробная часть (копейки) при
выводе на экран должна быть отделена от целой части запятой. Реализовать сложение сумм, вычитание,
деление сумм, деление суммы на дробное число, умножение на дробное число и операции сравнения.*/

#include <iostream>
#include <cmath>

using namespace std;

class Money {
    unsigned long long rub;
    unsigned char pen;
public:
    Money(int r, int p) {
        setRub(r);
        setPen(p);
    }

    void setRub(int r) {
        rub = r;
    }
    void setPen(int p) {
        pen = p;
    }
    int getRub() {
        return rub;
    }
    int getPen() {
        return pen;
    }

    int conv() {
        return rub * 100 + pen;
    }

    Money add(Money m) {
        Money result(0, 0);
        int p = pen + m.getPen();
        int r = rub + m.getRub();
        result.setRub(r + p / 100);
        result.setPen(p % 100);
        return result;
    }

    Money sub(Money m) {
        Money result(0, 0);
        int p, r;
        if (less(m)) {
            p = m.getPen() - pen;
            r = m.getRub() - rub;
        } else {
            p = pen - m.getPen();
            r = rub - m.getRub();
        }
        if (p < 0) {
            p = 100 + p;
            r--;
        }
        result.setRub(r);
        result.setPen(p);
        return result;
    }

    double div(Money m) {
        return (double)conv() / (double)m.conv();
    }

    double fraction_div(double div) {
        return conv() / div / 100;
    }

    Money fraction_mult(double mult) {
        Money result(0, 0);
        result.setPen(fmod(abs(conv() * mult), 100));
        result.setRub(abs(conv() * mult) / 100);
        return result;
    }

    bool less(Money m) {
        return conv() < m.conv();
    }

    bool eq(Money m) {
        return conv() == m.conv();
    }

    bool greater(Money m) {
        return conv() > m.conv();
    }
};

int main()
{
    int rub, pen;

    cout << "Enter rub1\n";
    cin >> rub;
    cout << "Enter pen1\n";
    cin >> pen;
    Money cash1(rub, pen);

    cout << "Enter rub2\n";
    cin >> rub;
    cout << "Enter pen2\n";
    cin >> pen;
    Money cash2(rub, pen);

    cout << "cash1 is " << cash1.getRub() << " rub, " << cash1.getPen() << " pen\n";
    cout << "cash2 is " << cash2.getRub() << " rub, " << cash2.getPen() << " pen\n";

    Money res = cash1.add(cash2);
    cout << "cash1 + cash2 is " << res.getRub() << " rub, " << res.getPen() << " pen\n";

    res = cash1.sub(cash2);
    if (cash1.less(cash2)) {
        cout << "cash1 - cash2 is -" << res.getRub() << " rub, " << res.getPen() << " pen\n";
    } else {
        cout << "cash1 - cash2 is " << res.getRub() << " rub, " << res.getPen() << " pen\n";
    }

    if (cash2.conv() == 0) {
        cout << "Can't divide: cash2 is 0! Aborting...\n\n";
    } else {
        cout << "cash1 div cash2 is " << cash1.div(cash2) << endl << endl;
    }

    cout << "cash1 < cash2?: " << cash1.less(cash2) << endl;
    cout << "cash1 = cash2?: " << cash1.eq(cash2) << endl;
    cout << "cash1 > cash2?: " << cash1.greater(cash2) << endl << endl;

    double div, mult;
    cout << "Enter cash1 fractional divider\n";
    cin >> div;
    cout << "Enter cash2 fractional multiplier\n";
    cin >> mult;

    if (div == 0) {
        cout << "Can't divide: divider is 0! Aborting...\n";
    } else {
        cout << "cash1 div " << div << " is " << cash1.fraction_div(div) << endl;
    }

    res = cash2.fraction_mult(mult);
    if (mult < 0) {
        cout << "cash2 mult " << mult << " is -" << res.getRub() << " rub, " << res.getPen() << " pen\n";
    } else {
        cout << "cash2 mult " << mult << " is " << res.getRub() << " rub, " << res.getPen() << " pen\n";
    }
    return 0;
}
