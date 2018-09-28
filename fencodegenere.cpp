#include "fencodegenere.h"
#include "fenprincipale.h"

FenCodeGenere::FenCodeGenere (QString& nomClasse, QString &codeh, QString &codecpp, QWidget *parent=0) : QDialog(parent)
{
    // On assigne les attributs internes pour exploitation ultérieure
    nom_classe = nomClasse;
    code_h = new QString(codeh);
    code_cpp = new QString(codecpp);

    // Créer le QtabWiget pour les onglets
    QTabWidget *onglets = new QTabWidget(this);
    onglets->setGeometry(0,0,400,550);
    QWidget *page1 = new QWidget;
    QWidget *page2 = new QWidget;

    //contenu page header (principale)
    codehGenere = new QTextEdit();
    codehGenere->setPlainText(codeh);
    codehGenere->setReadOnly(true);
    codehGenere->setFont(QFont("Courrier"));
    codehGenere->setLineWrapMode(QTextEdit::NoWrap);

    fermer = new QPushButton("Fermer");
    enregistrerh = new QPushButton("Enregistrer");
    QHBoxLayout *layoutBoutons = new QHBoxLayout;
    layoutBoutons->addWidget(enregistrerh);
    layoutBoutons->addWidget(fermer);
    QVBoxLayout *layoutPage1 = new QVBoxLayout;
    layoutPage1->addWidget(codehGenere);
    layoutPage1->addLayout(layoutBoutons);

    page1->setLayout(layoutPage1);

    // page code cpp
    codecppGenere = new QTextEdit();
    codecppGenere->setPlainText(codecpp);
    codecppGenere->setReadOnly(true);
    codecppGenere->setFont(QFont("Courrier"));
    codecppGenere->setLineWrapMode(QTextEdit::NoWrap);

    fermer2 = new QPushButton("Fermer");
    enregistrercpp = new QPushButton("Enregistrer");
    QHBoxLayout *layoutBoutons2 = new QHBoxLayout;
    layoutBoutons2->addWidget(enregistrercpp);
    layoutBoutons2->addWidget(fermer2);
    QVBoxLayout *layoutPage2 = new QVBoxLayout;
    layoutPage2->addWidget(codecppGenere);
    layoutPage2->addLayout(layoutBoutons2);
    page2->setLayout(layoutPage2);

    // Enfin, ajouter les onglets dans le QTabWidget
    onglets->addTab(page1,"header");
    onglets->addTab(page2,"code cpp");
    resize(400, 550);

/*
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(onglets);
    layoutPrincipal->addWidget(fermer);
*/

    connect(fermer,SIGNAL(clicked()),this,SLOT(accept()));
    connect(fermer2,SIGNAL(clicked()),this,SLOT(accept()));
    connect(enregistrerh,SIGNAL(clicked()),this,SLOT(enregistrer()));
    connect(enregistrercpp,SIGNAL(clicked()),this,SLOT(enregistrer()));
}

void FenCodeGenere::enregistrer()
{
    QString nomDossier = QFileDialog::getExistingDirectory(this);

    // enregistrement du header
    QString nomFichierH = nomDossier + "/" + nom_classe + ".h";
    QFile *fichierH = new QFile(nomFichierH);
    if (!fichierH->open(QIODevice::WriteOnly | QIODevice::Text))
     {
        QMessageBox::critical(this,"Erreur d'enregistrement du fichier",nomFichierH);
        return;
     }
     QTextStream coutH(fichierH);
     coutH << *code_h;
     fichierH->close();

     // enregistrement du code cpp
     QString nomFichierCpp = nomDossier + "/" + nom_classe + ".cpp";
     QFile *fichierCpp = new QFile(nomFichierCpp);
     if (!fichierCpp->open(QIODevice::WriteOnly | QIODevice::Text))
      {
         QMessageBox::critical(this,"Erreur d'enregistrement du fichier",nomFichierCpp);
         return;
      }
      QTextStream coutCpp(fichierCpp);
      coutCpp << *code_cpp;
      fichierCpp->close();
     QMessageBox::information(this,"2 Fichiers enregistrés avec succès :",nomFichierH);
}

void FenCodeGenere::enregistrerCpp()
{
    QMessageBox::information(this,"A venir","Enregistrement du code cpp");
}
