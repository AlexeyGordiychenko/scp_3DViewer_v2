#ifndef S21_POLYGONTYPECOMMAND_H
#define S21_POLYGONTYPECOMMAND_H

#include "s21_command.h"
#include <QColor>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../s21_glwidget.h"

class s21_PolygonTypeCommand : public s21_Command
{
public:
    s21_PolygonTypeCommand(s21_polygonType old_type, s21_polygonType new_type, MainWindow *mw);
    void redo() override;
    void undo() override;
private:
    MainWindow* mw;
    void setPolygonType(s21_polygonType type);
    s21_polygonType old_type;
    s21_polygonType new_type;
};

#endif // S21_POLYGONTYPECOMMAND_H
