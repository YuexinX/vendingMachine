//
//  main.cpp
//  vendingmachine
//
//  Created by Time Thief on 7/8/22.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

bool isValidVendingMachineString(string vendingstring);
    bool checkLetters (string vendingstring);
    bool startEndCheck(string vendingstring);
    bool lettersNumberFollowing(string vendingstring);
    bool depositCheck(string vendingstring);
double amountSpent(string vendingstring);
double changeReturned(string vendingstring);
int howManyItemsBought(string vendingstring);


int main() {
    string vendingstring;
    cerr<<"vendingstring: ";
    getline(cin,vendingstring);
    cerr<<"valid or not: "<<isValidVendingMachineString(vendingstring)<<endl
    <<"amount spent: "<<amountSpent(vendingstring)<<endl
    <<"change returned: "<<changeReturned(vendingstring)<<endl
    << "how many items bought: "<<howManyItemsBought(vendingstring)<<endl;
    return (0);

    
}
bool isValidVendingMachineString(string vendingstring)
{
    if (vendingstring.length()<3)
    {
        bool valid=false;
        for (size_t i=0; i<vendingstring.length();i++)
        {
            char c = vendingstring.at(i);
            switch (c)
            {
                case 'R':
                    valid = true;
                    break;
                default:
                    return false;
            }
        }
        return valid;
    }
    else if(vendingstring.length()>=3)
    {
        if (checkLetters(vendingstring) == false || startEndCheck(vendingstring) == false || lettersNumberFollowing(vendingstring) == false || depositCheck(vendingstring) == false)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    return false;
}

bool checkLetters (string vendingstring)
{//check if contain the right letters: DMPRABCpndq$0-9
    bool valid = true;
    for(size_t i = 0; i < vendingstring.length(); i++)
    {
        char letter = vendingstring.at(i);
        if(letter != 'D' && letter != 'M' && letter != 'P' && letter != 'R' && letter != 'A' && letter != 'B' && letter != 'C' && letter != 'p' && letter != 'n' && letter != 'd' && letter !='q' && letter != '$' && letter != '0' && letter != '1' && letter !='2' && letter !='3' && letter != '4' && letter != '5' && letter !='6' && letter !='7' && letter !='8' && letter !='9')
        {
            valid = false;
        }
        else
        {
            valid = true;
        }
    }
    return valid;
}
bool startEndCheck(string vendingstring)
{//check if start with the uppercase letter DMR
    //check if end with a purchase or refund
    bool valid=true;
    char start = vendingstring.at(0);
    char end_purchase = vendingstring.at(vendingstring.length()-3);
    char end_refund = vendingstring.at(vendingstring.length()-1);
    if (start != 'D' && start != 'M' && start != 'R')
    {
        valid = false;
    }
    if (end_purchase != 'P' && end_refund != 'R')
    {
        valid = false;
    }
    return valid;
}
bool lettersNumberFollowing(string vendingstring)
{
    //only a single pndq$ following D or M
    //find D and M
    //check if a second pndq$ presents
    bool valid=true;
    for (size_t i=0; i<vendingstring.length(); i++)
    {
        char letter = vendingstring.at(i);
        if ((letter == 'D' || letter == 'M') && (i+2)<vendingstring.length())
        {
            char first = vendingstring.at(i+1);
            char second = vendingstring.at(i+2);
            if ((first == 'p' || first == 'd' || first == 'n' || first == 'q' || first == '$') && (second == 'D' || second == 'M' || second == 'P' || second == 'R'))
            {
                valid = true;
            }
            else
            {
                valid = false;
            }
        }
        else if ((letter == 'A' || letter == 'B' || letter == 'C')&& (i+2)<vendingstring.length())
        {
            char first = vendingstring.at(i+1);
            char second = vendingstring.at(i+2);
            if((first != '0' && first != '1' && first != '2' && first != '3' && first != '4' && first != '5' && first != '6' && first != '7' && first != '8' && first !='9') || (second != 'P' && second != 'D' && second != 'M' && second != 'R'))
            {
                valid = false;
            }
        }
        else if ((letter == 'A' || letter == 'B' || letter == 'C')&& (i+1)<vendingstring.length())
        {
            char first = vendingstring.at(i+1);
            if (first != '0' && first != '1' && first != '2' && first != '3' && first != '4' && first != '5' && first != '6' && first != '7' && first != '8' && first !='9')
            {
                valid = false;
            }
        }
    }
    return valid;
}

bool depositCheck(string vendingstring)
{
    //deposite must have enough money
    //find item purchased by finding  ABC in the string
    //calculate the amount deposite
    //compare the two amount
    bool valid = true;
    double deposit = 0,change = 0;
        for (size_t i=0; i<vendingstring.length();i++)
        {
            char c = vendingstring.at(i);
            switch (c)
            {
                case 'A':
                    deposit -= 1.00;
                    change = deposit;
                    break;
                case 'B':
                    deposit -= 2.00;
                    change = deposit;
                    break;
                case 'C':
                    deposit -= 3.00;
                    change = deposit;
                    break;
                    //$=1, q=0.25, p=0.01
                    //d=0.1, n=0.05
                case '$':
                    deposit += 1.00;
                    break;
                case 'q':
                    deposit += 0.25;
                    break;
                case 'p':
                    deposit += 0.01;
                    break;
                case 'd':
                    deposit += 0.10;
                    break;
                case 'n':
                    deposit += 0.05;
                    break;
                case 'R':
                    deposit -= deposit;
                    break;
            }
        }
    if(change < 0)
    {
        valid = false;
    }
    return valid;
}

double amountSpent(string vendingstring)
{
    if (isValidVendingMachineString(vendingstring) == true)
    {
        double totalSpent = 0;
        for (size_t i = 0; i<vendingstring.length(); i++)
        {
            char c = vendingstring.at(i);
            switch (c)
            {
                case 'A':
                    totalSpent += 1.00;
                    break;
                case 'B':
                    totalSpent += 2.00;
                    break;
                case 'C':
                    totalSpent += 3.00;
                    break;
            }
        }
        return totalSpent;
    }
    else
    {
        return(-1.00);
    }
}

double changeReturned(string vendingstring)
{
    if (isValidVendingMachineString(vendingstring) == true)
    {
        double deposit = 0, change = 0;
        for(size_t i=0; i<vendingstring.length();i++)
        {
            char c = vendingstring.at(i);
            switch (c)
            {
                case 'A':
                    deposit -= 1.00;
                    change = deposit;
                    break;
                case 'B':
                    deposit -= 2.00;
                    change = deposit;
                    break;
                case 'C':
                    deposit -= 3.00;
                    change = deposit;
                    break;
                    //$=1, q=0.25, p=0.01
                    //d=0.1, n=0.05
                case '$':
                    deposit += 1.00;
                    break;
                case 'q':
                    deposit += 0.25;
                    break;
                case 'p':
                    deposit += 0.01;
                    break;
                case 'd':
                    deposit += 0.10;
                    break;
                case 'n':
                    deposit += 0.05;
                    break;
                case 'R':
                    change = deposit;
                    deposit = 0;
                    break;
            }
        }
        return change;
    }
    else
    {
        return (-1.00);
    }
}

int howManyItemsBought(string vendingstring)
{
    if (isValidVendingMachineString(vendingstring) == true)
    {
        int itemPurchased = 0;
        for (size_t i=0; i<vendingstring.length(); i++)
        {
            char c = vendingstring.at(i);
            switch (c)
            {
                case 'P':
                    itemPurchased++;
                    break;
            }
        }
        return itemPurchased;
    }
    else
    {
        return(-1);
    }
}
