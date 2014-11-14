#include "passwordpolicywindow.h"
#include "ui_passwordpolicywindow.h"

PasswordPolicyWindow::PasswordPolicyWindow(PasswordPolicy *pp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordPolicyWindow)
{
    ui->setupUi(this);
    policy = pp;
    ui->checkLowAlpha->setChecked(policy->getClassRequired(PasswordPolicy::LOW_ALPHAS));
    ui->checkHighAlpha->setChecked(policy->getClassRequired(PasswordPolicy::UPPER_ALPHAS));
    ui->checkDigits->setChecked(policy->getClassRequired(PasswordPolicy::DIGITS));
    ui->checkSymbols->setChecked(policy->getClassRequired(PasswordPolicy::SYMBOLS));
    ui->checkSpace->setChecked(policy->getClassRequired(PasswordPolicy::SPACE));
    ui->spinLowAlpha->setValue(policy->getClassMinimum(PasswordPolicy::LOW_ALPHAS));
    ui->spinHighAlpha->setValue(policy->getClassMinimum(PasswordPolicy::UPPER_ALPHAS));
    ui->spinDigits->setValue(policy->getClassMinimum(PasswordPolicy::DIGITS));
    ui->spinSymbols->setValue(policy->getClassMinimum(PasswordPolicy::SYMBOLS));
    ui->spinSpace->setValue(policy->getClassMinimum(PasswordPolicy::SPACE));
    ui->spinLowAlpha->setEnabled(ui->checkLowAlpha->isChecked());
    ui->spinHighAlpha->setEnabled(ui->checkHighAlpha->isChecked());
    ui->spinDigits->setEnabled(ui->checkDigits->isChecked());
    ui->spinSymbols->setEnabled(ui->checkSymbols->isChecked());
    ui->spinSpace->setEnabled(ui->checkSpace->isChecked());
    ui->checkDiffMinMaxLength->setChecked(policy->getMinLength() != policy->getMaxLength());
    ui->spinMinLegnth->setValue(policy->getMinLength());
    ui->spinMaxLength->setValue(policy->getMaxLength());
    ui->spinMaxLength->setEnabled(ui->checkDiffMinMaxLength->isChecked());
    ui->checkMode->setChecked(policy->getMode() == PasswordPolicy::SPECIAL_MODE);
    ui->lineEditAlphabet->setEnabled(ui->checkMode->isChecked());
    ui->lineEditAlphabet->setText(QString::fromStdString(policy->getSpecialCharset()));
}

PasswordPolicyWindow::~PasswordPolicyWindow()
{
    delete ui;
}

void PasswordPolicyWindow::on_spinMinLegnth_valueChanged(int arg1)
{
    if (!ui->checkDiffMinMaxLength->isChecked())
        ui->spinMaxLength->setValue(arg1);
    else if (arg1 > ui->spinMaxLength->value())
        ui->spinMinLegnth->setValue(ui->spinMaxLength->value());
    policy->setLength(ui->spinMinLegnth->value(), ui->spinMaxLength->value());
}

void PasswordPolicyWindow::on_spinMaxLength_valueChanged(int arg1)
{
    if (!ui->checkDiffMinMaxLength->isChecked())
        ui->spinMinLegnth->setValue(arg1);
    else if (arg1 < ui->spinMinLegnth->value())
        ui->spinMaxLength->setValue(ui->spinMinLegnth->value());
    policy->setLength(ui->spinMinLegnth->value(), ui->spinMaxLength->value());
}

void PasswordPolicyWindow::on_checkDiffMinMaxLength_stateChanged(int arg1)
{
    if (arg1 == Qt::Unchecked)
        ui->spinMinLegnth->setValue(ui->spinMaxLength->value());
    ui->spinMaxLength->setEnabled(arg1 == Qt::Checked);
}

void PasswordPolicyWindow::on_checkMode_stateChanged(int arg1)
{
    ui->checkLowAlpha->setEnabled(arg1 != Qt::Checked);
    ui->checkHighAlpha->setEnabled(arg1 != Qt::Checked);
    ui->checkDigits->setEnabled(arg1 != Qt::Checked);
    ui->checkSymbols->setEnabled(arg1 != Qt::Checked);
    ui->checkSpace->setEnabled(arg1 != Qt::Checked);
    ui->spinLowAlpha->setEnabled(arg1 != Qt::Checked);
    ui->spinHighAlpha->setEnabled(arg1 != Qt::Checked);
    ui->spinDigits->setEnabled(arg1 != Qt::Checked);
    ui->spinSymbols->setEnabled(arg1 != Qt::Checked);
    ui->spinSpace->setEnabled(arg1 != Qt::Checked);
    ui->lineEditAlphabet->setEnabled(arg1 == Qt::Checked);
    if (arg1 == Qt::Unchecked)
        policy->setMode(PasswordPolicy::NORMAL_MODE);
    else
        policy->setMode(PasswordPolicy::SPECIAL_MODE);
}

void PasswordPolicyWindow::on_buttonTest_clicked()
{
    try
    {
        ui->lineEditTest->setText(QString::fromStdString(policy->generate()));
    }
    catch (std::exception e)
    {
        ui->lineEditTest->setText("There's an issue");
    }
}

void PasswordPolicyWindow::changeClassEnabled(PasswordPolicy::CharacterClass cc, bool enabled)
{
    policy->setClassEnabled(cc, enabled);
}

void PasswordPolicyWindow::changeClassMinimum(PasswordPolicy::CharacterClass cc, int minimum)
{
    policy->setClassMinimum(cc, minimum);
}

void PasswordPolicyWindow::on_checkLowAlpha_stateChanged(int arg1)
{
    changeClassEnabled(PasswordPolicy::LOW_ALPHAS, (arg1 != Qt::Unchecked));
    if (arg1 != Qt::Unchecked)
        changeClassMinimum(PasswordPolicy::LOW_ALPHAS, ui->spinLowAlpha->value());
    ui->spinLowAlpha->setEnabled(arg1 != Qt::Unchecked);
}

void PasswordPolicyWindow::on_checkHighAlpha_stateChanged(int arg1)
{
    changeClassEnabled(PasswordPolicy::UPPER_ALPHAS, (arg1 != Qt::Unchecked));
    if (arg1 != Qt::Unchecked)
        changeClassMinimum(PasswordPolicy::UPPER_ALPHAS, ui->spinHighAlpha->value());
    ui->spinHighAlpha->setEnabled(arg1 != Qt::Unchecked);
}

void PasswordPolicyWindow::on_checkDigits_stateChanged(int arg1)
{
    changeClassEnabled(PasswordPolicy::DIGITS, (arg1 != Qt::Unchecked));
    if (arg1 != Qt::Unchecked)
        changeClassMinimum(PasswordPolicy::DIGITS, ui->spinDigits->value());
    ui->spinDigits->setEnabled(arg1 != Qt::Unchecked);
}

void PasswordPolicyWindow::on_checkSymbols_stateChanged(int arg1)
{
    changeClassEnabled(PasswordPolicy::SYMBOLS, (arg1 != Qt::Unchecked));
    if (arg1 != Qt::Unchecked)
        changeClassMinimum(PasswordPolicy::SYMBOLS, ui->spinSymbols->value());
    ui->spinSymbols->setEnabled(arg1 != Qt::Unchecked);
}

void PasswordPolicyWindow::on_checkSpace_stateChanged(int arg1)
{
    changeClassEnabled(PasswordPolicy::SPACE, (arg1 != Qt::Unchecked));
    if (arg1 != Qt::Unchecked)
        changeClassMinimum(PasswordPolicy::SPACE, ui->spinSpace->value());
    ui->spinSpace->setEnabled(arg1 != Qt::Unchecked);
}

void PasswordPolicyWindow::on_spinLowAlpha_valueChanged(int arg1)
{
    changeClassMinimum(PasswordPolicy::LOW_ALPHAS, arg1);
    ui->checkLowAlpha->setChecked(true);
}

void PasswordPolicyWindow::on_spinHighAlpha_valueChanged(int arg1)
{
    changeClassMinimum(PasswordPolicy::UPPER_ALPHAS, arg1);
    ui->checkHighAlpha->setChecked(true);
}

void PasswordPolicyWindow::on_spinDigits_valueChanged(int arg1)
{
    changeClassMinimum(PasswordPolicy::DIGITS, arg1);
    ui->checkDigits->setChecked(true);
}

void PasswordPolicyWindow::on_spinSymbols_valueChanged(int arg1)
{
    changeClassMinimum(PasswordPolicy::SYMBOLS, arg1);
    ui->checkSymbols->setChecked(true);
}

void PasswordPolicyWindow::on_spinSpace_valueChanged(int arg1)
{
    changeClassMinimum(PasswordPolicy::SPACE, arg1);
    ui->checkSpace->setChecked(true);
}

void PasswordPolicyWindow::on_lineEditAlphabet_textChanged(const QString &arg1)
{
    policy->setSpecialCharset(arg1.toStdString());
}

void PasswordPolicyWindow::on_comboDefaults_activated(int index)
{
    switch (index)
    {
    case 1: // hexadecimal
        ui->checkMode->setChecked(true);
        ui->lineEditAlphabet->setText("0123456789abcdef");
        ui->checkDiffMinMaxLength->setChecked(false);
        ui->spinMinLegnth->setValue(24);
        break;
    case 2: // all but spaces
        ui->checkMode->setChecked(false);
        ui->spinLowAlpha->setValue(0);
        ui->spinHighAlpha->setValue(1);
        ui->spinDigits->setValue(2);
        ui->spinSymbols->setValue(2);
        ui->checkSpace->setChecked(false);
        ui->checkDiffMinMaxLength->setChecked(true);
        ui->spinMinLegnth->setValue(12);
        ui->spinMaxLength->setValue(16);
        break;
    case 3: // base 58
        ui->checkMode->setChecked(true);
        ui->lineEditAlphabet->setText("123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz");
        ui->checkDiffMinMaxLength->setChecked(false);
        ui->spinMinLegnth->setValue(16);
        break;
    }
}

void PasswordPolicyWindow::on_buttonSaveClose_clicked()
{
    this->done(0); // indicates change
}

void PasswordPolicyWindow::on_buttonClose_clicked()
{
    this->done(1); // indicates no change
}
