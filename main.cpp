#include <iostream>
#include <bitset>
#include <cstring>
#include <clocale>

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");

    // === Часть 1: Мониторинг памяти ===
    cout << "--- 1. Спецификация типов данных ---" << endl;
    cout << "Тип bool занимает:        " << sizeof(bool)        << " байт" << endl;
    cout << "Тип char занимает:        " << sizeof(char)        << " байт" << endl;
    cout << "Тип short int занимает:   " << sizeof(short int)   << " байт" << endl;
    cout << "Тип int занимает:         " << sizeof(int)         << " байт" << endl;
    cout << "Тип long int занимает:    " << sizeof(long int)    << " байт" << endl;
    cout << "Тип long long занимает:   " << sizeof(long long)   << " байт" << endl;
    cout << "Тип float занимает:       " << sizeof(float)       << " байт" << endl;
    cout << "Тип double занимает:      " << sizeof(double)      << " байт" << endl;
    cout << "Тип long double занимает: " << sizeof(long double) << " байт" << endl;
    cout << endl;

    // === Часть 2: Побитовый разбор INT ===
    cout << "--- 2. Анализ целого числа (int) ---" << endl;
    int input_int;
    cout << "Укажите целое число: ";
    cin >> input_int;

    cout << "Бинарный вид: ";
    for (int idx = 31; idx >= 0; idx--) {
        int current_bit = (input_int >> idx) & 1;
        cout << current_bit;
        if (idx == 31) {
            cout << " [знак] ";
        }
    }
    cout << endl << endl;

    // === Часть 3: Побитовый разбор FLOAT ===
    cout << "--- 3. Анализ вещественного числа (float) ---" << endl;
    float input_float;
    cout << "Укажите число float: ";
    cin >> input_float;

    unsigned int float_bytes;
    memcpy(&float_bytes, &input_float, sizeof(float));

    cout << "Структура IEEE 754: ";
    for (int idx = 31; idx >= 0; idx--) {
        cout << ((float_bytes >> idx) & 1);
        if (idx == 31 || idx == 23) {
            cout << " | ";
        }
    }
    cout << "\n(Формат: Знак [1 бит] | Порядок [8 бит] | Мантисса [23 бита])" << endl << endl;

    // === Часть 4: Побитовый разбор DOUBLE ===
    cout << "--- 4. Анализ вещественного числа (double) ---" << endl;
    double input_double;
    cout << "Укажите число double: ";
    cin >> input_double;

    unsigned long long double_bytes;
    memcpy(&double_bytes, &input_double, sizeof(double));

    cout << "Structure IEEE 754: ";
    for (int idx = 63; idx >= 0; idx--) {
        cout << ((double_bytes >> idx) & 1);
        if (idx == 63 || idx == 52) {
            cout << " | ";
        }
    }
    cout << "\n(Формат: Знак [1 бит] | Порядок [11 бит] | Мантисса [52 бита])" << endl << endl;

    // === Часть 5: Модификация отдельных битов ===
    cout << "--- 5. Редактирование битовой маски ---" << endl;
    int choice_type, bit_num, action;

    cout << "Выберите категорию (1 - int, 2 - float, 3 - double): ";
    cin >> choice_type;

    if (choice_type == 1) {
        int val;
        cout << "Значение int: "; cin >> val;
        cout << "Позиция бита (0-31): "; cin >> bit_num;
        cout << "Действие (1 - обнулить, 2 - выставить в 1, 3 - инвертировать): "; cin >> action;

        if (bit_num >= 0 && bit_num <= 31 && action >= 1 && action <= 3) {
            unsigned int mask = 1u << bit_num;
            cout << "Исходный вид: ";
            for (int i = 31; i >= 0; i--) cout << ((val >> i) & 1);
            cout << endl;

            if (action == 1) val &= ~mask;
            else if (action == 2) val |= mask;
            else val ^= mask;

            cout << "Итоговый вид: ";
            for (int i = 31; i >= 0; i--) cout << ((val >> i) & 1);
            cout << " = " << val << endl;
        }
    }
    else if (choice_type == 2) {
        float val;
        cout << "Значение float: "; cin >> val;
        cout << "Позиция бита (0-31): "; cin >> bit_num;
        cout << "Действие (1 - обнулить, 2 - выставить в 1, 3 - инвертировать): "; cin >> action;

        if (bit_num >= 0 && bit_num <= 31 && action >= 1 && action <= 3) {
            unsigned int raw_data;
            memcpy(&raw_data, &val, sizeof(float));
            unsigned int mask = 1u << bit_num;

            cout << "Исходный вид: ";
            for (int i = 31; i >= 0; i--) cout << ((raw_data >> i) & 1);
            cout << endl;

            if (action == 1) raw_data &= ~mask;
            else if (action == 2) raw_data |= mask;
            else raw_data ^= mask;

            memcpy(&val, &raw_data, sizeof(float));
            cout << "Итоговый вид: ";
            for (int i = 31; i >= 0; i--) cout << ((raw_data >> i) & 1);
            cout << " = " << val << endl;
        }
    }
    else if (choice_type == 3) {
        double val;
        cout << "Значение double: "; cin >> val;
        cout << "Позиция бита (0-63): "; cin >> bit_num;
        cout << "Действие (1 - обнулить, 2 - выставить в 1, 3 - инвертировать): "; cin >> action;

        if (bit_num >= 0 && bit_num <= 63 && action >= 1 && action <= 3) {
            unsigned long long raw_data;
            memcpy(&raw_data, &val, sizeof(double));
            
            // ОШИБКА ТУТ: студент забыл поставить 1ULL для double, оставил 1u (32 бита)
            unsigned long long mask = 1u << bit_num; 

            cout << "Исходный вид: ";
            for (int i = 63; i >= 0; i--) cout << ((raw_data >> i) & 1);
            cout << endl;

            if (action == 1) raw_data &= ~mask;
            else if (action == 2) raw_data |= mask;
            else raw_data ^= mask;

            memcpy(&val, &raw_data, sizeof(double));
            cout << "Итоговый вид: ";
            for (int i = 63; i >= 0; i--) cout << ((raw_data >> i) & 1);
            cout << " = " << val << endl;
        }
    }

    // === Индивидуальное задание (ИДЗ) ===
    cout << endl << "--- 6. Индивидуальное задание (Деление на 2) ---" << endl;
    int source_number;
    cout << "Введите число для деления: ";
    cin >> source_number;

    int shift_result = source_number >> 1;

    cout << "Исходное (двоичный код): " << bitset<32>(source_number) << endl;
    cout << "Результат (двоичный код): " << bitset<32>(shift_result) << endl;
    cout << "Математический итог:     " << source_number << " / 2 = " << shift_result << " (дробная часть отброшена)" << endl;

    return 0;
}
