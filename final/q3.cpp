
#include <iostream>
#include <cassert>
using namespace std;

class Dispenser
{
public:
    Dispenser();
    int addBlorks(int num);
    bool dispenseBlork();

private:
    int m_numBlorks;
    int m_capacity;
};

Dispenser::Dispenser()
{
    m_numBlorks = 0;
    m_capacity = 125;
}

int Dispenser::addBlorks(int num)
{
    if (num <= 0)
        return 0;
    if (m_numBlorks + num > m_capacity)
        num = m_capacity - m_numBlorks;
    m_numBlorks += num;
    return num;
}

bool Dispenser::dispenseBlork()
{
    if (m_numBlorks == 0)
        return false;
    m_numBlorks--;
    return true;
}

class VendingMachine
{
public:
    VendingMachine(int price, int startAmount);
    int addBlorks(int num);
    int purchase(int amt);
    int moneyRetained() const;

private:
    Dispenser m_dispenser;
    int m_price;
    int m_totalMoneyKept;
};

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE VendingMachine MEMBER FUNCTIONS
VendingMachine::VendingMachine(int price, int startAmount)
{
    m_dispenser = Dispenser();
    m_dispenser.addBlorks(startAmount);
    m_price = price;
    m_totalMoneyKept = 0;
}

int VendingMachine::addBlorks(int num)
{
    return m_dispenser.addBlorks(num);
}

int VendingMachine::purchase(int amt)
{
    int wanted = amt / m_price;
    int to_purchase = 0;
    for (int i = 0; i < wanted; i++)
    {
        if(m_dispenser.dispenseBlork()){
           to_purchase++; 
        }
    }
    int cost = to_purchase * m_price;
    m_totalMoneyKept += cost;
    return amt - cost;
}

int VendingMachine::moneyRetained() const
{
    return m_totalMoneyKept;
}
// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE VendingMachine MEMBER FUNCTIONS

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE createVM FUNCTION
VendingMachine *createVM(){
    VendingMachine *vm = new VendingMachine(4,125);
    vm->purchase(80);
    return vm;
}
// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE createVM FUNCTION

int main()
{
    VendingMachine *vm0 = createVM();
    VendingMachine vm(5, 25);
    assert(vm.addBlorks(35) == 35); // So now vm holds 60 blorks
    assert(vm.purchase(47) == 2);   // 9 blorks dispensed, 2 frips change
    assert(vm.moneyRetained() == 45);

    VendingMachine vm2(5, 2);
    assert(vm2.addBlorks(3) == 3); // So now vm holds 60 blorks
    assert(vm2.purchase(31) == 6);   // 9 blorks dispensed, 2 frips change
    assert(vm2.moneyRetained() == 25);
    assert(vm2.addBlorks(1) == 1); // So now vm holds 60 blorks

    assert(vm2.purchase(102) == 97);   // 9 blorks dispensed, 2 frips change
    assert(vm2.moneyRetained() == 30);
    cout << "All tests succeeded" << endl;

    
}