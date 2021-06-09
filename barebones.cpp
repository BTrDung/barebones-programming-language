#include <iostream> 
#include <fstream> 

#include <vector> 
#include <stack>
#include <map> 

#include <algorithm> 

#include "lexicalAnalyse.h"

class analysisSyntaxTree
{
    public:
        std::map<std::string, int> variable; 
        std::stack<std::string> endBlock;
        std::map<std::string, bool> exist; 

        bool is_statement(int id, std::vector<std::pair<std::string, std::string>> &listToken)
        {  
            if (id >= listToken.size()) 
                return false; 
            if (listToken[id].second == "WHILE") return true; 
            if (listToken[id].second == "INCR") return true; 
            if (listToken[id].second == "DECR") return true; 
            if (listToken[id].second == "END") return true; 
            if (listToken[id].second == "CLEAR") return true; 
            if (listToken[id].second == "PRINT") return true; 
            return false; 
        }

        bool is_identifier(int id, std::vector<std::pair<std::string, std::string>> &listToken)
        {  
            if (listToken[id].first == "IDENTIFIER") 
                return true;
            return false; 
        }

        bool is_terminator(int id, std::vector<std::pair<std::string, std::string>> &listToken)
        {  
            if (listToken[id].first == "TERMINATOR") 
                return true;
            return false; 
        }

        bool is_do(int id, std::vector<std::pair<std::string, std::string>> &listToken)
        {  
            if (listToken[id].second == "DO") 
                return true;
            return false; 
        }

        std::string upcase(std::string s)
        { 
            for(int i = 0; i < s.size(); ++i) 
                if ((int)('a') <= s[i] && s[i] <= (int)('z')) 
                        s[i] = (char)(s[i] - 32); 
            return s; 
        }
        
        std::pair<bool, std::string> read_statement(std::vector<std::pair<std::string, std::string>> &listToken, std::stack<int> &pid, int &id)
        { 
            if (listToken[id].second == "WHILE")
            {
                std::string ls, rs; 
                id += 1;

                if (is_identifier(id, listToken) == true)
                { 
                    ls = listToken[id].second; 
                    id += 1;
                } 
                else 
                { 
                    return {false, "Expect a variable! The true statement is <while <ls> not <rs> do;>."};
                }
              
                if (is_identifier(id, listToken) == true)
                { 
                    std::string op = listToken[id].second; 
                    if (upcase(op) == "NOT") id += 1;
                }
                else 
                { 
                    return {false, "Expect NOT operator! The true statement is <while <ls> not <rs> do;>."};
                }
               
                if (is_identifier(id, listToken) == true)
                { 
                    rs = listToken[id].second; 
                    if (rs == "0") id += 1;
                } 
                else 
                { 
                    return {false, "Expect 0! The true statement is <while <ls> not <rs> do;>."};
                }

                if (is_do(id, listToken) == true)
                { 
                    id += 1; 
                }
                else 
                { 
                    return {false, "Expect \"do\" ! The true statement is <while <ls> not <rs> do;>."};
                }

                if (is_terminator(id, listToken) == true) 
                { 
                    id += 1; 
                }
                else 
                { 
                    return {false, "Expect \";\"! The true statement is <while <ls> not <rs> do;>."};
                }
                pid.push(id); 
                endBlock.push(ls); 
                return {true, ""};
            }     

            if (listToken[id].second == "END")
            { 
                if (endBlock.size() == 0)
                { 
                    return {false, "The command does not valid"}; 
                }

                std::string top = endBlock.top(); 
                if (variable[top] != 0)
                { 
                    id += 1;
                    if (is_terminator(id, listToken) == false) 
                    { 
                        return {false, "Expect  \";\"! The true statement is <end;>."};
                    } 
                    id = pid.top(); 
                }
                else 
                { 
                    pid.pop(); 
                    endBlock.pop(); 
                    id += 1;
                    if (is_terminator(id, listToken) == true) 
                    { 
                        id += 1;
                    } 
                    else 
                    { 
                        return {false, "Expect  \";\"! The true statement is <end;>."};
                    } 
                }
                return {true, ""}; 
            }

            if (listToken[id].second == "INCR")
            { 
                id += 1; 
                if (is_identifier(id, listToken) == true) 
                { 
                    variable[listToken[id].second] += 1;
                } 
                else 
                { 
                    return {false, "Expect a variable! The true statement is <incr <var>;>."};
                }

                id += 1; 
                if (is_terminator(id, listToken) == true) 
                { 
                    id += 1;
                } 
                else 
                { 
                    return {false, "Expect  \";\"! The true statement is <incr <var>;>."};
                } 
                return {true, ""};
            }


            if (listToken[id].second == "DECR")
            { 
                id += 1; 
                if (is_identifier(id, listToken) == true) 
                { 
                    variable[listToken[id].second] -= 1;
                    if (variable[listToken[id].second] < 0) 
                    { 
                        return  {false, "The value of variable is not allow smaller than zero!"}; 
                    }
                } 
                else 
                { 
                    return {false, "Expect a variable! The true statement is <decr <var>;>."};
                }

                id += 1; 
                if (is_terminator(id, listToken) == true) 
                { 
                    id += 1;
                } 
                else 
                { 
                    return {false, "Expect  \";\"! The true statement is <decr <var>;>."};
                } 
                return {true, ""};
            }
        
            if (listToken[id].second == "CLEAR") 
            { 
                id += 1; 
                if (is_identifier(id, listToken) == true)
                { 
                    std::string var = listToken[id].second; 
                    exist[var] = true; 
                }
                else 
                { 
                    return {false, "Expect a variable! The true statement is <clear <var>;>."};
                }
                id += 1; 
                if (is_terminator(id, listToken) == true) 
                { 
                    id += 1; 
                }
                else 
                { 
                    return {false, "Expect  \";\"! The true statement is <clear <var>;>."};
                } 
                return {true, ""};  
            } 

            if (listToken[id].second == "PRINT")
            { 
                id += 1; 
                if (is_identifier(id, listToken) == true)
                { 
                    std::string var = listToken[id].second; 
                    if (exist[var] == true)
                        std::cout<<variable[var]<<std::endl; 
                    else 
                        return {false, "A variable does not exist!."}; 
                }
                else 
                { 
                    return {false, "Expect a variable! The true statement is <clear <var>;>."};
                }
                id += 1; 
                if (is_terminator(id, listToken) == true) 
                { 
                    id += 1; 
                }
                else 
                { 
                    return {false, "Expect  \";\"! The true statement is <clear <var>;>."};
                } 
                return {true, ""};  
            }
            return {false, "Not recognize command!"}; 
        }

        void run(std::vector<std::pair<std::string, std::string>> &listToken)
        { 
            std::stack<int> pid = std::stack<int>();
            pid.push(0); 
            bool getValid = false;
            std::string mess = ""; 

            while(pid.size() != 0)
            { 
                int process = pid.top(); 
                while (is_statement(process, listToken))
                {
                    std::pair<bool, std::string> result = read_statement(listToken, pid, process); 
                    getValid = result.first; 
                    mess = result.second; 
                    if (getValid == false) 
                    { 
                        std::cout<<mess<<std::endl;
                        return; 
                    }
                }
                pid.pop(); 
            } 
        }
};

int main(int argc, char** argv)
{ 
    lexicalAnalyse readToken; 
    std::vector<std::pair<std::string, std::string>> listToken; 
    std::string link = argv[1];
    readToken.__init__(); 
    listToken = readToken.analysis(link);

    analysisSyntaxTree runProgram; 
    runProgram.run(listToken);
    return 0;
}