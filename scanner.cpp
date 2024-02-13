#include <iostream>
#include <string>
#include <vector>
#include <boost/variant.hpp>
#include <fstream>

struct token{
    char type;
    boost::variant<int, std::string, char> val;
};

int main(){
    std::vector<std::string> code;
    std::string fileLine;
    std::ifstream file("code.txt");
    while (getline(file, fileLine)) {
        code.push_back(fileLine);
    }
    file.close();


    std::vector<token> tokenStream;
    for(std::string line : code){
        int ls = line.size();
        int i = 0;
        while(i < ls){
            char current = line[i];
            if(current >= 'a' && current <= 'z' || current >= 'A' && current <= 'Z'){
                std::string word{current};
                i++;
                current = line[i];
                while(current >= 'a' && current <= 'z' || current >= 'A' && current <= 'Z' || current >= '0' && current <= '9' || current == '_'){
                    word.push_back(current);
                    i++;
                    current = line[i];
                }
                if(word == "num" || word == "vec" || word == "mat" || word == "fn" || word == "return"){
                    tokenStream.push_back(token{'k', word});
                }else{
                    tokenStream.push_back(token{'i', word});
                }
            } else if(current >= '0' && current <= '9'){
                std::string num{current};
                i++;
                current = line[i];
                while(current >= '0' && current <= '9'){
                    num.push_back(current);
                    i++;
                    current = line[i];
                }
                tokenStream.push_back(token{'n', num});
            } else if(current == '=' || current == ',' || current == ';' || current == '(' || current == ')' || current == '[' || current == ']' || current == '{' || current == '}' || current == '+' || current == '-' || current == '*' || current == '/' || current == '^'){
                tokenStream.push_back(token{'s', current});
                i++;
            } else if (current == ' '){
                i++;
            } else{
                std::cout << "ERROR\n";
                std::cout << current << std::endl;
                exit(0);
            }
        }
    }

    for(int i = 0; i < tokenStream.size(); i++){
        std::cout << tokenStream[i].type << " " << tokenStream[i].val << std::endl;
    }
}