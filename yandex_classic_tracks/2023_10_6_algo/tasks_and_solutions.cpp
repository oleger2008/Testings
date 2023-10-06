// Написать метод, который заменит все пробелы в строке а "%20" inplace.
// На вход подаётся строка с зарезервироваными под расширение символами (
// гарантируется, что resize() до разумных размеров не будет выделять память).
// Ограничения: О(1) по памяти, О(N) по времени, менять исходную строку можно.

// str.size: [0...std::numeric_limits<size_t>::max]
// char: any

// time: O(n)
// mem: O(1)
void replaceSpaces(std::string &str) {
    if (str.empty()) return;

    const char space = ' ';
    size_t count = 0u;
    for (const auto c : str) {
        if (c == space) {
            ++count;
        }
    }

    const auto old_size = str.size();
    const auto extra = count * 3 - count;
    str.resize(old_size + extra);
    auto cur = str.rbegin() + extra;
    auto free = str.rbegin();

    while (cur != str.rend()) {
        if (*cur == space) {
            *free = '0'; ++free;
            *free = '2'; ++free;
            *free = '%'; ++free;
        } else {
            *free = *cur;
            ++free;
        }
        ++cur;
    }
}

//---------------------------------------

// Для заданой строки найти длину наибольшей подстроки без повторяющихся символов.
// Например:
// abcabccbbddee -> 3 (abc)
// bbbbbb -> 1 (b)
// pwwkew -> 3 (wke)

// str.size: [0...std::numeric_limits<size_t>::max]
// char: any

// time: O(n)
// mem: O(1) | know all possible symbols count
size_t uniqueSymbolsStrSize(std::string_view str) {
    std::unordered_map<char, size_t> poses;
    size_t begin = 0u;
    size_t result = 0u;
    for (size_t i = 0u; i < str.size(); ++i) {
        auto c = str[i];
        if (poses.count(c)) {
            begin = std::max(begin, poses[c] + 1);
        }
        poses[c] = i;
        result = std::max(result, i - begin + 1); 
    }
    return result;
}