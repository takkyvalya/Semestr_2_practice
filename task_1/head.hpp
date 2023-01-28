#include <string.h>
#include <fstream>
#include <vector>
#include <cstdlib>

namespace m{
    struct Table{
        std::string t_word;
        int t_number;
    };

    class Cipher{
    private:
        std::string m_str;
        std::vector <int> m_fib;
        std::vector <int> m_key;
        std::vector <Table> code;
        int DontKnow;

        int Fibonacci(int n){
            float a1= (1+sqrt(5))/2;
            float a2= pow(a1,n);
            float b1= (1-sqrt(5))/2;
            float b2= pow(b1,n);
            int F = (a2 - b2) / sqrt(5);
            return F;
        }

        void VectorFib(){
            for (int i =2; i<32;i++)
                m_fib.push_back(Fibonacci(i));
        }
        bool Check(){
            bool flag = true;
            for(int i =0; i <m_key.size();i++) {
                bool flag1 = false;
                for (int j = 0; j < 30; j++) {
                    if (m_key[i] == m_fib[j] ) {
                        flag1 = true;
                    }
                }
                bool flag2 = false;
                for (int j = 0; j < code.size(); j++) {
                    if (m_key[i] == code[j].t_number ) {
                        flag2 = true;
                    }
                }

                if(flag1== false or flag2 == false)
                    flag = false;
            }
            return flag;
        }

    public:
        Cipher(int k){         VectorFib(); }
        ~Cipher() { }

        void Encode(){
            std::ifstream file("C:/Users/vtakk/CLionProjects/untitled/Message.txt");
            int k = 2;
            if (!file)
                std::cout << "Error!" << std::endl;
            while(file >> m_str){
                code.emplace_back(Table {m_str, Fibonacci(k)});
                k++;
            }
        }

        void Decode(){
            std::ifstream file("C:/Users/vtakk/CLionProjects/untitled/Key.txt");
            std::ofstream out("C:/Users/vtakk/CLionProjects/untitled/ShMessage.txt");
            if (!file)
                std::cout << "Error!" << std::endl;
            std::string integer;

                while (file >> integer) {
                    m_key.push_back(std::stoi(integer));
                }

            if(Check()==1) {
                //for(int i =0; i<m_key.size()-1; i++)
                //    for(int j =i+1; j<m_key.size();j++)
                //        if(m_key[i] > m_key[j])
                //            std::swap(m_key[i], m_key[j]);
                for (int i = 0; i < m_key.size(); i++)
                    for (int j = 0; j < code.size(); j++)
                        if (code[j].t_number == m_key[i])
                            out << code[j].t_word << " ";
                std::cout << "work: ";
                rightDecode();
            }
            else{
                std::cout << "Error";
            }
        }

        void rightDecode(){
            std::ifstream file("C:/Users/vtakk/CLionProjects/untitled/ShMessage.txt");
            if (!file)
                std::cout << "Error!" << std::endl;
            std::string integer;
            int k =0;

            for(int i =0; i<m_key.size()-1; i++)
                for(int j =i+1; j<m_key.size();j++)
                    if(m_key[i] > m_key[j])
                        std::swap(m_key[i], m_key[j]);

            if(Check()==1){
                for(int i =0; i<m_key.size(); i++)
                    for(int j =0; j<code.size() ;j++)
                        if (code[j].t_number == m_key[i])
                            std::cout << code[j].t_word << " ";
            } else{
                std::cout << "Error";
            }
        }
    };
}