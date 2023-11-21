#ifndef S21_COMMAND_H
#define S21_COMMAND_H


class s21_Command
{
public:
    s21_Command();
    s21_Command(s21_Command const& other);
    ~s21_Command();
    virtual void redo() =0;
    virtual void undo() =0;
};

#endif // S21_COMMAND_H
