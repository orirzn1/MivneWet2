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
    double money_owed;
    double extra_prize;
    
public:
    Customer(int c_id, int phone_num) : ID(c_id), phone_num(phone_num), is_member(false), money_owed(0), extra_prize(0){}

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
    double getMoneyOwed()
    {
        return money_owed;
    }

    void add_extra(int change){
        extra_prize += change;
    }
    double get_prize(){
        return extra_prize;
    }

};

#endif /* Customer_h */
