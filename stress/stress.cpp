#include <bits/stdc++.h>
using namespace std;

signed main(){
    system("g++ путь\\к\\файлу\\stupid.cpp -o stupid.exe"); //компиляция в файл stupid.exe
    system("g++ путь\\к\\файлу\\solve.cpp -o solve.exe");
    system("g++ путь\\к\\файлу\\gen.cpp -o gen.exe");
    while (true) {
        system("gen > input.txt"); //отправить вывод в файл input.txt
        system("stupid < input.txt > answer.txt"); // взять ввод из input.txt отправить вывод в файл answer.txt
        system("solve < input.txt > output.txt"); // взять ввод из input.txt отправить вывод в файл output.txt
        if (system("fc answer.txt output.txt") != 0) break; //если файлы не равны - завершить программу. стресс тест в файле input.txt
    }
}