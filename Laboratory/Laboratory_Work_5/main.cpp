#include <iostream>
#include <bitset>

template<typename T>
class vector{
public:
    vector(){
        std::cout << "all types without bools" << std::endl;
    }
};

template<>
class vector<bool>{
private:
    size_t v_length{0};
    char* v_mas = new char[0];
public:
    vector<bool>(){
        std::cout << "only bool" << std::endl;
    }
    ~vector() {delete[] v_mas;}

    vector(size_t n){
        v_length = n;

        delete[] v_mas;
        v_mas = new char [v_length];

        int ascii = 96;
        for(int i =0; i<v_length; i++){
            if(ascii < 122) {
                ascii += 1;
            }
            else {
                ascii = 97;
            }
            v_mas[i] = char(ascii);
        }

    }

    void Pushback(){
        std::string str = std::bitset<8>(v_mas[v_length-1]).to_string();
        //bool flag = true;
        for(int i =0; i < 8; i++){
            if(str[i] == '1' and i == 0){
                char* mas = new char [v_length];

                for(int i =0; i<v_length; i++) {
                    mas[i] = v_mas[i];
                }

                delete[] v_mas;
                v_mas = new char [v_length+1];

                for(int i =0; i<v_length; i++) {
                    v_mas[i] = mas[i];
                }

                delete[] mas;
                v_mas[v_length] = 00000001;
                v_length++;
                //flag = false;
                break;
            }
            else if(str[i] == '1' and i != 0){
                v_mas[v_length-1] = (1 << 8-i) | v_mas[v_length-1];
                //std::cout << std::bitset<8>( (1 << 8-i)).to_string() << std::endl;
                break;
            }
        }
    }

   void Set(bool val, int index){
       int IndexInMas = index / (sizeof(v_mas[0]) * 8);
       int IndexInVariable = index - 8 * IndexInMas;
       if(val == 1) {
           //std::cout << std::bitset<8>(v_mas[IndexInMas]).to_string() << std::endl;
           v_mas[IndexInMas] = (1 << IndexInVariable) | v_mas[IndexInMas];
       }
       else if(val == 0){
           //std::cout << std::bitset<8>(v_mas[IndexInMas]).to_string() << std::endl;
           v_mas[IndexInMas] = (~(1 << IndexInVariable) & v_mas[IndexInMas]) | (val << IndexInVariable);
       }
   }

   bool Get(int index){
       int IndexInMas = index / (sizeof(v_mas[0]) * 8);
       //std::cout << (((v_mas[IndexInMas]) >> index) & 0b00000001);
       return ((v_mas[IndexInMas]) >> index) & 0b00000001 ;
   }

    size_t Size() {return v_length;}

    void insert(int index, bool val){
        int IndexInMas = index / (sizeof(v_mas[0]) * 8);
        int IndexInVariable = index - 8 * IndexInMas;
        //for(int i = IndexInMas; i< v_length;i++)
        char c;

        for(int i =0; i< IndexInVariable;i++){
            if(((v_mas[IndexInMas]) >> i) & 0b00000001 == 1){
                c = (1 << i) | c;
            }
        }

        if(val == 1)
            c = (1 << IndexInVariable) | c;

        for(int i = IndexInVariable+1; i< 8;i++){
            if(((v_mas[IndexInMas]) >> i) & 0b00000001 == 1){
                c = (1 << i+1) | c;
            }
        }

        bool lastval =  ((v_mas[IndexInMas]) >> 7) & 0b00000001;
        v_mas[IndexInMas] = c;

        for(int i = IndexInMas+1; i < v_length; i++){
            bool LastValInThis = ((v_mas[i]) >> 7) & 0b00000001;
            v_mas[i] = v_mas[i] << 1;
            if(lastval == 1)
                v_mas[i] = 1 | v_mas[i];
            lastval = LastValInThis;
        }

        if(lastval == 1)
            Pushback();
    }

    void erase(int index){
        int IndexInMas = index / (sizeof(v_mas[0]) * 8);
        int IndexInVariable = index - 8 * IndexInMas;
        //for(int i = IndexInMas; i< v_length;i++)

        bool Firstval = 0;

        for(int i = v_length-1; i > IndexInMas; i--){
            bool FirstValInThis = (v_mas[i]) & 0b00000001;
            v_mas[i] = v_mas[i] >> 1;
            if(Firstval == 1)
                v_mas[i] = 0b10000000 | v_mas[i];
            Firstval = FirstValInThis;
        }

        char c;

        for(int i =0; i< IndexInVariable;i++){
            if((((v_mas[IndexInMas]) >> i) & 0b00000001) == 1){
                c = (1 << i) | c;
            }
        }

        for(int i = IndexInVariable+1; i< 8;i++){
            if((((v_mas[IndexInMas]) >> i) & 0b00000001) == 1){
                c = (1 << i-1) | c;
            }
        }

        if(Firstval == 1)
            c= 0b10000000 | c;

        v_mas[IndexInMas] = c;
    }

    void Print(){
        for(int i=0; i<v_length;i++)
        {
            std::cout << std::bitset<8>(v_mas[i]).to_string() << " ";
        }
        std::cout << std::endl;
    }

};

int main() {
    vector<bool> v(3);
    v.Print();
    v.insert(3,1);
    v.Print();
    v.erase(13);
    v.Print();
}
