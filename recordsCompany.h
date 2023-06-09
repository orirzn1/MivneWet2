#ifndef RECORDS_COMPANY_H
#define RECORDS_COMPANY_H

#import "utilesWet2.h"
#include "Customer.h"
#include "Record.h"
#include "HashTable.h"
#include "MemberTree.h"
#include "UnionFind.h"
#include <memory>

class RecordsCompany {
  public:
    hashTable<std::shared_ptr<Customer>> customer_hash;
    std::shared_ptr<Record>* record_copies;
    MemberTree member_tree;
    int number_of_records;
    UnionFind stacks_of_records;

    
  public:
    RecordsCompany();
    ~RecordsCompany();
    StatusType newMonth(int *records_stocks, int number_of_records);
    StatusType addCostumer(int c_id, int phone);
    Output_t<int> getPhone(int c_id);
    StatusType makeMember(int c_id);
    Output_t<bool> isMember(int c_id);
    StatusType buyRecord(int c_id, int r_id);
    StatusType addPrize(int c_id1, int c_id2, double  amount);
    Output_t<double> getExpenses(int c_id);
    StatusType putOnTop(int r_id1, int r_id2);
    StatusType getPlace(int r_id, int *column, int *hight);
};


#endif
