#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QtWidgets>

class FenPrincipale : public QWidget
{
    Q_OBJECT

public:
    FenPrincipale();

private slots:
    void genererCode();

private:
    QLineEdit *nom;
    QLineEdit *classeMere;
    QCheckBox *protections;
    QCheckBox *genererConstructeur;
    QCheckBox *genererDestructeur;
    QGroupBox *groupCommentaires;
    QLineEdit *auteur;
    QDateEdit *date;
    QTextEdit *role;
    QPushButton *generer;
    QPushButton *quitter;

 };

#endif // FENPRINCIPALE_H
