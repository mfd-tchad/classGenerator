#include "fenprincipale.h"
#include "fencodegenere.h"

FenPrincipale::FenPrincipale() : QWidget()
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);

    QGroupBox *blocFormulaire = new QGroupBox("Définition de la classe");
    QFormLayout *formulaire = new QFormLayout;
        nom = new QLineEdit();
        classeMere = new QLineEdit();
        formulaire->addRow("&Nom",nom);
        formulaire->addRow("Classe &mère", classeMere);
    blocFormulaire->setLayout(formulaire);
    layoutPrincipal->addWidget(blocFormulaire);

    QGroupBox *blocCasesACocher = new QGroupBox("Options");
       protections = new QCheckBox("Protéger le header contre les inclusions multiples");
       protections->setChecked(true);
       genererConstructeur = new QCheckBox("Générer un constructeur par défaut");
       genererDestructeur = new QCheckBox("Générer un destructeur");

       QVBoxLayout *vbox = new QVBoxLayout;
       vbox->addWidget(protections);
       vbox->addWidget(genererConstructeur);
       vbox->addWidget(genererDestructeur);

     blocCasesACocher->setLayout(vbox);
     layoutPrincipal->addWidget(blocCasesACocher);

        auteur = new QLineEdit();
        date = new QDateEdit();
        date->setDate(QDate::currentDate());
        role = new QTextEdit();
        QFormLayout *formComment = new QFormLayout;
        formComment->addRow("&Auteur",auteur);
        formComment->addRow("Da&te de création", date);
        formComment->addRow("&Rôle de la classe", role);
     groupCommentaires = new QGroupBox("Ajouter des commentaires");
        groupCommentaires->setCheckable(true);
        groupCommentaires->setChecked(false);
        groupCommentaires->setLayout(formComment) ;
    layoutPrincipal->addWidget(groupCommentaires);

    QHBoxLayout *hbox = new QHBoxLayout;
        generer= new QPushButton("&Générer") ;
        quitter = new QPushButton("&Quitter");
        hbox->setAlignment(Qt::AlignRight);
        hbox->addWidget(generer);
        hbox->addWidget(quitter);
    layoutPrincipal->addLayout(hbox);
    setLayout(layoutPrincipal);
    setWindowTitle("Zero Class Generator");
    setWindowIcon(QIcon("icone.png"));
    resize(400, 450);
    connect(quitter,SIGNAL(clicked()),qApp, SLOT(quit()));
    connect(generer,SIGNAL(clicked()),this,SLOT(genererCode()));
}

void FenPrincipale::genererCode()
{
    if(nom->text().isEmpty())
    {
        QMessageBox::critical(this,"Erreur","Veuillez entrer au moins un nom de classe");
        return; // arrêt de la méthode
    }
    // si tout va bien, on génère le code pour le .h et le .cpp
    QString codeh = 0;

    //Génération du code à l'aide des informations de la fenêtre
    if (groupCommentaires->isChecked())
    {
        codeh = "/*\nAuteur : " + auteur->text() + "\nDate de création : " + date->text() + "\n\nRôle : \n" + role->toPlainText() + "\n*/\n\n\n";
    }
    if (protections->isChecked())
    {
        codeh+= "#ifndef HEADER_" + nom->text().toUpper() + "\n#define HEADER_" + nom->text().toUpper() + "\n\n\n";

    }
    codeh+= "Class " + nom->text();
    if (!classeMere->text().isEmpty())
    {
        codeh+= " : public " + classeMere->text();
    }
    codeh += "\n{\n  public:\n";
    if (genererConstructeur->isChecked())
    {
        codeh+="       " + nom->text() + "();\n";
    }
    if (genererDestructeur->isChecked())
    {
        codeh+="       ~" + nom->text() + "();\n";
    }
    codeh += "\n\n  protected:\n\n\n    private:\n\n};\n";
    if (protections->isChecked())
    {
        codeh+= "#endif // HEADER_" + nom->text().toUpper() + "\n";
    }


    // Reste à générer le code pour le .cpp
    QString codecpp = 0;
    codecpp = "#include \"" + nom->text() + ".h\"\n\n";
    if (genererConstructeur->isChecked())
    {
        codecpp += nom->text() + "::" + nom->text() + "()";
        if (!classeMere->text().isEmpty())
        {
            codecpp+= " : " + classeMere->text() + "()";
        }
        codecpp += "\n{\n\n}\n\n";
    }
    if (genererDestructeur->isChecked())
    {
        codecpp += nom->text() + "::~" + nom->text() + "()\n";
        codecpp += "{\n\n}\n";
    }
    // On crée puis affiche la fenêtre qui affichera le code généré, qu'on lui envoie en paramètre
    QString nomClasse = nom->text();
    FenCodeGenere *fenetreCode = new FenCodeGenere(nomClasse, codeh, codecpp, this);
    fenetreCode->exec();
}


