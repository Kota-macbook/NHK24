#include <iostream>
#include <chrono>
#include <thread>

void something()
{
    // 2.5秒スリープする
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
}

int main(int argc, const char * argv[])
{
    // 開始日時を取得する
    auto start = std::chrono::system_clock::now();
    
    // 計測したい処理
    something();
    
    // 終了日時を取得する
    auto end = std::chrono::system_clock::now();
    
    // end - start をミリ秒単位で計算する
    std::chrono::duration<double, std::milli> elapsed = end - start;
    
    // end - start を秒単位で計算する
    std::chrono::duration<double> elapsed2 = end - start;
    
    // 結果をコンソールに出力する
    std::cout << elapsed.count() << "ms" << std::endl;
    std::cout << elapsed2.count() << "s" << std::endl;
    
    return 0;
}
