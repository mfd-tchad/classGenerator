#ifndef FENCODEGENERE_H
#define FENCODEGENERE_H

#include <QtWidgets>

class FenCodeGenere : public QDialog
{
  Q_OBJECT
public:
    FenCodeGenere(QString &nomClasse, QString &codeh,QString &codecpp, QWidget *parent);

private slots:
    void enregistrer();
    void enregistrerCpp();

private:
    QString nom_classe;
    QString *code_h;
    QString *code_cpp;
    QTextEdit *codehGenere;
    QTextEdit *codecppGenere;
    QPushButton *fermer;
    QPushButton *fermer2;
    QPushButton *enregistrerh;
    QPushButton *enregistrercpp;
};
#endif // FENCODEGENERE_H
