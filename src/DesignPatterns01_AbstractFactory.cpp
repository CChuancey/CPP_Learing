#include <iostream>

// 抽象工厂模式，适用于工厂生产固定个数组件的情况,如电脑的组件CPU、显卡和内存
class CPU {
public:
    virtual void cpu_run() = 0;
};

class Card {
public:
    virtual void card_run() = 0;
};

class Memory {
public:
    virtual void memory_run() = 0;
};

// 还可以有AMD生产cpu、card、memory
class IntelCPU : public CPU {
public:
    virtual void cpu_run() override {
        std::cout << "intel cpu run!" << std::endl;
    }
};

class IntelCard : public Card {
public:
    virtual void card_run() override {
        std::cout << "intel card displayed!" << std::endl;
    }
};

class IntelMemory : public Memory {
public:
    virtual void memory_run() override {
        std::cout << "intel memory store files!" << std::endl;
    }
};

class AbstractFactory {
public:
    virtual CPU* createCPU() = 0;
    virtual Card* createCard() = 0;
    virtual Memory* createMemory() = 0;
};

// 还可以有amd、nv等工厂
class IntelFactory : public AbstractFactory {
public:
    virtual CPU* createCPU() { return new IntelCPU; }
    virtual Card* createCard() { return new IntelCard; }
    virtual Memory* createMemory() { return new IntelMemory; }
};

class Computer {
public:
    Computer() = default;
    Computer(CPU* cpu, Card* card, Memory* memory)
        : cpu(cpu), card(card), memory(memory) {}
    void run() {
        cpu->cpu_run();
        card->card_run();
        memory->memory_run();
    }

private:
    CPU* cpu;
    Card* card;
    Memory* memory;
};

int main() {
    AbstractFactory* intelFactory = new IntelFactory;
    CPU* intelCPU = intelFactory->createCPU();
    Card* intelCard = intelFactory->createCard();
    Memory* intelMemory = intelFactory->createMemory();
    // 创建PC时未必全都用intel的cpu、card和memeory
    Computer* pc = new Computer(intelCPU, intelCard, intelMemory);
    pc->run();

    return 0;
}