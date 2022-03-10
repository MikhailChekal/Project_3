#include <iostream>
#include <vector>
#include <iterator>
#include "algorithm"
#include "numeric"
#include "random"
#include "functional"
#include "sstream"
#define RANGE(container) std::begin(container), std::end(container)

using namespace  std;

bool is_prime(int N){
    double m = sqrt(N);
    if(N<2 || (!(N&1) && N!=2))
        return false;
    for(int i=3; i<=m; i+=2){
        if(!(N%i))
            return false;
    }
    return true;
}

template<typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& container) {
    out << '[';
    std::copy(begin(container), prev(end(container)), std::ostream_iterator<T>(out, ", "));
    out << *(std::prev(std::end(container))) << ']';
    return out;
}

int main() {
    vector<int> sequence(10);

    std::random_device rd;
    std::mt19937 g(rd()); // generator
    auto distribution = std::uniform_int_distribution(1, 10);

    iota(begin(sequence), end(sequence), 1); // 1


    back_insert_iterator<vector<int>> b (sequence); // 2
    cout << "initial " << sequence << std::endl;
    //*b = 12;


    sequence.push_back(9);
    sequence.push_back(9);
    sequence.push_back(2);


    std::shuffle(begin(sequence), end(sequence), g); // 3
    cout << "shuffled " << sequence << std::endl;


    std::sort(begin(sequence), end(sequence));

    auto to_delete = std::unique(RANGE(sequence)); // 4
    sequence.erase(to_delete, std::end(sequence));
    cout << "without duplicates " << sequence << std::endl;

    auto count_div2 = std::count_if(sequence.begin(), sequence.end(), [](int i){return i % 2 == 1;});
    std::cout << "number of odd " << count_div2 << endl; // 5

    cout << "max " << *(std::max_element(sequence.begin(), sequence.end())) << endl; //6
    cout << "min " << *(std::min_element(sequence.begin(), sequence.end())) << endl; //6

    cout << "prime numbers " << *std::find_if(sequence.begin(), sequence.end(),is_prime) << endl; // 7

    vector<int> transformed;
    std::transform(begin(sequence), end(sequence), back_inserter(transformed),
                   [](auto elem){return elem * elem;});
    sequence.clear();
    std::copy(transformed.begin(), transformed.end(), std::back_inserter(sequence));
    cout << "squared seq " <<  sequence << endl; // 8


    unsigned N = sequence.size();
    vector<int> sequence_2(0);
    for (auto i=0; i<N; i++){
        sequence_2.push_back(distribution(g));
    }
    cout << "seq 2 " << sequence_2 << endl; // 9
    cout << "sum of seq2 " << std::accumulate(sequence_2.begin(), sequence_2.end(), 0) << endl; // 10

    //11


    for (auto i=0; i<3; i++){
        sequence_2[i] = 1;
    }
    cout << "sequence_2 with 1 " << sequence_2 << endl;


    vector<int> sequence_3(0); // 12
    for (auto i=0; i<N; i++){
        sequence_3.push_back(sequence[i] - sequence_2[i]);
    }
    cout << "sequence_3 " << sequence_3 << endl;


    std::replace_if(sequence_3.begin(), sequence_3.end(), [](auto elem){return elem < 0;}, 0); // 13
    cout << ">= zero " << sequence_3 << endl;

    auto to_delete_2 = std::find_if(sequence_3.begin(), sequence_3.end(),
                                    [](auto elem){return elem == 0;});
    sequence_3.erase(to_delete_2, std::end(sequence_3)); // 14
    cout << "no zero " << sequence_3 << endl;

    std::reverse(sequence_3.begin(), sequence_3.end()); // 15
    cout << "reversed sequence_3 " << sequence_3 << endl;


    auto to_delete_3 = std::unique(RANGE(sequence_3));
    sequence_3.erase(to_delete_3, std::end(sequence_3)); // 16
    cout << "three max numbers " << sequence_3[0] << " " << sequence_3[1] << " " << sequence_3[2];


    std::sort(sequence.begin(), sequence.end()); // 17
    std::sort(sequence_2.begin(), sequence_2.end());


    std::vector<int> sequence_4;
    std::merge(sequence.begin(), sequence_2.begin(), sequence.end(), sequence_2.end(),
               std::back_inserter(sequence_4)); // 18
    //std::cout << "sequence_4" << sequence_4 << endl;


    // 19
    // 20
    cout << sequence << endl;
    cout << sequence_2 << endl;
    cout << sequence_3 << endl;

}
