#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Address Book");

    QStringList list=(QStringList()<< ""<< "Alabama "<<" Alaska"<<" Arizona  "<<" Arkansas  "<<" California  "<<" Colorado  "<<" Connecticut  "<<
                      " Delaware  "<<" Florida  "<<" Georgia  "<<" Hawaii  "<<" Idaho  "<<" Illinois  "<<
                      " Indiana  "<<" Iowa  "<<" Kansas  "<<" Kentucky  "<<" Louisiana  "<<" Maine  "<<" Maryland  "<<" Massachusetts" <<
                      " Michigan  "<<" Minnesota  "<<" Mississippi  "<<" Missouri  "<<
                      " Montana  "<<" Nebraska  "<<" Nevada  "<<" New Hampshire  "<<" New Jersey  "<<" New Mexico  "<<" New York  " <<
                      " North Carolina  "<<" North Dakota  "<<" Ohio  "<<" Oklahoma  "<<" Oregon  "<<
                      " Pennsylvania  "<<" Rhode Island  "<<" South Carolina  "<<" South Dakota  "<<" Tennessee  "<<" Texas  "<<
                      " Utah  "<<" Vermont  "<<" Virginia  "<<" Washington  "<<" West Virginia  "<<" Wisconsin  "<<" Wyoming");
    ui->comboBox_state->addItems(list);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNewBook_triggered()
{
    QString selectedFilter = "Text files(*.txt)";

    QString newBookName = QFileDialog::getSaveFileName(this,
                                                        "New Address Book",
                                                        QDir::currentPath(),
                                                        "All files (*.*);;"
                                                        "Text files(*.txt);;",
                                                        &selectedFilter);


    if (!newBookName.isEmpty())
    {
        QFile newFile(newBookName);
        if(!newFile.open(QFile::WriteOnly|QFile::Text))
        {
            qDebug() << "Cannot Open File";
            QMessageBox::information(this, "Error", "Cannot open file\n" + newBookName);
            return;
        }
        else
        {
            currentFile.setFileName(newBookName);
            newFile.close();
            this->setWindowTitle("Address Book - " + newBookName);
            this->persons.clear();
            ui->textBrowser->clear();

            qDebug() << "Book Created";
        }
    }
}



void MainWindow::on_actionOpen_triggered()
{
    QString selectedFilter = "Text files(*.txt)";

    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Open Address Book",
                                                    QDir::currentPath(),
                                                    "All files (*.*);;"
                                                    "Text files(*.txt);;",
                                                    &selectedFilter);


    if (!filename.isEmpty())
    {
        QFile newFile(filename);
        if(!newFile.open(QFile::ReadOnly|QFile::Text))
        {
            qDebug() << "Cannot Create File";
            QMessageBox::information(this, "Error", "Cannot create file\n" + filename);
            return;
        }
        else
        {
            ui->textBrowser->clear();
            this->persons.clear();

            QTextStream in(&newFile);

            while (!in.atEnd())
            {
                Person p;

                for (int i = 0; i < 9; i++)
                {
                    QString line = in.readLine(1000);
                    QStringList strList = line.split(": ");
                    QString text = strList.value(1);

                    switch (i)
                    {
                    case 0:
                        p.firstName = text;
                        break;
                    case 1:
                        p.lastName = text;
                        break;
                    case 2:
                        p.phoneNumber = text;
                        break;
                    case 3:
                        p.email = text;
                        break;
                    case 4:
                        p.address1 = text;
                        break;
                    case 5:
                        p.address2 = text;
                        break;
                    case 6:
                        p.city = text;
                        break;
                    case 7:
                        p.state = text;
                        break;
                    case 8:
                        p.zipCode = text;
                        break;
                    default:
                        break;
                    }
                }

                p.setText(p.firstName + " " + p.lastName);

                persons.push_back(p);

                ui->listWidget->addItem(&persons.last());

                in.readLine(1000);
            }



            currentFile.setFileName(filename);
            newFile.close();
            this->setWindowTitle("Address Book - " + filename);


            qDebug() << "Book Created";
        }
    }
}

void MainWindow::on_action_Save_triggered()
{
    if (currentFile.fileName().isEmpty())
    {
        on_action_SaveAs_triggered();
    }
    else
    {
        if (!currentFile.open(QFile::WriteOnly|QFile::Text))
        {
            QMessageBox::information(this, "Error", "Cannot open file\n" + currentFile.fileName());
            return;
        }
        else
        {
            QTextStream out(&currentFile);
            for (int i = 0; i < persons.size(); i++)
            {
                out << persons[i].getEntry() << "\n";
            }

            currentFile.close();
        }
    }
}

void MainWindow::on_action_SaveAs_triggered()
{
    QString selectedFilter = "Text files(*.txt)";

    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Save As",
                                                    QDir::currentPath(),
                                                    "All files (*.*);;"
                                                    "Text files(*.txt);;",
                                                    &selectedFilter);


    if (!filename.isEmpty())
    {
        QFile newFile(filename);

        if(!newFile.open(QFile::WriteOnly|QFile::Text))
        {
            QMessageBox::information(this, "Error", "Cannot open file\n" + filename);
            return;
        }
        else
        {
            QTextStream out(&newFile);
            for (int i = 0; i < persons.size(); i++)
            {
                out << persons[i].getEntry() << "\n";
            }
            currentFile.setFileName(filename);
            newFile.close();
            this->setWindowTitle("Address Book - " + filename);

        }
    }
}


void MainWindow::on_action_Exit_triggered()
{
    exit(0);
}

void MainWindow::on_action_SortName_triggered()
{
    for (int i = 1; i < persons.size(); i++)
    {
        QString name2 = persons[i].firstName + " " + persons[i].lastName;
        QString name1 = persons[i-1].firstName + " " + persons[i-1].lastName;

        if (name2 < name1)
        {
            for (int j = 0; j < i; j++)
            {
                QString name3 = persons[j].firstName + " " + persons[j].lastName;

                if (name3 >= name2)
                {
                    Person p = persons[i];
                    persons.erase(persons.begin()+i);
                    persons.insert(persons.begin()+j, p);

                    ui->listWidget->insertItem(j, &persons[j]);

                    break;
                }
            }
        }
    }


}

void MainWindow::on_action_SortZipCode_triggered()
{
    for (int i = 1; i < persons.size(); i++)
    {
        if (persons[i].zipCode.toInt() < persons[i-1].zipCode.toInt())
        {
            for (int j = 0; j < i; j++)
            {
                if (persons[j].zipCode.toInt() >= persons[i].zipCode.toInt())
                {
                    Person p = persons[i];
                    persons.erase(persons.begin()+i);
                    persons.insert(persons.begin()+j, p);

                    ui->listWidget->insertItem(j, &persons[j]);

                    break;
                }
            }
        }
    }


}

void MainWindow::on_pushButton_addContacct_clicked()
{
    if (
            (ui->lineEdit_lname->text().isEmpty()&&
            ui->lineEdit_fname->text().isEmpty()) ||
              (
            ui->lineEdit_zipcode->text().isEmpty() &&
            ui->lineEdit_address1->text().isEmpty() &&
            ui->lineEdit_city->text().isEmpty() &&
            ui->lineEdit_phone->text().isEmpty() &&
            ui->lineEdit_email->text().isEmpty() &&
            ui->comboBox_state->currentText() == ""
               )
        )
    {
        QMessageBox::information(this, "Error", "Please at least fill the First Name or Last Name and One more additional info!");
        return;
    }

    bool ok;
    ui->lineEdit_zipcode->text().toInt(&ok);

    if(!ui->lineEdit_zipcode->text().isEmpty())
    {
        if (!ok || ui->lineEdit_zipcode->text().size() != 5)
        {
            QMessageBox::StandardButton resBtn = QMessageBox::question(this,
                                                                       "Wrong Zip-Code format",
                                                                       "The zip-code you entered is not in the correct 5-digit format.\n"
                                                                       "Do you want to add this entry anyway?",
                                                                       QMessageBox::No | QMessageBox::Yes);
            if (resBtn == QMessageBox::No)
            {
                return;
            }
        }
     }



    QString emailInput = ui->lineEdit_email->text();
    int atpos = emailInput.indexOf("@");
    int dotpos = emailInput.lastIndexOf(".");
    if (emailInput != NULL)
    {
        if (atpos<1 || dotpos<atpos+2 || dotpos+2>=emailInput.length())
          {
            QMessageBox::information(this, "Error", "Email format is wrong!");
            return;
          }

    }


    bool validPhoneNum;
    long  phoneNumber = ui->lineEdit_phone->text().toLong(&validPhoneNum,10);

    if (! ui->lineEdit_phone->text().isEmpty())
    {
        if(ui->lineEdit_phone->text().size() == 10)
        {
            if(validPhoneNum==false || phoneNumber<1000000000 ||phoneNumber>9999999999)
            {
                QMessageBox::information(this, "Error", "Phone number must be in a 10 or 7 digits format!");
                return;
             }
        }

        else if( ui->lineEdit_phone->text().size() == 7 )
        {
            if(validPhoneNum==false)
            {
                QMessageBox::information(this, "Error", "Phone number must be in a 10 or 7 digits format!");
                return;
            }
        }

        else if(validPhoneNum == false || ui->lineEdit_phone->text().size() != 7 || ui->lineEdit_phone->text().size() != 10)
        {
            QMessageBox::information(this, "Error", "Phone number must be in a 10 or 7 digits format!");
            return;
        }

   }

    Person person = Person(ui->lineEdit_fname->text(),
                           ui->lineEdit_lname->text(),
                           ui->lineEdit_address1->text(),
                           ui->lineEdit_phone->text(),
                           ui->lineEdit_city->text(),
                           ui->comboBox_state->currentText(),
                           ui->lineEdit_email->text(),
                           ui->lineEdit_zipcode->text(),
                           ui->lineEdit_address2->text());

    person.setText(ui->lineEdit_fname->text() + " " + ui->lineEdit_lname->text());

    persons.push_back(person);

    ui->listWidget->addItem(&persons.last());


}

void MainWindow::on_pushButton_editContact_clicked()
{     
    if (
            (ui->lineEdit_lname->text().isEmpty()&&
            ui->lineEdit_fname->text().isEmpty()) ||
              (
            ui->lineEdit_zipcode->text().isEmpty() &&
            ui->lineEdit_address1->text().isEmpty() &&
            ui->lineEdit_city->text().isEmpty() &&
            ui->lineEdit_phone->text().isEmpty() &&
            ui->lineEdit_email->text().isEmpty() &&
            ui->comboBox_state->currentText() == ""
               )
        )
    {
        QMessageBox::information(this, "Error", "Please at least fill the First Name or Last Name and One more additional info!");
        return;
    }


    bool ok;
    ui->lineEdit_zipcode->text().toInt(&ok);

    if(!ui->lineEdit_zipcode->text().isEmpty())
    {
        if (!ok || ui->lineEdit_zipcode->text().size() != 5)
        {
            QMessageBox::StandardButton resBtn = QMessageBox::question(this,
                                                                       "Wrong Zip-Code format",
                                                                       "The zip-code you entered is not in the correct 5-digit format.\n"
                                                                       "Do you want to add this entry anyway?",
                                                                       QMessageBox::No | QMessageBox::Yes);
            if (resBtn == QMessageBox::No)
            {
                return;
            }
        }
     }

    QString emailInput = ui->lineEdit_email->text();
    int atpos = emailInput.indexOf("@");
    int dotpos = emailInput.lastIndexOf(".");
    if (emailInput != NULL)
    {
        if (atpos<1 || dotpos<atpos+2 || dotpos+2>=emailInput.length())
          {
            QMessageBox::information(this, "Error", "Email format is wrong!");
            return;
          }

    }


    bool validPhoneNum;
    long  phoneNumber = ui->lineEdit_phone->text().toLong(&validPhoneNum,10);

    if (! ui->lineEdit_phone->text().isEmpty())
    {
        if(ui->lineEdit_phone->text().size() == 10)
        {
            if(validPhoneNum==false || phoneNumber<1000000000 ||phoneNumber>9999999999)
            {
                QMessageBox::information(this, "Error", "Phone number must be in a 10 or 7 digits format!");
                return;
             }
        }

        else if( ui->lineEdit_phone->text().size() == 7 )
        {
            if(validPhoneNum==false)
            {
                QMessageBox::information(this, "Error", "Phone number must be in a 10 or 7 digits format!");
                return;
            }
        }

        else if(validPhoneNum == false || ui->lineEdit_phone->text().size() != 7 || ui->lineEdit_phone->text().size() != 10)
        {
            QMessageBox::information(this, "Error", "Phone number must be in a 10 or 7 digits format!");
            return;
        }

   }



    Person person = Person(ui->lineEdit_fname->text(),
                           ui->lineEdit_lname->text(),
                           ui->lineEdit_address1->text(),
                           ui->lineEdit_phone->text(),
                           ui->lineEdit_city->text(),
                           ui->comboBox_state->currentText(),
                           ui->lineEdit_email->text(),
                           ui->lineEdit_zipcode->text(),
                           ui->lineEdit_address2->text());

    person.setText(ui->lineEdit_fname->text() + " " + ui->lineEdit_lname->text());

    int row = ui->listWidget->currentRow();

    persons[row] = person;

    Person* p = dynamic_cast<Person*>(ui->listWidget->currentItem());

    p = &persons[row];

    ui->listWidget->setFocus();
    ui->textBrowser->setText(p->getEntry());


}

void MainWindow::on_pushButton_deleteContact_clicked()
{
    if (ui->listWidget->selectedItems().isEmpty())
    {
        return;
    }

    QMessageBox::StandardButton resBtn = QMessageBox::warning(this,
                                                              "Are you sure?",
                                                              tr("Are you sure that you want to delete this entry?"),
                                                              QMessageBox::No | QMessageBox::Yes);
    if (resBtn == QMessageBox::No)
    {
        return;
    }

    int row = ui->listWidget->currentRow();
    persons.erase(persons.begin()+row);
    ui->listWidget->takeItem(row);
    ui->listWidget->clearSelection();
    ui->textBrowser->clear();


}

void MainWindow::on_pushButton_exit_clicked()
{
    close();
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    if (ui->listWidget->selectedItems().isEmpty())
    {
        ui->pushButton_deleteContact->setEnabled(false);
        ui->pushButton_editContact->setEnabled(false);
        ui->pushButton_fillValues->setEnabled(false);
        ui->textBrowser->clear();
        return;
    }
    else
    {
        ui->pushButton_deleteContact->setEnabled(true);
        ui->pushButton_editContact->setEnabled(true);
        ui->pushButton_fillValues->setEnabled(true);
    }
    Person* p = dynamic_cast<Person*>(ui->listWidget->currentItem());
    ui->textBrowser->setText(p->getEntry());
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        Person* p = dynamic_cast<Person*>(ui->listWidget->item(i));
        QString name = p->firstName + " " + p->lastName;
        if (name.contains(ui->lineEdit->text()))
        {
            ui->listWidget->item(i)->setHidden(false);
        }
        else
        {
            ui->listWidget->item(i)->setHidden(true);
            if (ui->listWidget->item(i)->isSelected())
            {
                ui->listWidget->item(i)->setSelected(false);
            }
        }
    }
}

void MainWindow::on_pushButton_fillValues_clicked()
{
    Person* p = dynamic_cast<Person*>(ui->listWidget->currentItem());

    ui->lineEdit_address1->setText(p->address1);
    ui->lineEdit_address2->setText(p->address2);
    ui->lineEdit_city->setText(p->city);
    ui->lineEdit_email->setText(p->email);
    ui->lineEdit_fname->setText(p->firstName);
    ui->lineEdit_lname->setText(p->lastName);
    ui->lineEdit_phone->setText(p->phoneNumber);
    ui->comboBox_state->setCurrentText(p->state);
    ui->lineEdit_zipcode->setText(p->zipCode);
}



