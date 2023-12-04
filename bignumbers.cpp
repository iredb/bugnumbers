/**************************************
 * Струк Степан Андреевич             *
 * 05.12.2023                         *
 * Арифметика длинных чисел           *
 * https://onlinegdb.com/kJtT0QaBn7   *
 **************************************/

#include <iostream>
#include <string>

using namespace std;

int size(string s){
  int size = 0;
  for (auto symbol: s){
    if (symbol == '-'){
      continue;
    }
    ++size;
  }
  return size;
}

int startPosition(int number[], int len){
  for (int digitIndex = 0; digitIndex < len; ++ digitIndex){
    if (number[digitIndex] != 0){
      return digitIndex;
    }
  }
  
  return len;
}

void rewrite(string stringNumber, int normalNumber[], int numberLen){
  for (int digitIndex = 0; digitIndex < numberLen; ++digitIndex){
    if (stringNumber[0] == '-'){
      normalNumber[digitIndex] = stringNumber[digitIndex + 1] - '0';
    } else {
      normalNumber[digitIndex] = stringNumber[digitIndex] - '0';
    }
  }
}

//сравнение
char comparison(int num1[], int num2[], int len1, int len2){
  int maxLen = len1 > len2 ? len1 : len2;
  
  int help1[maxLen] = { 0 };
  int help2[maxLen] = { 0 };
  
  for (int digitIndex = maxLen - len2; digitIndex < maxLen; ++digitIndex){
    help2[digitIndex] += num2[digitIndex - (maxLen - len2)];
  }
  for (int digitIndex = maxLen - len1; digitIndex < maxLen; ++digitIndex){
    help1[digitIndex] += num1[digitIndex - (maxLen - len1)];
  }
  
  char result = '=';
  
  for (int digitIndex = 0; digitIndex < maxLen; ++digitIndex){
    if (help1[digitIndex] > help2[digitIndex]){
      result = '>';
      break;
    } else if (help2[digitIndex] > help1[digitIndex]){
      result = '<';
      break;
    }
  }
  return result;
}

//сумма
void summ(int num1[], int num2[], int len1, int len2){
  int maxLen = len1 > len2 ? len1 : len2;
  
  int help1[maxLen] = { 0 };
  int help2[maxLen] = { 0 };
  
  for (int digitIndex = maxLen - len2; digitIndex < maxLen; ++digitIndex){
    help2[digitIndex] += num2[digitIndex - (maxLen - len2)];
  }
  for (int digitIndex = maxLen - len1; digitIndex < maxLen; ++digitIndex){
    help1[digitIndex] += num1[digitIndex - (maxLen - len1)];
  }
  
  int summm[maxLen + 1] = { 0 };
  
  for (int digitIndex = maxLen - 1; digitIndex >= 0; --digitIndex){
    summm[digitIndex + 1] += (help1[digitIndex] + help2[digitIndex]) % 10;
    summm[digitIndex] += (help1[digitIndex] + help2[digitIndex]) / 10;
  }
  
  //cout << "result: ";
  
  for (int digitIndex = startPosition(summm, maxLen + 1); digitIndex < maxLen + 1; ++digitIndex){
    cout << summm[digitIndex] << "";
  }
}

//разность
void difference(int num1[], int num2[], int len1, int len2){
    
  if ( comparison(num1, num2, len1, len2) == '<'){
    cout << '-';
    difference(num2, num1, len2, len1);
    return;
  }
  
  int maxLen = len1 > len2 ? len1 : len2;
  
  int help1[maxLen] = { 0 };
  int help2[maxLen] = { 0 };
  
  for (int digitIndex = maxLen - len2; digitIndex < maxLen; ++digitIndex){
    help2[digitIndex] += num2[digitIndex - (maxLen - len2)];
  }
  for (int digitIndex = maxLen - len1; digitIndex < maxLen; ++digitIndex){
    help1[digitIndex] += num1[digitIndex - (maxLen - len1)];
  }
  
  int difff[maxLen + 1] = { 0 };
  
  if ( comparison(num1, num2, len1, len2) == '=' ) {
    cout << 0;
  } else {
    for (int digitIndex = maxLen - 1; digitIndex >= 0; --digitIndex){
      difff[digitIndex] += help1[digitIndex] - help2[digitIndex];
      if (difff[digitIndex] < 0){
        ++++++++++++++++++++difff[digitIndex];
        --difff[digitIndex - 1];
      }
    }
  }
  
  for (int digitIndex = startPosition(difff, maxLen + 1); digitIndex < maxLen; ++digitIndex){
    cout << difff[digitIndex] << "";
  }
}

//умножение
void multiplication(int num1[], int num2[], int len1, int len2){
    
  int mulll[len1 + len2] = { 0 };
  
  for (int digit2Index = len2 - 1; digit2Index >= 0; --digit2Index){
      
    for (int digit1Index = len1 - 1; digit1Index >= 0; --digit1Index){
      mulll[digit1Index + digit2Index + 1] += (num1[digit1Index] * num2[digit2Index]) % 10;
      mulll[digit1Index + digit2Index] += (num1[digit1Index] * num2[digit2Index]) / 10;
      
      if (mulll[digit1Index + digit2Index + 1] >= 10){
        mulll[digit1Index + digit2Index] += mulll[digit1Index + digit2Index + 1] / 10;
        mulll[digit1Index + digit2Index + 1] = mulll[digit1Index + digit2Index + 1] % 10;
      }
      
    }
    
  }
  
  for (int i = startPosition(mulll, len1 + len2); i < len1 + len2; ++i){
    cout << mulll[i] << "";
  }
}

int main(){
  string stringNumber1, stringNumber2;
  
  cout << "enter (1)first number: ";
  cin >> stringNumber1;
  cout << "enter (2)second number: ";
  cin >> stringNumber2;
  
  bool number1Sign = stringNumber1[0] != '-';
  bool number2Sign = stringNumber2[0] != '-';
  
  int number1Len = size(stringNumber1);
  int number2Len = size(stringNumber2);
  
  int number1Array[number1Len];
  int number2Array[number2Len];
  
  rewrite(stringNumber1, number1Array, number1Len);
  rewrite(stringNumber2, number2Array, number2Len);
  
  char what;
  
  cout << "sum -> +\ndifference -> -\nmultiplication -> *\ncomparison -> ?" << endl;
  cin >> what;
  
  switch (what){
    case '+':
      if (!number2Sign && !number1Sign){
        cout << '-';
        summ(number1Array, number2Array, number1Len, number2Len);
        break;
      } else if (number2Sign && number1Sign){
        summ(number1Array, number2Array, number1Len, number2Len);
        break;
      } else if (number1Sign && !number2Sign){
        difference(number1Array, number2Array, number1Len, number2Len);
        break;
      } else if (!number1Sign && number2Sign){
        difference(number2Array, number1Array, number2Len, number1Len);
        break;
      }
    case '-':
      if (!number2Sign && !number1Sign){
        difference(number2Array, number1Array, number2Len, number1Len);
        break;
      } else if (number2Sign && number1Sign){
        difference(number1Array, number2Array, number1Len, number2Len);
        break;
      } else if (number1Sign && !number2Sign){
        summ(number1Array, number2Array, number1Len, number2Len);
        break;
      } else if (!number1Sign && number2Sign){
        cout << '-';
        summ(number2Array, number1Array, number2Len, number1Len);
        break;
      }
    case '*':
      if ( (number1Sign + number2Sign) % 2 == 1 ){
        cout << '-';
      }
      multiplication(number1Array, number2Array, number1Len, number2Len);
      break;
    case '?':
      cout << comparison(number1Array, number2Array, number1Len, number2Len);
      break;
    default:
      cout << "durak?";
  }
  
  return 0;
}
