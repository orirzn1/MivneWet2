//
//  recordsCompany.cpp
//  MivneWet2edit
//
//  Created by Ori Razon on 29/5/2023.
//

#include <stdio.h>
#include "recordsCompany.h"

RecordsCompany::RecordsCompany() : customer_hash(hashTable<std::shared_ptr<Customer>>()), record_copies(nullptr), member_tree(Tree<std::shared_ptr<Customer>, int>()), number_of_records(0)
{
    
}

RecordsCompany::~RecordsCompany()
{
    if(record_copies != nullptr)
        delete[] record_copies;
    //The hash table and trees have their own destructors which will be called automatically
}

double CalculateDiscount(int c_id, node<std::shared_ptr<Customer>,int>* N, double discount);

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    if(number_of_records < 0)
        return StatusType::INVALID_INPUT;
    try
    {
        customer_hash.zeroCustomerDebt();
        if(record_copies)
            delete[] record_copies;
        record_copies = new std::shared_ptr<Record>[number_of_records];
        for(int i = 0; i < number_of_records; i++)
        {
            std::shared_ptr<Record> record = std::make_shared<Record>(i, records_stocks[i]);
            record_copies[i] = record;
        }
        this->number_of_records = number_of_records;
        return StatusType::SUCCESS;
    }
    catch(std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR; 
    }
    
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if(phone < 0 or c_id < 0)
        return StatusType::INVALID_INPUT;
    std::shared_ptr<Customer> customer = std::make_shared<Customer>(c_id, phone);
    try
    {
        if(!customer_hash.insert(customer))
            return StatusType::ALREADY_EXISTS;
    }
    catch(std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if(c_id < 0)
        return Output_t<int>(StatusType::INVALID_INPUT);
    try
    {
       return Output_t<int>(customer_hash.findObject(c_id).get()->getPhone());
    }
    catch(Failure& e)
    {
        return Output_t<int>(StatusType::DOESNT_EXISTS);
    }
}

StatusType RecordsCompany::makeMember(int c_id)
{
    if(c_id < 0)
        return StatusType::INVALID_INPUT;
    try
    {
        std::shared_ptr<Customer> customer = customer_hash.findObject(c_id);
        Customer* customer_raw = customer.get();
        if(customer_raw->getMemberStatus())
            return StatusType::ALREADY_EXISTS;
        customer_raw->makeMember();
        member_tree.insert(customer, c_id);
        double discount = CalculateDiscount(c_id,member_tree.getRoot(),0);
        member_tree.findNode(c_id)->data->add_extra(-1*discount);
        return StatusType::SUCCESS;
    }
    catch(Failure& e)
    {
        return StatusType::DOESNT_EXISTS;
    }
    catch(std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if(c_id < 0)
        return Output_t<bool>(StatusType::INVALID_INPUT);
    try
    {
        Customer* customer = customer_hash.findObject(c_id).get();
        return Output_t<bool>(customer->getMemberStatus());
    }
    catch(Failure& e)
    {
        return Output_t<bool>(StatusType::DOESNT_EXISTS);
    }
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if(c_id < 0 || r_id < 0)
        return StatusType::INVALID_INPUT;
    if(r_id >= number_of_records)
        return StatusType::DOESNT_EXISTS;
    try
    {
        Customer* customer = customer_hash.findObject(c_id).get();
        customer->memberPayment(record_copies[r_id].get()->getNumPurchases() + INITIAL_RECORD_PRICE);
        record_copies[r_id].get()->addPurchase();
        return StatusType::SUCCESS; 
    }
    catch(Failure& e)
    {
        return StatusType::DOESNT_EXISTS;
    }
    
}

void addPrize_aux(node<std::shared_ptr<Customer>,int>* node, double amount, int c_id, bool last_move);

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    if(c_id1 < 0 || c_id2 < c_id1 || amount <= 0)
        return StatusType::INVALID_INPUT;



    node<std::shared_ptr<Customer>,int>* root = member_tree.getRoot();

    //lastmove = true if the last move was right and false if the last move was left

    addPrize_aux(root, amount, c_id2, false);
    addPrize_aux(root, -1*amount,c_id1,false);


}

void addPrize_aux(node<std::shared_ptr<Customer>,int>* node, double amount, int c_id, bool last_move){
    if(node){
        if (node->data->getID() < c_id){
            if(!last_move){
                node->data->add_extra(amount);
            }
            addPrize_aux(node->right,amount,c_id,true);
            return;
        } else if (node->data->getID() > c_id) {
            if(last_move){
                node->data->add_extra(-1*amount);
            }
            addPrize_aux(node->left,amount,c_id,false);
            return;
        } else{
            if(last_move){
                node->data->add_extra(-1*amount);
            }
        }
    }
}
 Output_t<double> RecordsCompany::getExpenses(int c_id) {

     if(c_id < 0 )
         return StatusType::INVALID_INPUT;
     try{
         std::shared_ptr<Customer> target = customer_hash.findObject(c_id);
         double money_owed = target->getMoneyOwed();
         if (!(target->getMemberStatus())){
             return money_owed;
         } else{
             return money_owed - CalculateDiscount(c_id, member_tree.getRoot(), 0);
         }
     } catch (Failure& e) {
         return StatusType::DOESNT_EXISTS;
     }


}

double CalculateDiscount(int c_id, node<std::shared_ptr<Customer>,int>* N, double discount)
{
    discount += N->data->get_prize();
    if (c_id > N->data->getID()){
        return CalculateDiscount(c_id,N->right,discount);
    } else if(c_id < N->data->getID()){
        return CalculateDiscount(c_id,N->left,discount);
    } else
        return discount;

}

