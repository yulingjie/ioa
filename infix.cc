#include<iostream>
#include<stack>
#include<cctype>
#include<cmath>
const int N_OPTR = 9;
const char pri[N_OPTR][N_OPTR] = {
    {'>','>','<','<','<','<','<','>','>',},
    {'>','>','<','<','<','<','<','>','>',},
    {'>','>','>','>','>','<','<','>','>',},
    {'>','>','>','>','<','<','<','>','>',},
    {'>','>','>','>','>','<','<','>','>',},
    {'>','>','>','>','>','>',' ','>','>',},
    {'<','<','<','<','<','<','<','=',' ',},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',},
    {'<','<','<','<','<','<','<',' ','='}

};
int readNumber(const char* S, std::stack<float>& opnd);
char orderBetween(char a, char b);
float calcu(char op, float opnd);
float calcu(float opnd1, char op, float opnd2);
float evaluate(const char* S)
{
    std::stack<float> opnd; 
    std::stack<char> optr;
    optr.push('\0');
    while(!optr.empty()){
        std::cout<<"cur S = "<<*S<<std::endl;
        if(isdigit(*S))
        {
           int len = readNumber(S,opnd); // read as many operands as possible
           S += len;
        }
        else
        {
            char r = orderBetween(optr.top(),*S);
            std::cout<<"optr top = "<<optr.top()<<" S = "<<*S<<std::endl;
            std::cout<<" r = "<<r<<std::endl;
            //optr.pop();
           switch(r){
               case '<':
                   optr.push(*S); S++; break;
                   
               case '=':
                   optr.pop(); S++;break;
               case '>':
                   char op = optr.top();
                   optr.pop();
                   std::cout<<"op = "<<op<<std::endl;
                   if('!' == op) {
                       float opnd1 = opnd.top();
                       opnd.pop();
                       opnd.push(calcu(op, opnd1));
                   }
                   else 
                   {
                       float opnd2 = opnd.top();
                       opnd.pop();
                       float opnd1 = opnd.top();
                       opnd.pop();
                       opnd.push(calcu(opnd1, op,opnd2));
                   }
                   break;
           }
        }
    }
    float rt = opnd.top();
    opnd.pop();
    return rt;
}
int main(int argc, char* argv[])
{

    const char *test = "2+3*4-5";
    char * t = NULL;
    float rt = evaluate(test);
    std::cout<<"result = "<<rt<<std::endl;
}
int readNumber(const char* S, std::stack<float>& opnd)
{
    int len = 0;
    const char * ite = S;
    float rt = 0;
    while(*ite != '\0')
    {
        //std::cout<<"readNumber "<<*ite<<std::endl;
        if(isdigit(*ite))
        {
            rt =  rt *10 + (*ite -'0');
        }
        else
        {
            break;
        }
        ++ite;
        ++len;
    }
    opnd.push(rt);
    return len;
}

int operator2index(char a)
{
    if(a == '+')
    {
        return 0;
    }
    if (a == '-') return 1;
    if(a == '*') return 2;
    if (a=='/') return 3;
    if( a=='^') return 4;
    if( a == '!') return 5;
    if( a == '(') return 6;
    if(a == ')') return 7;
    if(a == '\0') return 8;
    return -1;
}
char orderBetween(char a, char b)
{
    return pri[operator2index(a)][operator2index(b)];
}

float calcu(char op, float opnd)
{
    if (op == '!')
        return !opnd;
    return 0;
}

float calcu(float opnd1, char a, float opnd2)
{
 if(a == '+')
    {
        return opnd1 + opnd2;
    }
    if (a == '-') 
    {
        return opnd1 - opnd2;
    }
    if(a == '*') 
    {
        return opnd1 * opnd2;
    }
    if (a=='/') 
    {
        return opnd1 / opnd2;
    }
    if( a=='^') 
    {
        return pow(opnd1, opnd2);
    }
    return 0;
}
