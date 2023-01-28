#include <iostream>

int main() {
    const int N = 10;
    //long double mas1[N] = {1,2,3,4};
    //long double mas2[N];
    std::string mas1[N] = {"dw", "iheiq","pighrespokg"};
    std::string mas2[N];

    for(int i=0; i<N;i++){
        std::string* k = &mas1[i];
        mas2[i] = *k;
        std::cout << mas2[i] << " " << sizeof k << " ";
    }

    std::cout << std::endl;

    for (int i =0; i<N;i++){
        mas2[i]=mas2[i];
        std::cout << mas2[i] <<" "<< sizeof mas2[i] << " ";
    }
}
