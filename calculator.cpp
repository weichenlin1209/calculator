#include <bits/stdc++.h>

using namespace std;

enum TokenType
{
    LPAREN, RPAREN, OPERATOR, OPERAND, ERROR
};

typedef struct
{
    TokenType type = TokenType::ERROR;
    string val = "";
    int num = 0;
    int order = -1;

} Token;

const string OP = "+-*/";
const string Paren = "()";
const int Priority[] = {1, 1, 2, 2, 0, 0};
void ToInfix(string expression, vector<Token> &infix);
void ToPostfix(vector<Token> &infix ,vector<Token> &postfix);
int evaluate(vector<Token> &postfix);

int main()
{
    vector<Token> infix;
    vector<Token> postfix;
    string expression;
    int ans;
    cin >> expression;

    ToInfix(expression ,infix);
    ToPostfix(infix ,postfix);
    ans = evaluate(postfix);

    cout << ans;
    return 0;
}

int GetPriority(char s)
{
    if(OP.find(s) != string::npos)
    {
        return Priority[OP.find(s)];
    }
    else
    {
        return Priority[Paren.find(s)+4];
    }
}

TokenType GetType(string c)
{
    if(OP.find(c) != string::npos)
    {
        return TokenType::OPERATOR;
    }
    else if(Paren.find(c) == 0)
    {
        return TokenType::LPAREN;
    }
    else if(Paren.find(c) == 1)
    {
        return TokenType::RPAREN;
    }
    else
    {
        return TokenType::OPERAND;
    }
}

void init(Token &token)
{
    token.type = TokenType::ERROR;
    token.val = "";
    token.num = 0;
    token.order = -1;
}

string ctos(char c)
{
    string s;
    return s+c;
}

void ToInfix(string expression, vector<Token> &infix)
{
    string operand;
    Token token;

    for(const char &s : expression)
    {
        if(OP.find(s) != string::npos || Paren.find(s) != string::npos)
        {
            if(operand != "")
            {
                //operand
                token.num = stoi(operand);
                token.val = operand;
                token.type = GetType(operand);
                infix.push_back(token);
                init(token);
                operand = "";
            }

            //operator
            token.val = ctos(s);
            token.order = GetPriority(s);
            token.type = GetType(token.val);
            infix.push_back(token);
            init(token);
        }
        else
        {
            operand += s;
        }
    }

    if(operand != "")
    {
        //operand
        token.num = stoi(operand);
        token.val = operand;
        token.type = GetType(operand);
        infix.push_back(token);
        init(token);
        operand = "";
    }
}

void ToPostfix(vector<Token> &infix ,vector<Token> &postfix)
{
    stack<Token> sOP;

    for(const Token &token : infix)
    {
        switch(token.type)
        {
            case(TokenType::OPERAND):
            {
                postfix.push_back(token);
                break;
            }

            case(TokenType::LPAREN):
            {
                sOP.push(token);
                break;
            }

            case(TokenType::RPAREN):
            {
                while(!sOP.empty())
                {
                    if(sOP.top().type != TokenType::LPAREN)
                    {
                        postfix.push_back(sOP.top());
                        sOP.pop();
                    }
                    else
                    {
                        sOP.pop();
                        break;
                    }
                }
                break;
            }

            case(TokenType::OPERATOR):
            {
                while(!sOP.empty())
                {
                    if(token.order > sOP.top().order || sOP.top().type == TokenType::LPAREN)
                    {
                        break;
                    }
                    else
                    {
                        postfix.push_back(sOP.top());
                        sOP.pop();
                    }
                }

                sOP.push(token);
                break;
            }

            default:
                return;
        }

    }

    while(!sOP.empty())
    {
        postfix.push_back(sOP.top());
        sOP.pop();
    }

    return;
}

int evaluate(vector<Token> &postfix)
{
    stack<int> s;

    for(Token &t : postfix)
    {
        switch(t.type)
        {
            case TokenType::OPERAND:
            {
                s.push(t.num);
                break;
            }

            case TokenType::OPERATOR:
            {
                int a = 0 ,b = 0;
                b = s.top();
                s.pop();
                a = s.top();
                s.pop();

                switch(t.val[0])
                {
                    case '+':
                    {
                        s.push(a+b);
                        break;
                    }

                    case '-':
                    {
                        s.push(a-b);
                        break;
                    }

                    case '*':
                    {
                        s.push(a*b);
                        break;
                    }

                    case '/':
                    {
                        s.push(a/b);
                        break;
                    }

                    default:
                    {
                        return -1;
                    }

                }

                break;
            }

            default:
            {
                return -1;
            }
        }
    }

    return s.top();
}
