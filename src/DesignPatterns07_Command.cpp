#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Doctor {
public:
    void treatEyes() { cout << "治疗眼" << endl; }
    void treatNose() { cout << "治疗鼻子" << endl; }
};

class Command {
public:
    Command(Doctor* d) : doctor(d) {}
    virtual void treat() = 0;
    ~Command() {
        if (doctor) {
            delete doctor;
        }
    }

protected:
    Doctor* doctor;
};

class EyeCommand : public Command {
public:
    EyeCommand(Doctor* d) : Command(d) {}
    void treat() override { doctor->treatEyes(); }
};

class NoseCommand : public Command {
public:
    NoseCommand(Doctor* d) : Command(d) {}
    void treat() override { doctor->treatNose(); }
};

class Nurse {
public:
    Nurse(Command* c) : cmd(c) {}
    void put() { cmd->treat(); }
    ~Nurse() {
        if (cmd) {
            delete cmd;
        }
    }

private:
    Command* cmd;
};

int main() {
    Nurse* nurse = new Nurse(new EyeCommand(new Doctor()));
    nurse->put();
    return 0;
}