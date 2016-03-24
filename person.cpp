#include "person.h"


QString Person::getEntry() const
{
    QString entry =
            "First Name: " + this->firstName + "\n" +
            "Last Name: " + this->lastName + "\n" +
            "Phone: " + this->phoneNumber + "\n" +
            "Email: " + this->email + "\n" +
            "Address 1: " + this->address1 + "\n" +
            "Address 2: " + this->address2 + "\n" +
            "City: " + this->city + "\n" +
            "State: " + this->state + "\n" +
            "Zip Code: " + this->zipCode + "\n";

    return entry;

}
