#ifndef S21_COMMAND_H
#define S21_COMMAND_H


class Command
{
public:
    Command();
    Command(Command const& other);
    ~Command();
    virtual void redo() =0;
    virtual void undo() =0;
};

#endif // S21_COMMAND_H
