//
//  Record.h
//  MivneWet2edit
//
//  Created by Ori Razon on 29/5/2023.
//

#ifndef Record_h
#define Record_h

static const int INITIAL_RECORD_PRICE = 100;

class Record
{
private:
    int ID;
    int copies;
    int purchases;
    int price;
    
public:
    Record(int ID, int copies) : ID(ID), copies(copies), purchases(0), price(INITIAL_RECORD_PRICE)
    {
        
    }
    
    int getNumPurchases()
    {
        return purchases;
    }
    
    void addPurchase()
    {
        purchases++;
    }
    
};

#endif /* Record_h */
