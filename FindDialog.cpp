#include "FindDialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent){
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);
    connect(lineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableFindButton(const QString &)));

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));

    findButton = new QPushButton(tr("&Find"));
    findButton->setDefault(true);
    findButton->setEnabled(false);
    connect(findButton, SIGNAL(clicked()),
            this, SLOT(findClicked()));

    closeButton = new QPushButton(tr("&Close"));
    connect(closeButton, SIGNAL(clicked()),
            this, SLOT(close()));

   // Markup
   QHBoxLayout *lineLayout = new QHBoxLayout;
   lineLayout->addWidget(label);
   lineLayout->addWidget(lineEdit);

   QVBoxLayout *leftLayout = new QVBoxLayout;
   leftLayout->addLayout(lineLayout);
   leftLayout->addWidget(caseCheckBox);
   leftLayout->addWidget(backwardCheckBox);

   QVBoxLayout *rightLayout = new QVBoxLayout;
   rightLayout->addWidget(findButton);
   rightLayout->addWidget(closeButton);

   QHBoxLayout *fullLayout = new QHBoxLayout;
   fullLayout->addLayout(leftLayout);
   fullLayout->addLayout(rightLayout);
   setLayout(fullLayout);

   setWindowTitle(tr("Find &Dialog"));
   setFixedHeight(sizeHint().height());
}

void FindDialog::findClicked(){
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive
                                                       : Qt::CaseInsensitive;

    if (backwardCheckBox->isChecked()){
        emit findPrev(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void FindDialog::enableFindButton(const QString &text){
    findButton->setEnabled(!text.isEmpty());
}
