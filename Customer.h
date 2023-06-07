//
//  Customer.h
//  MivneWet2edit
//
//  Created by Ori Razon on 29/5/2023.
//

#ifndef Customer_h
#define Customer_h

class Customer
{
private:
    int ID;
    int phone_num;
    bool is_member;
    int money_owed;
    
public:
    Customer(int c_id, int phone_num) : ID(c_id), phone_num(phone_num), is_member(false), money_owed(0){}
    int getID()
    {
        return ID;
    }
    int getPhone()
    {
        return phone_num;
    }
    bool getMemberStatus()
    {
        return is_member; 
    }
    void makeMember()
    {
        is_member = true;
    }
    void zeroCustomerDebt()
    {
        money_owed = 0;
    }
    void memberPayment(int price)
    {
        if(!is_member)
            return;
        else
            money_owed += price; 
    }
    
};

#endif /* Customer_h */
