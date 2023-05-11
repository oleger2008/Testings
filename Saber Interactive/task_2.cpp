/*
 * 2. Напишите функцию, удаляющую последовательно дублирующиеся символы в строке: 
 */

void RemoveDups(char* str) {
    if (str[0] == '\0') {
        return;
    }

    auto pattern = str[0];
    size_t write_idx = 1u;
    for (size_t i = 1u; str[i] != '\0'; ++i) {
        if (str[i] != pattern) {
            str[write_idx] = str[i];
            pattern = str[i];
            ++write_idx;
        }
    }
    str[write_idx] = '\0';
}
