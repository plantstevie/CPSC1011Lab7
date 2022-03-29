#include <stdio.h>
#include <math.h>

int CalcAGI(int wages, int unemp, int interest);
int GetDeduction(int status);
int CalcTaxable(int agi, int deduction);
int CalcTax(int status, int taxable);
int CalcTaxDue(int fedTax, int withheld);

int main () {
    // declare initial variables
    int wages;
    int unemp;
    int interest;
    int status;
    int withheld;
    int fedTax;

    // take inputs
    printf("Please enter wages, taxable interest, and unemployment compensation: \n");
    scanf("%d %d %d", &wages, &interest, &unemp);

    printf("Please enter status (0 dependent, 1 single, 2 married): \n");
    scanf("%d", &status);
    if (status != 0 && status != 1 && status != 2) {
        printf("Error: Must input status 0 (dependent), 1 (single), or 2 (married).\n");
        return -1;
    }

    printf("Please enter taxes withheld: \n");
    scanf("%d", &withheld);
    if (withheld < 0) {
        printf("Error: taxes withheld cannot be less than 0.\n");
        return -1;
    }

    // store fedTax as a variable to avoid later complication
    fedTax = CalcTax(status, CalcTaxable(CalcAGI(wages, unemp, interest), GetDeduction(status)));

    // Calculate AGI
    printf("AGI: $%d\n", CalcAGI(wages, unemp, interest));
    //Calculate deduction
    printf("Deduction: $%d\n", GetDeduction(status));
    // taxable
    printf("Taxable Income: $%d\n", CalcTaxable(CalcAGI(wages, unemp, interest), GetDeduction(status)));
    // fedTax
    printf("Federal Tax: $%d\n", CalcTax(status, CalcTaxable(CalcAGI(wages, unemp, interest), GetDeduction(status))));
    // determine if print tax owed or refund
    if (fedTax - withheld > 0) {
        printf("Taxes Owed: $%d\n", CalcTaxDue(fedTax, withheld));
    } else {
        printf("Tax Refund: $%d\n", CalcTaxDue(fedTax, withheld));
    }
}

int CalcAGI(int wages, int unemp, int interest) {
    return wages + unemp + interest;
}

int GetDeduction(int status) {
    if (status == 0) {
        return 6000;
    } else if (status == 1) {
        return 12000;
    } else if (status == 2) {
        return 24000;
    }
}

int CalcTaxable(int agi, int deduction) {
    if (agi - deduction > 0) {
        return agi - deduction;
    } else {
        return 0;
    }
}

int CalcTax(int status, int taxable) {
   if ((taxable >= 0 && taxable <= 10000) && (status == 1 || status == 0)) {
      return round(taxable * 0.1);
   } else if ((taxable >= 10001 && taxable <= 40000) && (status == 1 || status == 0)) {
      return 1000 + round((taxable - 10000) * 0.12);
   } else if ((taxable >= 40001 && taxable <= 85000) && (status == 1 || status == 0)) {
      return 4600 + round((taxable - 40000) * 0.22);
   } else if ((taxable > 85000) && (status == 1 || status == 0)) {
      return 14500 + round((taxable - 85000) * 0.24);
   } else if ((taxable < 20000) && status == 2) {
      return round(taxable * 0.1);
   } else if ((taxable >= 20001 && taxable <= 80000) && status == 2) {
      return 2000 + round((taxable - 20000) * 0.12);
   } else if ((taxable > 80000) && status == 2) {
      return 9200 + round((taxable - 80000) * 0.22);
   }
}

int CalcTaxDue(int fedTax, int withheld) {
    if (fedTax - withheld > 0) {
        return fedTax - withheld;
    } else if (fedTax - withheld < 0) {
        return withheld - fedTax;
    } else if (fedTax - withheld == 0) {
        return 0;
    }
}