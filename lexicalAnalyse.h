#include <iostream> 
#include <vector> 
#include <algorithm> 

class lexicalAnalyse
{ 
    public:
        std::vector<std::pair<std::string, std::vector<std::string>>> rules;
        void __init__()
        { 
            std::vector<std::string> item_keyword = {"WHILE", "INCR", "DECR", "DO", "END", "CLEAR", "PRINT"}; 
            std::vector<std::string> item_identifier = {"ANY"}; 
            std::vector<std::string> item_terminator = {";"}; 
            std::vector<std::string> item_operator = {"NOT"};

            std::vector<std::string> item_integer = {};
            std::vector<std::string> item_string = {}; 

            rules.push_back({"KEYWORD", item_keyword});
            rules.push_back({"IDENTIFIER", item_identifier}); 
            rules.push_back({"TERMINATOR", item_terminator});
            rules.push_back({"OPERATOR", item_operator});
        }

        std::string clearSpace(std::string line)
        { 
            std::string result = "";
            for(int i = 0; i < line.size(); ++i) 
                if (line[i] != ' ') 
                    if ((int)('a') <= line[i] && line[i] <= (int)('z')) 
                        result = result + (char)(line[i] - 32);
                    else
                        result = result + line[i]; 
            return result;
        }
        
        bool valid(char c)
        { 
            return  (int)('a') <= (int)(c) && (int)(c) <= (int)('z') ||
                    (int)('A') <= (int)(c) && (int)(c) <= (int)('Z') || 
                    (int)('0') <= (int)(c) && (int)(c) <= (int)('9'); 
        }

        std::pair<bool, std::pair<int, std::string>> match_string(std::string seq, int pos, std::string org)
        { 
            if (org == "ANY") 
            { 
                std::string getToken = "";
                int buff = 0; 

                while (pos < seq.size() && valid(seq[pos]) == true) 
                { 
                    getToken = getToken + seq[pos++];
                    ++buff; 
                }
                if (buff == 0) // Space  
                    return {false, {0, ""}}; 
                return {true, {buff, getToken}};
            }

            for(short i = 0; i < org.size(); ++i) 
            { 
                char a = seq[pos + i]; 
                char b = org[i]; 
                if ((int)('a') <= (int)(a) && (int)(a) <= (int)('z'))   
                    a = (char)(a - 32); 
                if (a != b)     
                    return {false,{0, ""}};
            }
            return {true, {org.size(), org}}; 
        }

        std::vector<std::pair<std::string, std::string>> analysis(std::string fileName)
        {
            std::ifstream readFile(fileName); 
            std::string seq; 
            std::vector<std::pair<std::string, std::string>> token; 
 
            while (std::getline(readFile, seq))
            { 
                bool findToken = false;
                int position = 0;  
                
                while(seq[0] == ' ') seq.erase(seq.begin());
                while (position < seq.size())
                { 
                    for(short rule = 0; rule < rules.size(); ++rule) 
                        for(short item = 0; item < rules[rule].second.size(); ++item)
                        { 
                            std::pair<bool, std::pair<int, std::string>> checker = match_string(seq, position, rules[rule].second[item]); 
                            if (checker.first == true)
                            { 
                                position += checker.second.first; 
                                findToken = true; 
                                token.push_back({rules[rule].first, checker.second.second});
                                break; 
                            }
                        }
                    if (findToken == false) position += 1;
                    else 
                    if (findToken == true) findToken = false; 
                }   
            }
            readFile.close();
            return token;
        }
}; 
 