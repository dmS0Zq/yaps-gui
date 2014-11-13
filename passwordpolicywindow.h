#ifndef PASSWORDPOLICYWINDOW_H
#define PASSWORDPOLICYWINDOW_H

#include <QDialog>
#include "PasswordPolicy.h"

namespace Ui {
class PasswordPolicyWindow;
}

class PasswordPolicyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordPolicyWindow(PasswordPolicy *pp, QWidget *parent = 0);
    ~PasswordPolicyWindow();

private slots:
    void on_spinMinLegnth_valueChanged(int arg1);

    void on_spinMaxLength_valueChanged(int arg1);

    void on_checkDiffMinMaxLength_stateChanged(int arg1);

    void on_checkMode_stateChanged(int arg1);

    void on_buttonTest_clicked();

    void on_checkLowAlpha_stateChanged(int arg1);

    void on_checkHighAlpha_stateChanged(int arg1);

    void on_checkDigits_stateChanged(int arg1);

    void on_checkSymbols_stateChanged(int arg1);

    void on_checkSpace_stateChanged(int arg1);

    void on_spinLowAlpha_valueChanged(int arg1);

    void on_spinHighAlpha_valueChanged(int arg1);

    void on_spinDigits_valueChanged(int arg1);

    void on_spinSymbols_valueChanged(int arg1);

    void on_spinSpace_valueChanged(int arg1);

    void on_lineEditAlphabet_textChanged(const QString &arg1);

private:
    Ui::PasswordPolicyWindow *ui;
    PasswordPolicy policy;

    void changeClassEnabled(PasswordPolicy::CharacterClass cc, bool enabled);
    void changeClassMinimum(PasswordPolicy::CharacterClass cc, int minimum);
};

#endif // PASSWORDPOLICYWINDOW_H
