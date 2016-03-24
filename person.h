#ifndef PERSON
#define PERSON

#include <QString>
#include <QListWidgetItem>

struct Person : public QListWidgetItem
{
    QString firstName;
    QString lastName;
    QString address1, phoneNumber;
    QString city, state, email;
    QString zipCode;
    QString address2;

    Person() {}

    Person(QString firstName, QString lastName, QString address1, QString phoneNumber, QString city,
           QString state, QString email, QString zipCode, QString address2 = "")
        : firstName(firstName), lastName(lastName), address1(address1), phoneNumber(phoneNumber),
          city(city), state(state), email(email), zipCode(zipCode), address2(address2), QListWidgetItem()
    {
    }

    QString getEntry() const;
};

#endif // PERSON

