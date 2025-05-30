#include <iostream>
using namespace std;

#define sp ' '
#define nl '\n'
#define N 100

class Sstring{
    protected: 
        char content[N];
        int length;
    public:
        Sstring(){
            content[0] = '\0';
            length = 0;
        }
        Sstring(char x)
        {
            content[0] = x;
            content[1] = '\0';
            length = 1;
        }
        Sstring(char* x){
            int i = 0;
            while(x[i] != '\0')
            {
                content[i] = x[i];
                ++i;
        
            }
            content[i] = '\0';
            length = i;
        }

        void display()
        {
            cout << "Content: " << content << nl << "Length: " << length << nl;
        }

        void delete_first_symbol()
        {
            for(int i = 0; i < length; i++)
            {
                content[i] = content[i+1];
            }
            length--;
        }

        void delete_last_symbol()
        {
            content[length-1] = '\0';
            length--;
        }

        void add_symbol_start(char ch)
        {
            
            for(int i = length; i >= 0; i--)
            {
                content[i+1] = content[i];
            }
            content[0] = ch;
            length++;
        }
        void add_symbol_end(char ch)
        {
            content[length+1] = content[length];
            content[length] = ch;
            length++;
        }

        void concat(Sstring sstr)
        {
            int i;
            for(i = 0; i <= sstr.length; i++) {
                content[i + length] = sstr.content[i];
            }
            length += sstr.length;
        }

        void to_upper_case()
        {
            for(int i = 0; i < length; i++)
            {
                if(content[i] >= 97 && content[i] <= 122)
                {
                    content[i] = (char)(content[i] - 32);
                }
            }
        }

        void to_lower_case()
        {
            for(int i = 0; i < length; i++)
            {
                if(content[i] >= 65 && content[i] <= 90)
                {
                    content[i] = (char)(content[i] + 32);
                }
            }
        }
};

class Bin: public Sstring{
    protected:
        int decimal;

    public:
        Bin():Sstring()
        {
            decimal = 0;
        }
        Bin(char x):Sstring()
        {
            if(x == '0' || x == '1')
            {
                content[0] = x;
                content[1] = '\0';
                length = 1;
                decimal = x - 48;

            }
            else{
                content[0] = '\0';
                length = 0;
                decimal = 0;
            }
        }
        Bin(char *x): Sstring()
        {
            decimal = 0;
            length = 0;
            for(int i = 0; x[i] != '\0'; i++)
            {
                if(x[i] == '0' || x[i] == '1')
                {
                    content[length] = x[i];
                    decimal = decimal * 2 + content[length] - 48;
                    length++;
                }

            }
            content[length] = '\0';
        }        

        void invert()
        {
            decimal = 0;
            for(int i = 0; i < length; i++)
            {
                if(content[i] == '0')
                {
                    content[i] = '1';
                }
                else{
                    content[i] = '0';
                }
                decimal = decimal * 2 + content[i] - '0';
            }
        }

        void bit_or(Bin x)
        {
            decimal = 0;
            if(length > x.length)
            {
                for(int i = 0; i < length - x.length; i++)
                {
                    x.add_symbol_start('0');
                }
            }
            else{
                for(int i =0; i < x.length - length; i++)
                {
                    add_symbol_start('0');
                }
            }

            for(int i = 0; i < length; i++)
            {
                if(content[i] == '0' && x.content[i] == '0')
                {
                    content[i] = '0';
                }
                if(content[i] == '0' && x.content[i] == '1')
                {
                    content[i] = '1';
                }
                if(content[i] == '1' && x.content[i] == '0')
                {
                    content[i] = '1';
                }
                if(content[i] == '1' && x.content[i] == '1')
                {
                    content[i] = '1';
                }
                decimal = decimal*2 + content[i] - '0';
            }
        }

        void bit_and(Bin x)
        {
            decimal = 0;
            if(length > x.length)
            {
                for(int i = 0; i < length - x.length; i++)
                {
                    x.add_symbol_start('0');
                }
            }
            else{
                for(int i =0; i < x.length - length; i++)
                {
                    add_symbol_start('0');
                }
            }

            for(int i = 0; i < length; i++)
            {
                if(content[i] == '0' && x.content[i] == '0')
                {
                    content[i] = '0';
                }
                if(content[i] == '0' && x.content[i] == '1')
                {
                    content[i] = '0';
                }
                if(content[i] == '1' && x.content[i] == '0')
                {
                    content[i] = '0';
                }
                if(content[i] == '1' && x.content[i] == '1')
                {
                    content[i] = '1';
                }
                decimal = decimal*2 + content[i] - '0';
            }
        }

        void shift_right()
        {
            delete_last_symbol();
            add_symbol_start('0');
            decimal /= 2;
        }

        void shift_left()
        {
            delete_first_symbol();
            add_symbol_end('0');
            decimal *= 2;
        }
        
};

class Id: public Sstring
{
    public:
        Id(): Sstring() {};
    

        Id(char x) : Sstring()
        {
            if((x >= '0' && x <= '9') || (x >= 'A' && x <= 'Z') || 
               (x == '_') || (x >= 'a' && x <= 'z'))
            {
                content[0] = x;
                content[1] = '\0';
                length = 1;
            }
        }

        Id(char* x) : Sstring()
        {
            int i = 0, j = 0;            
            bool flag = false;
            while(x[i] != '\0')
            {
                if((x[i] >= 'A' && x[i] <= 'Z') ||
                    (x[i] == '_') || (x[i] >= 'a' && x[i] <= 'z'))
                    {
                        flag = true;        
                    }
                if (flag && (x[i] >= '0' && x[i] <= '9') || (x[i] >= 'A' && x[i] <= 'Z') ||
                    (x[i] == '_') || (x[i] >= 'a' && x[i] <= 'z'))
                    {
                        content[j] = x[i];
                        j++; 
                    }
                    i++;
            }
            content[j] = '\0';
            length = j;
        }
};

void handleSstringMenu(Sstring& sstr)
{
    int choice;
    do
    {
        cout << "\nМеню для обычной строки:\n";
        cout << "1. Показать строку\n";
        cout << "2. Удалить первый символ\n";
        cout << "3. Удалить последний символ\n";
        cout << "4. Добавить символ в начало\n";
        cout << "5. Добавить символ в конец\n";
        cout << "6. Объединить с другой строкой\n";
        cout << "7. Привести к верхнему регистру\n";
        cout << "8. Привести к нижнему регистру\n";
        cout << "0. Выход\n";
        cout << ':' << sp;
        cin >> choice;

        switch(choice) {
            case 1: 
                sstr.display();
                break;
            case 2:
                sstr.delete_first_symbol();
                break;
            case 3:
                sstr.delete_last_symbol();
                break;
            case 4: {
                char c;
                cout << "Введите символ: ";
                cin >> c;
                sstr.add_symbol_start(c);
                break;
            }
            case 5: {
                char c;
                cout << "Введите символ: ";
                cin >> c;
                sstr.add_symbol_end(c);
                break;
            }
            case 6: {
                char str[20];
                cout << "Введите строку для объединения: ";
                cin >> str;
                Sstring s2(str);
                sstr.concat(s2);
                break;
            }
            case 7:
                sstr.to_upper_case();
                break;
            case 8:
                sstr.to_lower_case();
                break;
            case 0:
                return;
            default:
                cout << "Неверный ввод!\n";
        }
    } while (choice != 0);
}
    

void handleBinMenu(Bin& binStr) {
    int choice;
    do {
        cout << "\nМеню для бинарной строки:\n";
        cout << "1. Показать строку\n";
        cout << "2. Инвертировать\n";
        cout << "3. Побитовое И\n";
        cout << "4. Побитовое ИЛИ\n";
        cout << "5. Сдвиг вправо\n";
        cout << "6. Сдвиг влево\n";
        cout << "0. Выход\n";
        cout << ':' << sp;
        cin >> choice;

        switch(choice) {
            case 1:
                binStr.display();
                break;
            case 2:
                binStr.invert();
                break;
            case 3: {
                char mask[20];
                cout << "Введите маску: ";
                cin >> mask;
                Bin temp(mask);
                binStr.bit_and(temp);
                break;
            }
            case 4: {
                char mask[20];
                cout << "Введите маску: ";
                cin >> mask;
                Bin temp(mask);
                binStr.bit_or(temp);
                break;
            }
            case 5:
                binStr.shift_right();
                break;
            case 6:
                binStr.shift_left();
                break;
            case 0:
                return;
            default:
                cout << "Неверный ввод!\n";
        }
    } while(choice != 0);
} 

void handleIdMenu(Id& id)
{
    int choice;
    do {
        cout << "\nМеню для индентификатора: \n";
        cout << "1. Показать идентификатор\n";
        cout << "0. Выход\n";
        cout << ':' << sp;
        cin >> choice;
        switch (choice)
        {
        case 1:
            id.display();
            break;
        case 0:
            return;
        default:
            cout << "Неверный ввод!\n";
        }
    } while (choice != 0);
}

void mainMenu()
{
    int choice;
    do 
    {
        cout << "\nГлавное меню:\n";
        cout << "1. Обычная строка\n";
        cout << "2. Бинарная строка\n";
        cout << "3. Идентификатор\n";
        cout << "0. Выход\n";
        cout << ':' << sp;
        cin >> choice;
        
        switch(choice)
        {
            case 1: {
                char usual_str[N];
                cout << "Введите строку: ";
                cin >> usual_str;

                Sstring sstr(usual_str);
                handleSstringMenu(sstr);
                break; 
            }
            case 2: {
                char binary_str[N];
                cout << "Введите бинарную строку: ";
                cin >> binary_str;

                Bin bin_str(binary_str);
                handleBinMenu(bin_str);
                break;
            }
            case 3: {
                char id_str[N];
                cout << "Введите строку: ";
                cin >> id_str;


                Id id(id_str);
                handleIdMenu(id);
                break;
            }
            case 0:
                return;
            default: 
                cout << "Неверный ввод!\n";
        }
        
    } while(choice != 0);
}

int main()
{
    setlocale(LC_ALL, "ru");
    mainMenu();
    return 0;
}