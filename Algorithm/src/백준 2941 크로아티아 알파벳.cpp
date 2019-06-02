#include <iostream>
#include <string>
#include <array>
#include <algorithm>

int findCroatianAlphabet(const std::string& word, int pos);
int getNumOfCroatianAlphabet(const std::string& word);

int main() {
    std::string word;
    std::cin >> word;

    int num_of_croatian_alphabet {getNumOfCroatianAlphabet(word)};

    std::cout << num_of_croatian_alphabet << std::endl;

    return 0;
}

int findCroatianAlphabet(const std::string& word, int pos) {
    static const std::array<std::string, 8> CROANTIAN_ALPHABETS = {
        "c=",
        "c-",
        "dz=",
        "d-",
        "lj",
        "nj",
        "s=",
        "z=",
    };

    int max_length {0};
    for (auto& alphabet : CROANTIAN_ALPHABETS) {
        int length = alphabet.length();
        int i;
        for (i = 0; i < length; ++i)
            if (word[pos + i] != alphabet[i])
                break;
        if (i == length) 
            max_length = std::max(max_length, length);
    }
    return max_length;
}

int getNumOfCroatianAlphabet(const std::string& word) {
    int num_of_croatian_alphabet {0};

    int length = word.length();
    for (int i = 0; i < word.length(); ++i) {
        int croatian_alphabet_length = findCroatianAlphabet(word, i);
        if (croatian_alphabet_length > 0)
            i += croatian_alphabet_length - 1;
        num_of_croatian_alphabet++;
    }

    return num_of_croatian_alphabet;
}